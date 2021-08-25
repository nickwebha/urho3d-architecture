#include <logo.hpp>

void Logo::Start( void ) {
	this->timeStart_ = SECONDS_NOW;

	auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();

	auto* ui = this->GetSubsystem< Urho3D::UI >();
	this->sprite_ = ui->GetRoot()->CreateChild< Urho3D::Sprite >();
	Urho3D::SharedPtr< Urho3D::Texture2D > texture = cache->GetTempResource< Urho3D::Texture2D >( "Textures/FishBoneLogo.png" );
	if ( texture == NULL )
		Urho3D::ErrorExit();

	this->sprite_->SetTexture( texture );

	const short int textureWidth = texture->GetWidth();
	const short int textureHeight = texture->GetHeight();

	auto* graphics = this->GetSubsystem< Urho3D::Graphics >();

	this->sprite_->SetSize( textureWidth, textureHeight );
	this->sprite_->SetPosition( graphics->GetWidth() / 2 - textureWidth / 2, graphics->GetHeight() / 2 - textureHeight / 2 );
};

void Logo::Stop( void ) {
	this->sprite_->Remove();
};

void Logo::Update( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	const std::size_t now = SECONDS_NOW;
	if ( now >= this->timeStart_ + LOGO_TIMEOUT ) {
		Urho3D::VariantMap data;
		data[ "Screen" ] = Urho3D::String( "Loading" );
		SendEvent( "SwitchScreen", data );
	}
};
