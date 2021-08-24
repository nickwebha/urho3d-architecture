#pragma once

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "level.hpp"

class Player : public Urho3D::Component {
	URHO3D_OBJECT( Player, Urho3D::Component );

	private:
		Urho3D::SharedPtr< Urho3D::Node > player_;

		void HandleObjectCollisionStart( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData );

	public:
		explicit Player( Urho3D::Context* context ) : Urho3D::Component( context ) {};

		void Start( void );
};
