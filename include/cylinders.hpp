#pragma once

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "level.hpp"

class Cylinders : public Urho3D::Object {
	URHO3D_OBJECT( Cylinders, Urho3D::Object );

	private:
		Urho3D::SharedPtr< Urho3D::Node > cylinders_[ CYLINDERS_COUNT ];

		void HandleObjectCollisionStart( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData );

	public:
		explicit Cylinders( Urho3D::Context* context ) : Urho3D::Object( context ) {};

		void Start( void );
};
