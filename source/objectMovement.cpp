#include <objectMovement.hpp>

void ObjectMovement::MoveX( const float x ) {
	this->GetNode()->GetComponent< Urho3D::RigidBody >()->ApplyImpulse( Urho3D::Vector3( x * OBJECT_SPEED, 0, 0 ) );
};

void ObjectMovement::MoveZ( const float z ) {
	this->GetNode()->GetComponent< Urho3D::RigidBody >()->ApplyImpulse( Urho3D::Vector3( 0, 0, z * OBJECT_SPEED ) );
};
