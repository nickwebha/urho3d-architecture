#include <worldUI.hpp>

void WorldUI::HandleCloseButtonPressed( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	this->SetMenuOpen( false );
};

void WorldUI::HandleButtonPressed( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	this->GetSubsystem< Urho3D::Engine >()->Exit();
};

void WorldUI::Start( void ) {
	auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();
	auto* style = cache->GetResource< Urho3D::XMLFile >( "UI/DefaultStyle.xml" );

	auto* ui = this->GetSubsystem< Urho3D::UI >();
	this->uiRoot_ = ui->GetRoot();

	this->uiRoot_->SetDefaultStyle( style );
	this->window_ = new Urho3D::Window( this->GetContext() );

	this->uiRoot_->AddChild( this->window_ );

	this->window_->SetMinWidth( 384 );
	this->window_->SetLayout( Urho3D::LM_VERTICAL, 6, Urho3D::IntRect( 6, 6, 6, 6 ) );
	this->window_->SetAlignment( Urho3D::HA_CENTER, Urho3D::VA_CENTER );

	auto* titleBar = new Urho3D::UIElement( this->GetContext() );
	titleBar->SetMinSize( 0, 24 );
	titleBar->SetVerticalAlignment( Urho3D::VA_TOP );
	titleBar->SetLayoutMode( Urho3D::LM_HORIZONTAL );

	auto* windowTitle = new Urho3D::Text( this->GetContext() );
	windowTitle->SetText( "Exit?" );

	auto* buttonClose = new Urho3D::Button( this->GetContext() );

	titleBar->AddChild( windowTitle );
	titleBar->AddChild( buttonClose );

	this->window_->AddChild( titleBar );

	this->window_->SetStyleAuto();
	windowTitle->SetStyleAuto();
	buttonClose->SetStyle( "CloseButton" );

	auto* button = new Urho3D::Button( this->GetContext() );
	button->SetMinHeight( 24 );

	auto* buttonText = button->CreateChild< Urho3D::Text >();
	buttonText->SetFont( cache->GetResource< Urho3D::Font >( "Fonts/BlueHighway.ttf" ), 14 );
	buttonText->SetAlignment( Urho3D::HA_CENTER, Urho3D::VA_CENTER );
	buttonText->SetText( "Exit" );

	this->window_->AddChild( button );

	button->SetStyleAuto();

	this->SetMenuOpen( false );

	this->SubscribeToEvent( buttonClose, Urho3D::E_RELEASED, URHO3D_HANDLER( WorldUI, HandleCloseButtonPressed ) );
	this->SubscribeToEvent( button, Urho3D::E_RELEASED, URHO3D_HANDLER( WorldUI, HandleButtonPressed ) );
};

void WorldUI::Stop( void ) {
	this->UnsubscribeFromEvent( Urho3D::E_UIMOUSECLICK );
	this->UnsubscribeFromEvent( Urho3D::E_RELEASED );
};

void WorldUI::SetMenuOpen( bool enable ) {
	this->menuOpened_ = enable;

	this->window_->SetVisible( enable );

	this->GetSubsystem< Urho3D::Input >()->SetMouseVisible( enable );
};

bool WorldUI::GetMenuOpen( void ) {
	return this->menuOpened_;
};
