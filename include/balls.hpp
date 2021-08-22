#pragma once

#include <iostream>

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "level.hpp"

class Balls : public Urho3D::Component {
	private:
		Urho3D::SharedPtr< Urho3D::Node > balls_[ BALLS_COUNT ];

		void HandleObjectCollisionStart( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData );

	public:
		explicit Balls( Urho3D::Context* context ) : Urho3D::Component( context ) {};

		virtual void Start( void );
};
