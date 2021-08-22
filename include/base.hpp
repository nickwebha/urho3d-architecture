#pragma once

#include <Urho3D/Urho3DAll.h>

class Base : public Urho3D::Object {
	public:
		explicit Base( Urho3D::Context* context ) : Urho3D::Object( context ) {};

		virtual Urho3D::StringHash GetType( void ) const;
		virtual const Urho3D::String& GetTypeName( void ) const;
		virtual const Urho3D::TypeInfo* GetTypeInfo( void ) const;

		virtual void Start( void );
		virtual void Stop( void );
		virtual void Update( Urho3D::StringHash, Urho3D::VariantMap& );
};
