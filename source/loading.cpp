#include <loading.hpp>

void Loading::HandleLoadingEnd( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	if ( eventData[ Urho3D::ResourceBackgroundLoaded::P_SUCCESS ].GetBool() )
		this->loadedCount_--;
	else
		Urho3D::ErrorExit();

	if ( this->loadedCount_ == 0 )
		this->loaded_ = true;
};

template < class T >
void Loading::preloadFile( const std::string path ) {
	this->loadedCount_++;

	this->GetSubsystem< Urho3D::ResourceCache >()->BackgroundLoadResource< T >( path.c_str() );
};

void Loading::preload( void ) {
	this->preloadFile< Urho3D::Image >( "Textures/HeightMap.png" );
	this->preloadFile< Urho3D::Image >( "Textures/StoneDiffuse.dds" );
	this->preloadFile< Urho3D::Image >( "Textures/StoneNormal.dds" );
	this->preloadFile< Urho3D::Image >( "Textures/TerrainDetail1.png" );
	this->preloadFile< Urho3D::Image >( "Textures/TerrainDetail2.png" );
	this->preloadFile< Urho3D::Image >( "Textures/TerrainDetail3.png" );
	this->preloadFile< Urho3D::Image >( "Textures/TerrainWeights.png" );

	this->preloadFile< Urho3D::Sound >( "Sounds/Hit.ogg" );
};

void Loading::Start( void ) {
	this->loaded_ = false;
	this->loadedCount_ = 0;

	auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();

	auto* ui = this->GetSubsystem< Urho3D::UI >();
	this->sprite_ = ui->GetRoot()->CreateChild< Urho3D::Sprite >();
	Urho3D::SharedPtr< Urho3D::Texture2D > texture = cache->GetTempResource< Urho3D::Texture2D >( "Textures/Loading.png" );
	if ( texture == NULL )
		Urho3D::ErrorExit();

	this->sprite_->SetTexture( texture );

	const short int textureWidth = texture->GetWidth();
	const short int textureHeight = texture->GetHeight();

	auto* graphics = this->GetSubsystem< Urho3D::Graphics >();

	this->sprite_->SetSize( textureWidth, textureHeight );
	this->sprite_->SetPosition( graphics->GetWidth() / 2 - textureWidth / 2, graphics->GetHeight() / 2 - textureHeight / 2 );

	this->SubscribeToEvent( Urho3D::E_RESOURCEBACKGROUNDLOADED, URHO3D_HANDLER( Loading, HandleLoadingEnd ) );

	this->preload();
};

void Loading::Stop( void ) {
	this->sprite_->Remove();
};

void Loading::Update( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	if ( this->loaded_) {
		Urho3D::VariantMap data;
		data[ "Screen" ] = Urho3D::String( "World" );
		SendEvent( "SwitchScreen", data );
	}
};
