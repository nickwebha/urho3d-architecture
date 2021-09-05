#include <game.hpp>

void Game::SwitchScreen( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	this->baseScreen_->Stop();

	if ( eventData[ "Screen" ] == Urho3D::String( "Logo" ) )
		this->baseScreen_ = std::make_unique< Logo >( this->GetContext() );
	else if ( eventData[ "Screen" ] == Urho3D::String( "Loading" ) )
		this->baseScreen_ = std::make_unique< Loading >( this->GetContext() );
	else if ( eventData[ "Screen" ] == Urho3D::String( "World" ) )
		this->baseScreen_ = std::make_unique< World >( this->GetContext() );

	this->baseScreen_->Start();
};

void Game::Setup( void ) {
	engineParameters_[ Urho3D::EP_LOG_NAME ] = "";
	engineParameters_[ Urho3D::EP_RESOURCE_PATHS ] = ASSETS_PATHS;
	engineParameters_[ Urho3D::EP_WINDOW_ICON ] = WINDOW_ICON;
	engineParameters_[ Urho3D::EP_WINDOW_WIDTH ] = SCREEN_WIDTH;
	engineParameters_[ Urho3D::EP_WINDOW_HEIGHT ] = SCREEN_HEIGHT;

	#ifdef __DEBUG__
		engineParameters_[ Urho3D::EP_FULL_SCREEN ] = false;

		#ifndef __EMSCRIPTEN__
			engineParameters_[ Urho3D::EP_WINDOW_RESIZABLE ] = true;
		#endif

		this->framecount_ = 0;
		this->time_ = 0;
	#elif __RELEASE__
		engineParameters_[ Urho3D::EP_FULL_SCREEN ] = true;

		this->GetSubsystem< Urho3D::Log >()->SetLevel( Urho3D::LOG_NONE );

		auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();
		for ( const auto& i : ASSETS_PATHS_PACKAGES )
			cache->AddPackageFile( i.c_str() );
	#else
		#error Must define either __DEBUG__ or __RELEASE__.
	#endif

	Urho3D::SetRandomSeed( SECONDS_NOW );
};

void Game::Start( void ) {
	this->GetSubsystem< Urho3D::Graphics >()->SetWindowTitle( WINDOW_TITLE );
	this->GetSubsystem< Urho3D::Engine >()->SetMinFps( WINDOW_FPS_MINIMUM );
	this->GetSubsystem< Urho3D::Engine >()->SetMaxFps( this->GetSubsystem< Urho3D::Graphics >()->GetRefreshRate() );
	this->GetSubsystem< Urho3D::Engine >()->SetMaxInactiveFps( WINDOW_FPS_INACTIVE );

	SubscribeToEvent( Urho3D::E_UPDATE, URHO3D_HANDLER( Game, Update ) );

	SubscribeToEvent( "SwitchScreen", URHO3D_HANDLER( Game, SwitchScreen ) );

	#ifdef __DEBUG__
		auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();

		this->text_ = new Urho3D::Text( this->context_ );
		this->text_->SetFont( cache->GetResource< Urho3D::Font >( "Fonts/Anonymous Pro.ttf" ), 24 );
		this->text_->SetColor( Urho3D::Color::WHITE );
		this->text_->SetHorizontalAlignment( Urho3D::HA_CENTER );
		this->text_->SetVerticalAlignment( Urho3D::VA_TOP );

		this->GetSubsystem< Urho3D::UI >()->GetRoot()->AddChild( this->text_ );
	#endif

	this->baseScreen_ = std::make_unique< BaseScreen >( this->context_ );

	Urho3D::VariantMap data;
	data[ "Screen" ] = Urho3D::String( "Logo" );
	SendEvent( "SwitchScreen", data );
};

void Game::Stop( void ) {
	this->baseScreen_->Stop();

	UnsubscribeFromEvent( "SwitchScreen" );

	UnsubscribeFromEvent( Urho3D::E_UPDATE );
};

void Game::Update( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	this->baseScreen_->Update( eventType, eventData );

	#ifdef __DEBUG__
		const float timeStep = eventData[ Urho3D::Update::P_TIMESTEP ].GetFloat();
		this->framecount_++;
		this->time_ += timeStep;

		if ( this->time_ >= 1 ) {
			std::string str;

			{
				std::ostringstream ss;
				ss << this->framecount_;
				std::string s( ss.str() );
				str.append( s.substr( 0, 6 ) );
			}

			str.append( " frames in " );

			{
				std::ostringstream ss;
				ss << this->time_;
				std::string s( ss.str() );
				str.append( s.substr( 0, 6 ) );
			}

			str.append( " seconds = " );

			{
				std::ostringstream ss;
				ss << static_cast< float >( this->framecount_ ) / this->time_;
				std::string s( ss.str() );
				str.append( s.substr( 0, 8 ) );
			}

			str.append( " FPS" );
			Urho3D::String s( str.c_str(), str.size() );
			this->text_->SetText( s );
			this->framecount_ = 0;
			this->time_ = 0;
		}
	#endif
};
