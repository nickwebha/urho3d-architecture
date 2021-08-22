#pragma once

#include <memory>
#include <chrono>
#include <string>
#include <sstream>

#ifdef __RELEASE__
	#include <vector>
#endif

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"
#include "base.hpp"
#include "logo.hpp"
#include "loading.hpp"
#include "world.hpp"

class Game : public Urho3D::Application {
	private:
		std::unique_ptr< Base > base_;

		#ifdef __DEBUG__
			int framecount_;
			float time_;

			Urho3D::SharedPtr< Urho3D::Text > text_;
		#endif

		void SwitchScreen( Urho3D::StringHash, Urho3D::VariantMap& );

	public:
		Game( Urho3D::Context* context ) : Urho3D::Application( context ) {
			#ifdef __EMSCRIPTEN__
				EM_ASM( {
					const element = document.getElementById( "loading" );

					element.parentNode.removeChild( element );
				} );
			#endif
		};

		void Setup( void );
		void Start( void );
		void Stop( void );
		void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
