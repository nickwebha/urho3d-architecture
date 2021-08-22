#pragma once

#include <Urho3D/Urho3DAll.h>

class Base : public Urho3D::Object {
	protected:
		URHO3D_OBJECT( Base, Urho3D::Object );

	public:
		explicit Base( Urho3D::Context* context ) : Urho3D::Object( context ) {};

		virtual void Start( void );
		virtual void Stop( void );
		virtual void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
