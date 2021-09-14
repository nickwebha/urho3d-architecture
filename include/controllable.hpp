#pragma once

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "level.hpp"
#include "objectMovement.hpp"

class Controllable : public Urho3D::Object {
	URHO3D_OBJECT( Controllable, Urho3D::Object );

	private:
		Urho3D::SharedPtr< Urho3D::Node > controllable_;

		void HandleObjectCollisionStart( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData );

	public:
		explicit Controllable( Urho3D::Context* context ) : Urho3D::Object( context ) {};

		void Start( void );

		Urho3D::Node* GetControllable( void );
};
