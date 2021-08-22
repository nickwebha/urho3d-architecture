#pragma once

#include <iostream>

#include <Urho3D/Urho3DAll.h>

#include "constants.hpp"

class Level : public Urho3D::Component {
	private:
		URHO3D_OBJECT( Level, Urho3D::Component );

		#ifdef __DEBUG__
			bool drawDebug_;

			void HandlePostRenderUpdate( Urho3D::StringHash, Urho3D::VariantMap& );
		#endif

		Urho3D::SharedPtr< Urho3D::Scene > scene_;
		Urho3D::SharedPtr< Urho3D::Node > cameraNode_;
		Urho3D::SharedPtr< Urho3D::Node > terrainNode_;

	public:
		explicit Level( Urho3D::Context* context ) : Urho3D::Component( context ) {
			#ifdef __DEBUG__
				this->drawDebug_ = false;
			#endif
		};

		void Start( void );
		void Stop( void );
		void Update( Urho3D::StringHash, Urho3D::VariantMap& );

		#ifdef __DEBUG__
			void setDebug( const bool );
			bool getDebug( void );
		#endif

		Urho3D::SharedPtr< Urho3D::Scene > getScene( void );
		Urho3D::SharedPtr< Urho3D::Node > getCamera( void );
		Urho3D::SharedPtr< Urho3D::Node > getTerrain( void );

		void rotateCamera( const float, const float );
		void moveCamera( const Urho3D::Vector3& );
};
