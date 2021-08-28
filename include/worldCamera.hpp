#pragma once

#include <iostream>

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "level.hpp"

class WorldCamera : public Urho3D::Object {
	URHO3D_OBJECT( WorldCamera, Urho3D::Object );

	private:
		Urho3D::SharedPtr< Urho3D::Node > cameraNode_;

	public:
		explicit WorldCamera( Urho3D::Context* context ) : Urho3D::Object( context ) {};

		void Start( void );
		void Update( Urho3D::StringHash, Urho3D::VariantMap& );

		Urho3D::SharedPtr< Urho3D::Node > getCamera( void );

		void rotate( const float, const float );
		void move( const Urho3D::Vector3& );

		float getYaw( void );
		float getPitch( void );
};
