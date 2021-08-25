#pragma once

#include <string>

#include "constants.hpp"
#include "baseScreen.hpp"

class Loading : public BaseScreen {
	private:
		Urho3D::SharedPtr< Urho3D::Sprite > sprite_;

		bool loaded_;
		std::size_t loadedCount_;

		void HandleLoadingEnd( Urho3D::StringHash, Urho3D::VariantMap& );

		template < class T >
		void preloadFile( const std::string );

		void preload( void );

	public:
		using BaseScreen::BaseScreen;

		void Start( void );
		void Stop( void );
		void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
