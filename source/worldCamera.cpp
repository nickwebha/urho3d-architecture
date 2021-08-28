#include <worldCamera.hpp>

void WorldCamera::Start( void ) {
	this->cameraNode_ = new Urho3D::Node( this->GetContext() );
	this->cameraNode_->SetPosition( Urho3D::Vector3( 0.0f, 500.0f, -150.0f ) );
	auto* camera = this->cameraNode_->CreateComponent< Urho3D::Camera >();
	camera->SetFarClip( 1000.0f );

	auto* level = this->GetSubsystem< Level >();

	auto* renderer = this->GetSubsystem< Urho3D::Renderer >();
	Urho3D::SharedPtr< Urho3D::Viewport > viewport( new Urho3D::Viewport( this->GetContext(), level->getScene(), camera ) );
	renderer->SetViewport( 0, viewport );
};

void WorldCamera::Update( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	this->cameraNode_->LookAt( eventData[ "position" ].GetVector3() );
};

Urho3D::SharedPtr< Urho3D::Node > WorldCamera::getCamera( void ) {
	return this->cameraNode_;
};

void WorldCamera::rotate( const float pitch, const float yaw ) {
	this->cameraNode_->SetRotation( Urho3D::Quaternion( pitch, yaw, 0.0f ) );
};

void WorldCamera::move( const Urho3D::Vector3& vector3 ) {
	this->cameraNode_->Translate( vector3 );
};

float WorldCamera::getYaw( void ) {
	return this->cameraNode_->GetRotation().YawAngle();
};

float WorldCamera::getPitch( void ) {
	return this->cameraNode_->GetRotation().PitchAngle();
};
