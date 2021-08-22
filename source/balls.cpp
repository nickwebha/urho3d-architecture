#include <balls.hpp>

void Balls::Start( void ) {
	auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();
	auto* level = this->GetSubsystem< Level >();

	for ( short int i = 0 ; i < BALLS_COUNT ; i++ ) {
		this->balls_[ i ] = level->getScene()->CreateChild( "Ball" );
		const auto& ball = this->balls_[ i ];

		Urho3D::Vector3 position( Urho3D::Random( -100, 100 + 1 ), 0.0f, Urho3D::Random( -100, 100 + 1 ) );
		position.y_ = level->getTerrain()->GetComponent< Urho3D::Terrain >()->GetHeight( position ) + 10.0f;
		ball->SetPosition( position );
		ball->SetScale( Urho3D::Vector3( BALLS_SIZE, BALLS_SIZE, BALLS_SIZE ) );

		auto* object = ball->CreateComponent< Urho3D::StaticModel >();
		object->SetModel( cache->GetResource< Urho3D::Model >( "Models/Sphere.mdl" ) );
		object->SetMaterial( cache->GetResource< Urho3D::Material >( "Materials/Stone.xml" ) );
		object->SetCastShadows( true );

		auto* rigidBody = ball->CreateComponent< Urho3D::RigidBody >();
		rigidBody->SetMass( 1.0f );
		rigidBody->SetFriction( 0.25f );
		rigidBody->SetCollisionLayerAndMask( LayerFlagsBalls, LayerFlagsTerrain | LayerFlagsBalls );

		auto* collisionShape = ball->CreateComponent< Urho3D::CollisionShape >();
		collisionShape->SetSphere( 1 );
	}
};
