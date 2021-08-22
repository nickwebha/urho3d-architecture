#pragma once

#include <memory>
#include <iostream>

#include <Urho3D/Urho3DAll.h>

#include "base.hpp"
#include "level.hpp"
#include "balls.hpp"

#define MOVE_SPEED			100.0f
#define MOUSE_SENSITIVITY	0.1f

class World : public Base {
	private:
		float yaw_;
		float pitch_;

		void GamePadConnected( Urho3D::StringHash, Urho3D::VariantMap& );
		void GamePadDisconnected( Urho3D::StringHash, Urho3D::VariantMap& );
		void GamePadButtonDown( Urho3D::StringHash, Urho3D::VariantMap& );
		void GamePadButtonUp( Urho3D::StringHash, Urho3D::VariantMap& );
		void GamePadAxisMove( Urho3D::StringHash, Urho3D::VariantMap& );
		void GamePadHatMove( Urho3D::StringHash, Urho3D::VariantMap& );

		void HandleKeyDown( Urho3D::StringHash, Urho3D::VariantMap& );
		void HandleKeyUp( Urho3D::StringHash, Urho3D::VariantMap& );

	public:
		using Base::Base;

		void Start( void );
		void Stop( void );
		void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
