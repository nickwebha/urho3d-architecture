#include <base.hpp>

Urho3D::StringHash Base::GetType( void ) const {
	return "Base";
};

const Urho3D::String& Base::GetTypeName( void ) const {
	static Urho3D::String name( "Base" );

	return name;
};

const Urho3D::TypeInfo* Base::GetTypeInfo( void ) const {
	return GetTypeInfoStatic();
};

void Base::Start( void ) {};

void Base::Stop( void ) {};

void Base::Update( Urho3D::StringHash, Urho3D::VariantMap& ) {};
