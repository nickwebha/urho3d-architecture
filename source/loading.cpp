#include <loading.hpp>

void Loading::Start( void ) {
	auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();

	auto* ui = this->GetSubsystem< Urho3D::UI >();
	this->sprite_ = ui->GetRoot()->CreateChild< Urho3D::Sprite >();
	auto* texture = cache->GetResource< Urho3D::Texture2D >( "Textures/Loading.png" );	// TODO This should be a temporary resource.
	this->sprite_->SetTexture( texture );

	const short int textureWidth = texture->GetWidth();
	const short int textureHeight = texture->GetHeight();

	auto* graphics = this->GetSubsystem< Urho3D::Graphics >();

	this->sprite_->SetSize( textureWidth, textureHeight );
	this->sprite_->SetPosition( graphics->GetWidth() / 2 - textureWidth / 2, graphics->GetHeight() / 2 - textureHeight / 2 );

	// TODO Pre-load everything here.
};

void Loading::Stop( void ) {
	this->sprite_->Remove();
};

void Loading::Update( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	Urho3D::VariantMap data;
	data[ "Screen" ] = Urho3D::String( "World" );
	SendEvent( "SwitchScreen", data );
};
