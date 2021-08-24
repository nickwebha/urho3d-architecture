#pragma once

#include "constants.hpp"
#include "baseScreen.hpp"

class Loading : public BaseScreen {
	private:
		Urho3D::SharedPtr< Urho3D::Sprite > sprite_;

		void preload( void );

	public:
		using BaseScreen::BaseScreen;

		void Start( void );
		void Stop( void );
		void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
