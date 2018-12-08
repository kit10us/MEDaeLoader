// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <me/game/Game.h>
#include <me/render/VertexUtil.h>
#include <dae/library_geometries/Mesh.h>
#include <dae/Document.h>
#include <unify/V3.h>
#include <unify/TexCoords.h>
#include <unify/DataLock.h>

using namespace dae;

typedef std::vector< float > VFloat;
typedef std::vector< int > VInt;

Mesh::Mesh( IDocument & document, const qxml::Element * node )
: DocumentNode( document, node )
{
	using namespace me;
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "source" ) )
		{
			std::shared_ptr< Source > source( new Source( document, childNode ) );
			m_source.push_back( source );
			m_source_map[ source->GetID() ] = m_source.size() - 1;
		}
		else if ( childNode->IsTagName( "vertices" ) )
		{
			m_vertices.reset( new Vertices( document, childNode ) );
		}
		else if ( childNode->IsTagName( "polylist" ) )
		{
			// polylist.count	- The number of faces (polylist.vcount size).
			// polylist.input*	- Dictates the layout of the vertex.
			// polylist.vcount	- Array of vertex counts, each represents the number of vertices in a face.
			// polylist.p		- Sets (size by number of inputs) alternating index into inputs to describe the actual vertices used.
			// polylist.p.size / polylist.input.size = number of vertices = sum of polylist.vcount
			// polylis.count = number of polylist.vcount = number of faces
			std::shared_ptr< Polylist > polylist( new Polylist( document, childNode ) );
			m_polylist.push_back( polylist );
		}
		else if ( childNode->IsTagName( "triangles" ) )
		{
			// NOTE: Using polylist as it reduces duplicate code.
			// An * represents a value that is not native to the triangle, it's 
			// triangles.count	- Number of triangle primities.
			// triangles.input* - Dicates the layout of the vertex.
			// *polylist.vcount = 3 - This is constant
			// triangles.p
			std::shared_ptr< Polylist > polylist( new Polylist( document, childNode ) );
			m_polylist.push_back( polylist );
		}
	}
}

void Mesh::GetSources( std::list< ContributingInput > & sources, const Input_Shared * input, int offset, size_t & pStride ) const
{
	using namespace me;
	std::string realName;
	
	// Remove prepended "#" from name if it exists...
	if ( input->GetSource().at( 0 ) == '#' )
	{
		realName = input->GetSource().substr( 1 );
	}
	else
	{
		realName = input->GetSource();
	}

	// If we are referencing the vertices, then it can expand to multiple sources.
	if ( realName == m_vertices->GetID() )
	{
		for( auto && subInput : m_vertices->GetInput() )
		{
			GetSources( sources, subInput.get(), offset + input->GetOffset(), pStride );
		}
	}
	else
	{
		std::map< std::string, size_t >::const_iterator itr = m_source_map.find( realName );
		if ( itr != m_source_map.end() )
		{
			sources.push_back( ContributingInput{ input, m_source.at( itr->second ).get(), input->GetOffset() + offset } );
			pStride = std::max( pStride, (size_t)input->GetOffset() + 1 );
		}
	}
}

