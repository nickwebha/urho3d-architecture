#pragma once

#include <Urho3D/Urho3DAll.h>

class BaseScreen : public Urho3D::Object {
	URHO3D_OBJECT( BaseScreen, Urho3D::Object );

	public:
		explicit BaseScreen( Urho3D::Context* context ) : Urho3D::Object( context ) {};

		virtual void Start( void );
		virtual void Stop( void );
		virtual void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
