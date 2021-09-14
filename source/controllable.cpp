#include <controllable.hpp>

void Controllable::HandleObjectCollisionStart( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	auto* rigidBody1 = static_cast< Urho3D::RigidBody* >( eventData[ Urho3D::NodeCollisionStart::P_BODY ].GetPtr() );
	auto* node1 = rigidBody1->GetNode();
	const auto name1 = node1->GetName();

	auto* rigidBody2 = static_cast< Urho3D::RigidBody* >( eventData[ Urho3D::NodeCollisionStart::P_OTHERBODY ].GetPtr() );
	auto* node2 = rigidBody2->GetNode();
	const auto name2 = node2->GetName();

	if ( name2 == Urho3D::String( "Cylinder" ) ) {
		auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();

		auto* emitter = node1->CreateChild();
		emitter->SetWorldPosition( node1->GetWorldPosition() );

		auto* particleEmitter = emitter->CreateComponent< Urho3D::ParticleEmitter >();
		particleEmitter->SetEffect( cache->GetResource< Urho3D::ParticleEffect >( "Particle/Dust.xml" ) );
		particleEmitter->SetNumParticles( 1 );
		particleEmitter->SetEmitting( true );
		particleEmitter->SetAutoRemoveMode( Urho3D::REMOVE_NODE );
	}
};

void Controllable::Start( void ) {
	auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();
	auto* level = this->GetSubsystem< Level >();

	this->controllable_ = level->getScene()->CreateChild( "Controllable" );

	Urho3D::Vector3 position( 0.0f, 0.0f, -150.0f );
	position.y_ = level->getTerrain()->GetComponent< Urho3D::Terrain >()->GetHeight( position ) + CONTROLLABLE_SIZE / 2;
	this->controllable_->SetPosition( position );
	this->controllable_->SetScale( Urho3D::Vector3( CONTROLLABLE_SIZE, CONTROLLABLE_SIZE, CONTROLLABLE_SIZE ) );

	auto* object = this->controllable_->CreateComponent< Urho3D::StaticModel >();
	object->SetModel( cache->GetResource< Urho3D::Model >( "Models/Sphere.mdl" ) );
	object->SetMaterial( cache->GetResource< Urho3D::Material >( "Materials/Stone.xml" ) );
	object->SetCastShadows( true );

	auto* rigidBody = this->controllable_->CreateComponent< Urho3D::RigidBody >();
	rigidBody->SetMass( 5.0f );
	rigidBody->SetFriction( 1.0f );
	rigidBody->SetLinearDamping( 0.25f );
	rigidBody->SetCollisionLayerAndMask( LayerFlagsControllable, LayerFlagsTerrain | LayerFlagsCylinders );

	auto* collisionShape = this->controllable_->CreateComponent< Urho3D::CollisionShape >();
	collisionShape->SetSphere( 1 );

	this->controllable_->CreateComponent< ObjectMovement >();

	this->SubscribeToEvent( this->controllable_, Urho3D::E_NODECOLLISIONSTART, URHO3D_HANDLER( Controllable, HandleObjectCollisionStart ) );
};

Urho3D::Node* Controllable::GetControllable( void ) {
	return this->controllable_;
};
