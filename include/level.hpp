#pragma once

#include <iostream>

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"

class Level : public Urho3D::Object {
	URHO3D_OBJECT( Level, Urho3D::Object );

	private:
		#ifdef __DEBUG__
			bool drawDebug_;

			void HandlePostRenderUpdate( Urho3D::StringHash, Urho3D::VariantMap& );
		#endif

		Urho3D::SharedPtr< Urho3D::Scene > scene_;
		Urho3D::SharedPtr< Urho3D::Node > terrainNode_;

		void DrawLogo( void );

	public:
		explicit Level( Urho3D::Context* context ) : Urho3D::Object( context ) {
			#ifdef __DEBUG__
				this->drawDebug_ = false;
			#endif
		};

		void Start( void );
		void Stop( void );

		#ifdef __DEBUG__
			void setDebug( const bool );
			bool getDebug( void );
		#endif

		Urho3D::SharedPtr< Urho3D::Scene > getScene( void );
		Urho3D::SharedPtr< Urho3D::Node > getTerrain( void );
};
