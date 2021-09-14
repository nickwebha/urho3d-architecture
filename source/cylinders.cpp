#include <cylinders.hpp>

void Cylinders::HandleObjectCollisionStart( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	auto* rigidBody1 = static_cast< Urho3D::RigidBody* >( eventData[ Urho3D::NodeCollisionStart::P_BODY ].GetPtr() );
	auto* node1 = rigidBody1->GetNode();
	const auto name1 = node1->GetName();

	auto* rigidBody2 = static_cast< Urho3D::RigidBody* >( eventData[ Urho3D::NodeCollisionStart::P_OTHERBODY ].GetPtr() );
	auto* node2 = rigidBody2->GetNode();
	const auto name2 = node2->GetName();

	if ( name2 == Urho3D::String( "Controllable" ) || name2 == Urho3D::String( "Cylinders" ) ) {
		auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();
		auto* level = this->GetSubsystem< Level >();

		auto* sound = cache->GetResource< Urho3D::Sound >( "Sounds/Hit.ogg" );
		auto* soundNode = level->getScene()->CreateChild();
		auto* soundSource = soundNode->CreateComponent< Urho3D::SoundSource >();
		soundSource->Play( sound );
		soundSource->SetGain( 0.1f );
		soundSource->SetAutoRemoveMode( Urho3D::REMOVE_NODE );
	}
};

void Cylinders::Start( void ) {
	auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();
	auto* level = this->GetSubsystem< Level >();

	for ( short int i = 0 ; i < CYLINDERS_COUNT ; i++ ) {
		this->cylinders_[ i ] = level->getScene()->CreateChild( "Cylinder" );
		const auto& ball = this->cylinders_[ i ];

		Urho3D::Vector3 position( Urho3D::Random( -100, 100 + 1 ), 0.0f, Urho3D::Random( -100, 100 + 1 ) );
		position.y_ = level->getTerrain()->GetComponent< Urho3D::Terrain >()->GetHeight( position ) + CYLINDERS_SIZE;
		ball->SetPosition( position );
		ball->SetScale( Urho3D::Vector3( CYLINDERS_SIZE, CYLINDERS_SIZE, CYLINDERS_SIZE ) );
		ball->SetRotation( Urho3D::Quaternion( Urho3D::Random( 0, 360 ), Urho3D::Random( 0, 360 ), Urho3D::Random( 0, 360 ) ) );

		auto* object = ball->CreateComponent< Urho3D::StaticModel >();
		object->SetModel( cache->GetResource< Urho3D::Model >( "Models/Cylinder.mdl" ) );
		object->SetMaterial( cache->GetResource< Urho3D::Material >( "Materials/Stone.xml" ) );
		object->SetCastShadows( true );

		auto* rigidBody = ball->CreateComponent< Urho3D::RigidBody >();
		rigidBody->SetMass( 1.0f );
		rigidBody->SetFriction( 0.25f );
		rigidBody->SetAngularDamping( 0.5f );
		rigidBody->SetCollisionLayerAndMask( LayerFlagsCylinders, LayerFlagsTerrain | LayerFlagsControllable | LayerFlagsCylinders );

		auto* collisionShape = ball->CreateComponent< Urho3D::CollisionShape >();
		collisionShape->SetCylinder( 1, 1 );

		this->SubscribeToEvent( ball, Urho3D::E_NODECOLLISIONSTART, URHO3D_HANDLER( Cylinders, HandleObjectCollisionStart ) );
	}
};
