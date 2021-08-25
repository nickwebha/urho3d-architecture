#pragma once

#include <iostream>

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "baseScreen.hpp"

class Loading : public BaseScreen {
	private:
		Urho3D::SharedPtr< Urho3D::Sprite > sprite_;

		bool loaded_;

		void HandleLoadingEnd( Urho3D::StringHash, Urho3D::VariantMap& );

		template < class T >
		void preloadFile( const Urho3D::String );

		void preload( void );

	public:
		using BaseScreen::BaseScreen;

		void Start( void );
		void Stop( void );
		void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
