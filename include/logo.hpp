#pragma once

#include <chrono>

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "base.hpp"

class Logo : public Base {
	private:
		Urho3D::SharedPtr< Urho3D::Sprite > sprite_;

		std::size_t timeStart_;

	public:
		using Base::Base;

		void Start( void );
		void Stop( void );
		void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
