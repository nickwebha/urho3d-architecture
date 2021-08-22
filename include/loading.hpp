#pragma once

#include "constants.hpp"
#include "base.hpp"

class Loading : public Base {
	private:
		Urho3D::SharedPtr< Urho3D::Sprite > sprite_;

	public:
		using Base::Base;

		void Start( void );
		void Stop( void );
		void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
