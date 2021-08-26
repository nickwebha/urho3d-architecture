#pragma once

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"

class ObjectMovement : public Urho3D::Component {
	public:
		ObjectMovement( Urho3D::Context* context ) : Urho3D::Component( context ) {};

		void MoveX( const float );
		void MoveZ( const float );
};
