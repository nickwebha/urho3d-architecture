#pragma once

#include <chrono>

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "baseScreen.hpp"

#define SECONDS_NOW	std::chrono::duration_cast< std::chrono::seconds >( std::chrono::system_clock::now().time_since_epoch() ).count()

class Logo : public BaseScreen {
	private:
		Urho3D::SharedPtr< Urho3D::Sprite > sprite_;

		std::size_t timeStart_;

	public:
		using BaseScreen::BaseScreen;

		void Start( void );
		void Stop( void );
		void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
