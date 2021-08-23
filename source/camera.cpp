#include <camera.hpp>

void Camera::Start( void ) {
	this->cameraNode_ = new Urho3D::Node( this->GetContext() );
	this->cameraNode_->SetTransform( Urho3D::Vector3( 0.0f, 250.0f, 0.0f ), Urho3D::Quaternion( 90.0f, 0.0f, 0.0f ) );
	auto* camera = this->cameraNode_->CreateComponent< Urho3D::Camera >();
	camera->SetFarClip( 1000.0f );

	auto* level = this->GetSubsystem< Level >();

	auto* renderer = this->GetSubsystem< Urho3D::Renderer >();
	Urho3D::SharedPtr< Urho3D::Viewport > viewport( new Urho3D::Viewport( this->GetContext(), level->getScene(), this->cameraNode_->GetComponent< Urho3D::Camera >() ) );
	renderer->SetViewport( 0, viewport );
};

Urho3D::SharedPtr< Urho3D::Node > Camera::getCamera( void ) {
	return this->cameraNode_;
};

void Camera::rotateCamera( const float pitch, const float yaw ) {
	this->cameraNode_->SetRotation( Urho3D::Quaternion( pitch, yaw, 0.0f ) );
};

void Camera::moveCamera( const Urho3D::Vector3& vector3 ) {
	this->cameraNode_->Translate( vector3 );
};
