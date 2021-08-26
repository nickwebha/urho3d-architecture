#pragma once

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "level.hpp"
#include "playerComponent.hpp"

class Player : public Urho3D::Object {
	URHO3D_OBJECT( Player, Urho3D::Object );

	private:
		Urho3D::SharedPtr< Urho3D::Node > player_;

		void HandleObjectCollisionStart( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData );

	public:
		explicit Player( Urho3D::Context* context ) : Urho3D::Object( context ) {};

		void Start( void );

		Urho3D::Node* GetPlayer( void );
};
