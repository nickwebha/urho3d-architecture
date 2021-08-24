#pragma once

#include <iostream>

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"

class PlayerComponent : public Urho3D::Component {
	public:
		PlayerComponent( Urho3D::Context* context ) : Urho3D::Component( context ) {};

		void MoveX( const float );
		void MoveZ( const float );
};
