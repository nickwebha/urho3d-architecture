#include <player.hpp>

void Player::HandleObjectCollisionStart( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	auto* rigidBody1 = static_cast< Urho3D::RigidBody* >( eventData[ Urho3D::NodeCollisionStart::P_BODY ].GetPtr() );
	auto* node1 = rigidBody1->GetNode();
	const auto name1 = node1->GetName();

	auto* rigidBody2 = static_cast< Urho3D::RigidBody* >( eventData[ Urho3D::NodeCollisionStart::P_OTHERBODY ].GetPtr() );
	auto* node2 = rigidBody2->GetNode();
	const auto name2 = node2->GetName();

	if ( name2 == Urho3D::String( "Ball" ) ) {
		auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();

		auto* emitter = node1->CreateChild();
		emitter->SetWorldPosition( node1->GetWorldPosition() );

		auto* particleEmitter = emitter->CreateComponent< Urho3D::ParticleEmitter >();
		particleEmitter->SetEffect( cache->GetResource< Urho3D::ParticleEffect >( "Particle/Dust.xml" ) );
		particleEmitter->SetNumParticles( 1 );
		particleEmitter->SetEmitting( true );
	}
};

void Player::Start( void ) {
	auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();
	auto* level = this->GetSubsystem< Level >();

	this->player_ = level->getScene()->CreateChild( "Player" );

	Urho3D::Vector3 position( 0.0f, 0.0f, -200.0f );
	position.y_ = level->getTerrain()->GetComponent< Urho3D::Terrain >()->GetHeight( position ) + 10.0f;
	this->player_->SetPosition( position );
	this->player_->SetScale( Urho3D::Vector3( PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE ) );

	auto* object = this->player_->CreateComponent< Urho3D::StaticModel >();
	object->SetModel( cache->GetResource< Urho3D::Model >( "Models/Cylinder.mdl" ) );
	object->SetMaterial( cache->GetResource< Urho3D::Material >( "Materials/Stone.xml" ) );
	object->SetCastShadows( true );

	auto* rigidBody = this->player_->CreateComponent< Urho3D::RigidBody >();
	rigidBody->SetMass( 1.0f );
	rigidBody->SetFriction( 0.5f );
	rigidBody->SetLinearDamping( 0.25f );
	rigidBody->SetAngularDamping( 0.5f );
	rigidBody->SetCollisionLayerAndMask( LayerFlagsPlayer, LayerFlagsTerrain | LayerFlagsBalls );

	auto* collisionShape = this->player_->CreateComponent< Urho3D::CollisionShape >();
	collisionShape->SetCylinder( 1, 1 );

	SubscribeToEvent( this->player_, Urho3D::E_NODECOLLISIONSTART, URHO3D_HANDLER( Player, HandleObjectCollisionStart ) );
};