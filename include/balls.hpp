#pragma once

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "level.hpp"

class Balls : public Urho3D::Object {
	URHO3D_OBJECT( Balls, Urho3D::Component );

	private:
		Urho3D::SharedPtr< Urho3D::Node > balls_[ BALLS_COUNT ];

		void HandleObjectCollisionStart( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData );

	public:
		explicit Balls( Urho3D::Context* context ) : Urho3D::Object( context ) {};

		void Start( void );
};
