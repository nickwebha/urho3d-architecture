#pragma once

#include <iostream>

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "level.hpp"

class Balls : public Urho3D::Component {
	private:
		URHO3D_OBJECT( Balls, Urho3D::Component );

		Urho3D::SharedPtr< Urho3D::Node > balls_[ BALLS_COUNT ];

	public:
		explicit Balls( Urho3D::Context* context ) : Urho3D::Component( context ) {};

		void Start( void );
};
