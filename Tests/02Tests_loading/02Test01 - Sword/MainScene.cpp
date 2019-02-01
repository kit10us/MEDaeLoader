// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <MainScene.h>
#include <me/render/RenderMethod.h>
#include <me/render/VertexUtil.h>
#include <me/scene/SceneManager.h>
#include <me/object/Object.h>
#include <me/render/Mesh.h>
#include <sg/ShapeCreators.h>
#include <me/factory/PixelShaderFactories.h>
#include <me/factory/VertexShaderFactory.h>
#include <me/object/component/BBoxRendererComponent.h>
#include <me/scene/component/AutoBBoxSceneComponent.h>
#include <me/object/component/CameraComponent.h>

using namespace me;
using namespace render;

MainScene::MainScene( me::game::Game * gameInstance )
	:Scene( gameInstance, "main" )
{	
}

void MainScene::OnStart()
{
	using namespace unify;
	using namespace object;

	AddResources( unify::Path( "resources/Resources01.me_res" ) );

	// Add a camera...
	Object * camera = GetObjectAllocator()->NewObject( "camera" );
	camera->AddComponent( component::IObjectComponent::ptr( new component::CameraComponent() ) );
	auto * cameraComponent = polymorphic_downcast< component::CameraComponent * >( camera->GetComponent( "camera" ).get() );
	cameraComponent->SetProjection( MatrixPerspectiveFovLH( 3.141592653589f / 4.0f, 800/600, 1, 1000 ) );
	camera->GetFrame().SetPosition( { 0, 5, -7 } );
	camera->GetFrame().LookAt( { 0, 0, 0 } );

	{ // Sword
		Geometry::ptr meshASE{ GetAsset< render::Geometry >( "SwordASE" ) };
		PrimitiveList & plASE = ((Mesh*)meshASE.get())->GetPrimitiveList();
		auto object = GetObjectAllocator()->NewObject( "sword" );

		Matrix modelMatrix = MatrixIdentity();
		modelMatrix.Scale( 0.090f );
		modelMatrix.RotateAboutAxis( { -1.0f, 0.0f, 0.0f }, AngleInDegrees( 90 ) );
		modelMatrix.Translate( { 0, 1.0f, 0.0f } );

		AddGeometryComponent( object, meshASE, modelMatrix  );
		object->GetFrame().SetPosition( { 0, 0, 0 } );
		object->AddComponent( component::IObjectComponent::ptr( new object::component::BBoxRendererComponent( GetOS(), GetAsset< Effect >( "ColorSimple" ) ) ) );
	}
}

void MainScene::OnUpdate( const UpdateParams & params )
{
	using namespace object;

	// Use of camera controls to simplify camera movement...
	Object * camera = FindObject( "camera" );
	
	camera->GetFrame().Orbit( { 0, 0, 0 }, { 1, 0 }, unify::AngleInRadians( params.GetDelta().GetSeconds() ) );
	camera->GetFrame().LookAt( { 0, 0, 0 }, { 0, 1, 0 } );
}
