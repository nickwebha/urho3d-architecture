#include <playerComponent.hpp>

void PlayerComponent::MoveX( const float x ) {
	// this->GetNode()->GetComponent< Urho3D::RigidBody >()->ApplyImpulse( Urho3D::Vector3( x * PLAYER_SPEED, 0, 0 ) );
};

void PlayerComponent::MoveZ( const float z ) {
	// this->GetNode()->GetComponent< Urho3D::RigidBody >()->ApplyImpulse( Urho3D::Vector3( 0, 0, z * PLAYER_SPEED ) );
};
