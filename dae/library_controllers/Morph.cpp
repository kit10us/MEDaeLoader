#include <dae/library_controllers/Morph.h>

using namespace dae;

Morph::Morph( IDocument & document, const qxml::Element * node )
	: DocumentNode( document, node )
	, m_source( node->GetAttributeElse( "source", std::string() ) )
{
	/*
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
	if ( childNode->HasElements( "convex_mesh" ) )
	{
	throw Exception_NotSupported( "geometry.convex_mesh" );
	}
	else if ( childNode->IsTagName( "mesh" ) )
	{
	m_meshSource = MeshSource::Mesh;
	m_mesh.reset( new Mesh( GetDocument(), childNode ) );
	}
	else if ( childNode->HasElements( "spline" ) )
	{
	throw Exception_NotSupported( "geometry.spline" );
	}
	if ( childNode->HasElements( "brep" ) )
	{
	throw Exception_NotSupported( "geometry.brep" );
	}
	}
	*/
}

std::string Morph::GetSource() const
{
	return m_source;
}
