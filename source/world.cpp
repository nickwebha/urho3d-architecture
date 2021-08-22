#include <world.hpp>

void World::HandleKeyDown( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	std::cout << "Key Down: " << eventData[ Urho3D::KeyDown::P_KEY ].GetInt() << std::endl;

	if ( Urho3D::GetPlatform() != Urho3D::String( "Web" ) ) {
		const auto key = eventData[ Urho3D::KeyDown::P_KEY ].GetInt();
		if ( key == Urho3D::KEY_ESCAPE )
			this->GetSubsystem< Urho3D::Engine >()->Exit();
		#ifdef __DEBUG__
			else if ( key == Urho3D::KEY_SPACE )
				this->GetSubsystem< Level >()->setDebug( ! this->GetSubsystem< Level >()->getDebug() );
		#endif
	}
};

void World::HandleKeyUp( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	std::cout << "Key Up: " << eventData[ Urho3D::KeyUp::P_KEY ].GetInt() << std::endl;
};

void World::GamePadConnected( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	std::cout << "GamePad Connected: " << eventData[ Urho3D::JoystickConnected::P_JOYSTICKID ].GetInt() << std::endl;
};

void World::GamePadDisconnected( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	std::cout << "GamePad Disconnected: " << eventData[ Urho3D::JoystickDisconnected::P_JOYSTICKID ].GetInt() << std::endl;
};

void World::GamePadButtonDown( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	std::cout << "GamePad Button Down: " << eventData[ Urho3D::JoystickButtonDown::P_JOYSTICKID ].GetInt() << " " << eventData[ Urho3D::JoystickButtonUp::P_BUTTON ].GetInt() << std::endl;
};

void World::GamePadButtonUp( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	std::cout << "GamePad Button Up: " << eventData[ Urho3D::JoystickButtonUp::P_JOYSTICKID ].GetInt() << " " << eventData[ Urho3D::JoystickButtonUp::P_BUTTON ].GetInt() << std::endl;
};

void World::GamePadAxisMove( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	std::cout << "GamePad Axis Move: " << eventData[ Urho3D::JoystickAxisMove::P_JOYSTICKID ].GetInt() << " " << eventData[ Urho3D::JoystickAxisMove::P_AXIS ].GetInt() << " " << eventData[ Urho3D::JoystickAxisMove::P_POSITION ].GetFloat() << std::endl;
};

void World::GamePadHatMove( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	std::cout << "GamePad Hat Move: " << eventData[ Urho3D::JoystickHatMove::P_JOYSTICKID ].GetInt() << " " << eventData[ Urho3D::JoystickHatMove::P_HAT ].GetInt() << " " << eventData[ Urho3D::JoystickHatMove::P_POSITION ].GetInt() << std::endl;
};

void World::Start( void ) {
	this->yaw_ = 0;
	this->pitch_ = 90;

	this->GetContext()->RegisterSubsystem< Level >();
	this->GetSubsystem< Level >()->Start();

	this->GetContext()->RegisterSubsystem< Balls >();
	this->GetSubsystem< Balls >()->Start();

	SubscribeToEvent( Urho3D::E_KEYDOWN, URHO3D_HANDLER( World, HandleKeyDown ) );
	SubscribeToEvent( Urho3D::E_KEYUP, URHO3D_HANDLER( World, HandleKeyUp ) );
	SubscribeToEvent( Urho3D::E_JOYSTICKCONNECTED, URHO3D_HANDLER( World, GamePadConnected ) );
	SubscribeToEvent( Urho3D::E_JOYSTICKDISCONNECTED, URHO3D_HANDLER( World, GamePadDisconnected ) );
	SubscribeToEvent( Urho3D::E_JOYSTICKBUTTONDOWN, URHO3D_HANDLER( World, GamePadButtonDown ) );
	SubscribeToEvent( Urho3D::E_JOYSTICKBUTTONUP, URHO3D_HANDLER( World, GamePadButtonUp ) );
	SubscribeToEvent( Urho3D::E_JOYSTICKAXISMOVE, URHO3D_HANDLER( World, GamePadAxisMove ) );
	SubscribeToEvent( Urho3D::E_JOYSTICKHATMOVE, URHO3D_HANDLER( World, GamePadHatMove ) );
};

void World::Stop( void ) {
	UnsubscribeFromEvent( Urho3D::E_JOYSTICKHATMOVE );
	UnsubscribeFromEvent( Urho3D::E_JOYSTICKAXISMOVE );
	UnsubscribeFromEvent( Urho3D::E_JOYSTICKBUTTONUP );
	UnsubscribeFromEvent( Urho3D::E_JOYSTICKBUTTONDOWN );
	UnsubscribeFromEvent( Urho3D::E_JOYSTICKDISCONNECTED );
	UnsubscribeFromEvent( Urho3D::E_JOYSTICKCONNECTED );
	UnsubscribeFromEvent( Urho3D::E_KEYUP );
	UnsubscribeFromEvent( Urho3D::E_KEYDOWN );

	this->GetSubsystem< Level >()->Stop();
};

void World::Update( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	const float timeStep = eventData[ Urho3D::Update::P_TIMESTEP ].GetFloat();

	const auto* input = this->GetSubsystem< Urho3D::Input >();

	const auto mouseMove = input->GetMouseMove();
	this->yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
	this->pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
	this->pitch_ = Urho3D::Clamp( this->pitch_, -90.0f, 90.0f );

	auto* level = this->GetSubsystem< Level >();

	level->rotateCamera( this->pitch_, this->yaw_ );

	if ( input->GetKeyDown( Urho3D::KEY_W ) )
		level->moveCamera( Urho3D::Vector3::FORWARD * MOVE_SPEED * timeStep );
	if ( input->GetKeyDown( Urho3D::KEY_S ) )
		level->moveCamera( Urho3D::Vector3::BACK * MOVE_SPEED * timeStep );
	if ( input->GetKeyDown( Urho3D::KEY_A ) )
		level->moveCamera( Urho3D::Vector3::LEFT * MOVE_SPEED * timeStep );
	if ( input->GetKeyDown( Urho3D::KEY_D ) )
		level->moveCamera( Urho3D::Vector3::RIGHT * MOVE_SPEED * timeStep );

	level->Update( eventType, eventData );
};
