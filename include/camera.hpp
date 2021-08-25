#pragma once

#include <iostream>

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "level.hpp"

class Camera : public Urho3D::Object {
	URHO3D_OBJECT( Camera, Urho3D::Object );

	private:
		Urho3D::SharedPtr< Urho3D::Node > cameraNode_;

	public:
		explicit Camera( Urho3D::Context* context ) : Urho3D::Object( context ) {};

		void Start( void );

		Urho3D::SharedPtr< Urho3D::Node > getCamera( void );

		void rotateCamera( const float, const float );
		void moveCamera( const Urho3D::Vector3& );
};
