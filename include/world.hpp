#pragma once

#include <memory>
#include <iostream>

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "baseScreen.hpp"
#include "level.hpp"
#include "worldCamera.hpp"
#include "worldUI.hpp"
#include "controllable.hpp"
#include "objectMovement.hpp"
#include "cylinders.hpp"

class World : public BaseScreen {
	private:
		float yaw_;
		float pitch_;

		bool cameraFollowControllable_;

		Urho3D::SharedPtr< Urho3D::Node > controllable_;

		void GamePadConnected( Urho3D::StringHash, Urho3D::VariantMap& );
		void GamePadDisconnected( Urho3D::StringHash, Urho3D::VariantMap& );
		void GamePadButtonDown( Urho3D::StringHash, Urho3D::VariantMap& );
		void GamePadButtonUp( Urho3D::StringHash, Urho3D::VariantMap& );
		void GamePadAxisMove( Urho3D::StringHash, Urho3D::VariantMap& );
		void GamePadHatMove( Urho3D::StringHash, Urho3D::VariantMap& );

		void HandleKeyDown( Urho3D::StringHash, Urho3D::VariantMap& );
		void HandleKeyUp( Urho3D::StringHash, Urho3D::VariantMap& );

	public:
		using BaseScreen::BaseScreen;

		void Start( void );
		void Stop( void );
		void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
