#pragma once

#include <Urho3D/Urho3DAll.h>

class WorldUI : public Urho3D::Object {
	URHO3D_OBJECT( WorldUI, Urho3D::Object );

	private:
		Urho3D::SharedPtr< Urho3D::UIElement > uiRoot_;
		Urho3D::SharedPtr< Urho3D::Window > window_;

		bool menuOpened_;

		void HandleCloseButtonPressed( Urho3D::StringHash, Urho3D::VariantMap& );
		void HandleButtonPressed( Urho3D::StringHash, Urho3D::VariantMap& );
		void HandleControlClicked( Urho3D::StringHash, Urho3D::VariantMap& );
		void HandleKeyDown( Urho3D::StringHash, Urho3D::VariantMap& );

	public:
		explicit WorldUI( Urho3D::Context* context ) : Urho3D::Object( context ) {
			this->menuOpened_ = false;
		};

		void Start( void );
		void Stop( void );

		void SetMenuOpen( bool );

		bool GetMenuOpen( void );
};