void Mesh::Build( me::render::Mesh & mesh, const unify::Matrix & matrix, const BindMaterial_TechniqueCommon * technique, const dae::Skin * skin, const me::render::Skeleton * skeleton ) const
{
	using namespace me;

	auto & accumulatedPL = mesh.GetPrimitiveList();

	// polylist and triangles are treated as polylists.
	for( const auto polylist : m_polylist )
	{
		unify::Color diffuse = unify::ColorWhite();
		const NewParam * sampler2DParam = 0;
		const NewParam * surfaceParam = 0;
		
		const Effect * effect = nullptr;
		if( technique )
		{
			const std::string target = technique->GetInstanceMaterial( polylist->GetMaterial() ).GetTarget();
			const Material * material = GetDocument().GetLibraryMaterials().Find( target );
			std::string effectURL = material->GetInstanceEffect().GetURL();
			effect = GetDocument().GetLibraryEffects().Find( effectURL );
		}

		const Shading * shading = effect ? &effect->GetProfileCOMMON()->GetTechnique().GetShading() : nullptr;
		me::render::Effect::ptr primitiveEffectBase = GetDocument().GetEffect( effect );
		me::render::Effect::ptr myEffect( new me::render::Effect() );
		*myEffect = *primitiveEffectBase; // Copy.
		myEffect->ClearTextures(); // Clear textures, as we don't want the default texture that might have come with the effect.

		if( shading )
		{
			if( shading->GetDiffuse().GetType() == Shading::Property::ColorType )
			{
				diffuse = unify::Color( shading->GetDiffuse().GetColor() );
				myEffect->SetTexture( 0, me::render::ITexture::ptr() ); // Unset texture.
			}
			else // Is texture...
			{
				sampler2DParam = effect->GetProfileCOMMON()->FindNewParam( shading->GetDiffuse().GetTexture() );
				surfaceParam = effect->GetProfileCOMMON()->FindNewParam( sampler2DParam->GetSampler2D().source );
				const dae::Image * image = GetDocument().GetLibraryImages().Find( surfaceParam->GetSurface().init_from );
				me::render::ITexture::ptr texture( image->GetTexture() );
				myEffect->SetTexture( 0, texture );
			}
		}
		else
		{
			diffuse = unify::Color( unify::ColorGrey( 155 ) );
			myEffect->SetTexture( 0, me::render::ITexture::ptr() ); // Unset texture.
		}

		// Determine number of contributing inputs...
		// This is the mapping of components for each vertex (semantic and source).
		std::list< ContributingInput > ciList;
		size_t pStride = 1;
		for( auto && input : polylist->GetInput() )
		{
			GetSources( ciList, input.get(), 0, pStride );
		}
		
		// Create our primitive list...
		size_t numberOfVertices = polylist->GetP().size() / pStride;

		render::BufferSet & set = accumulatedPL.AddBufferSet();

		const render::VertexDeclaration::ptr vd = myEffect->GetVertexShader()->GetVertexDeclaration();
		unsigned short stream = 0;

		render::VertexElement positionE = render::CommonVertexElement::Position( stream );
		render::VertexElement normalE = render::CommonVertexElement::Normal( stream );
		render::VertexElement diffuseE = render::CommonVertexElement::Diffuse( stream );
		render::VertexElement specularE = render::CommonVertexElement::Specular( stream );
		render::VertexElement texE = render::CommonVertexElement::TexCoords( stream, 0 );
		render::VertexElement boneIndicesE = render::CommonVertexElement::Generic( stream, 1, me::render::ElementFormat::Int4 );
		render::VertexElement boneWeightsE = render::CommonVertexElement::Generic( stream, 2, me::render::ElementFormat::Float4 );

		std::shared_ptr< unsigned char > vertices( new unsigned char[ vd->GetSizeInBytes( 0 ) * numberOfVertices ] );
		unify::DataLock lock( vertices.get(), vd->GetSizeInBytes( 0 ), numberOfVertices, false, 0 );

		unify::BBox< float > bbox;

		// Vertices are created by joining a mapping of different (typically smaller sets) of components.
		size_t pHead = 0;
		size_t v_consumed = 0;
		for ( size_t vertexIndex = 0; vertexIndex < numberOfVertices; ++vertexIndex )
		{
			// Loop through all contributing inputs for each vertex, and joing values into the vertex...
			for( auto && ci : ciList )
			{
				size_t indexIntoP = pHead + ci.offset;
				size_t indexOfDAEVertex = polylist->GetP()[ indexIntoP ];

				const std::string metaType = ci.input->GetSemantic(); // Type of data, meta as it's an assumption.
				const std::vector< float > & floats = ci.source->GetFloatArray().GetArrayContents();
				size_t offsetOfFloats = indexOfDAEVertex * ci.input->GetStride();

				if ( unify::StringIs( metaType, "POSITION" ) || unify::StringIs( metaType, "VERTEX" ) )
				{
					unify::V3< float > val{
						floats[offsetOfFloats + 0], floats[offsetOfFloats + 1], floats[offsetOfFloats + 2] 
					};
					val = matrix.TransformCoord( val );
					bbox += val;
					WriteVertex( *vd, lock, vertexIndex, positionE, val );
					WriteVertex( *vd, lock, vertexIndex, diffuseE, diffuse );

					// Handle skinning with position.
					if( skin )
					{
						const auto & joints = skin->GetSource( "Controller-joints" )->GetNameArray();
						const auto & weights = skin->GetSource( "Controller-weights" )->GetFloatArray();

						unify::V4< int > boneIndices(-1);
						unify::V4< float > boneWeights;
						std::vector< VertexWeights::JointWeight > v_jw = skin->GetVertexWeights().GetVExpanded()[indexOfDAEVertex];

						for( size_t b = 0; b < v_jw.size(); b++ )
						{
							VertexWeights::JointWeight & jw = v_jw[b];

							if( jw.joint == -1 )
							{
								boneIndices[b] = -1;
							}
							else
							{
								std::string jointName = joints.GetArrayContents()[jw.joint];
								boneIndices[b] = (int)skeleton->FindJointIndex( jointName );
							}

							float weight = weights.GetArrayContents()[jw.weight];

							boneWeights[b] = weight;
						}

						// Write bone information to vertex...
						WriteVertex( *vd, lock, vertexIndex, boneIndicesE, boneIndices );
						WriteVertex( *vd, lock, vertexIndex, boneWeightsE, boneWeights );
					}
				}
				else if ( unify::StringIs( metaType, "NORMAL" ) )
				{
					unify::V3< float > val( floats[ offsetOfFloats + 0 ], floats[ offsetOfFloats + 1 ], floats[ offsetOfFloats + 2 ] );
					WriteVertex( *vd, lock, vertexIndex, normalE, val );
				}
				else if ( unify::StringIs( metaType, "TEXCOORD" ) )
				{
					WriteVertex( *vd, lock, vertexIndex, texE, unify::TexCoords( floats[ offsetOfFloats + 0 ], floats[ offsetOfFloats + 1 ] * -1.0f ) );
				}
			}

			pHead += pStride;
		}


		struct VT
		{
			unify::V3< float > p;
			unsigned int d;
		};

		VT * vt = (VT*)lock.GetData();

		set.AddVertexBuffer( { myEffect->GetVertexShader()->GetVertexDeclaration(), { { numberOfVertices, vertices.get() } }, render::BufferUsage::Dynamic, bbox } );

		
		switch( polylist->GetType() )
		{
		case Polylist::PolylistType:
		{
			size_t numberOfIndices = 0;
			for( size_t vci = 0; vci < polylist->GetVCount().size(); ++vci )
			{
				size_t vc = polylist->GetVCount()[ vci ];
				numberOfIndices += ( vc - 2 ) * 3;
			}

			std::vector< render::Index32 > indices( numberOfIndices );
			size_t vertexHead = 0; // Tracks the first vertex, increases by vc each iteration.
			size_t index = 0;
			for( size_t vci = 0; vci < polylist->GetVCount().size(); ++vci )
			{
				size_t vc = polylist->GetVCount()[ vci ];
				for( size_t indexOffset = 0; indexOffset < vc - 2; ++indexOffset )
				{
					indices[ index++ ] = vertexHead + indexOffset;
					indices[ index++ ] = vertexHead + indexOffset + 1;
					indices[ index++ ] = vertexHead + vc - 1;
				}
				vertexHead += vc;
			}

			set.AddIndexBuffer( { { { numberOfIndices, &indices[0] } }, render::BufferUsage::Staging } );

			set.AddMethod( render::RenderMethod::CreateTriangleListIndexed( numberOfVertices, numberOfIndices, 0, 0, myEffect ) );
		}
		break;

		case Polylist::TrianglesType:
		{
			set.AddMethod( render::RenderMethod::CreateTriangleList( 0, numberOfVertices / 3, myEffect ) );
		}
		break;

		case Polylist::LinesType:
		{
			set.AddMethod( render::RenderMethod::CreateLineList( 0, numberOfVertices / 2, myEffect ) );
		}
		break;
		}
	}
}