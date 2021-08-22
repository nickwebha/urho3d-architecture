#include <balls.hpp>

void Balls::HandleObjectCollisionStart( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	auto* rigidBody1 = static_cast< Urho3D::RigidBody* >( eventData[ Urho3D::NodeCollisionStart::P_BODY ].GetPtr() );
	auto* node1 = rigidBody1->GetNode();
	const auto name1 = node1->GetName();

	auto* rigidBody2 = static_cast< Urho3D::RigidBody* >( eventData[ Urho3D::NodeCollisionStart::P_OTHERBODY ].GetPtr() );
	auto* node2 = rigidBody2->GetNode();
	const auto name2 = node2->GetName();

	if ( name2 == "Player" ) {
		UnsubscribeFromEvent( node1, Urho3D::E_NODECOLLISIONSTART );

		node1->Remove();
	}
};

void Balls::Start( void ) {
std::cout << "Balls" << std::endl;
	for ( short int i = 0 ; i < BALLS_COUNT ; i++ ) {
		auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();
		auto* level = this->GetSubsystem< Level >();

		this->balls_[ i ] = level->getScene()->CreateChild( "Ball" );
		const auto& ball = this->balls_[ i ];

		Urho3D::Vector3 position( Urho3D::Random( -50, 50 + 1 ), 0.0f, Urho3D::Random( -50, 50 + 1 ) );
		position.y_ = level->getTerrain()->GetComponent< Urho3D::Terrain >()->GetHeight( position ) + 10.0f;
		ball->SetPosition( position );
		ball->SetScale( Urho3D::Vector3( 10.0f, 10.0f, 10.0f ) );

		auto* object = ball->CreateComponent< Urho3D::StaticModel >();
		object->SetModel( cache->GetResource< Urho3D::Model >( "Models/Sphere.mdl" ) );
		object->SetMaterial( cache->GetResource< Urho3D::Material >( "Materials/Stone.xml" ) );
		object->SetCastShadows( true );

		auto* rigidBody = ball->CreateComponent< Urho3D::RigidBody >();
		rigidBody->SetMass( 1.0f );
		rigidBody->SetFriction( 0.1f );
		rigidBody->SetCollisionLayerAndMask( LayerFlagsBall, LayerFlagsTerrain | LayerFlagsPlayer );

		auto* collisionShape = ball->CreateComponent< Urho3D::CollisionShape >();
		collisionShape->SetSphere( 1, Urho3D::Vector3( 0, .5, 0 ) );

		SubscribeToEvent( ball, Urho3D::E_NODECOLLISIONSTART, URHO3D_HANDLER( Balls, HandleObjectCollisionStart ) );
	}
};
