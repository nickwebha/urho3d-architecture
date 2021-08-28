#include <world.hpp>

void World::HandleKeyDown( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	std::cout << "Key Down: " << eventData[ Urho3D::KeyDown::P_KEY ].GetInt() << std::endl;

	const auto key = eventData[ Urho3D::KeyDown::P_KEY ].GetInt();
	if ( key == Urho3D::KEY_ESCAPE && Urho3D::GetPlatform() != Urho3D::String( "Web" ) )
		this->GetSubsystem< Urho3D::Engine >()->Exit();
	else if ( key == Urho3D::KEY_C )
		this->cameraFollowPlayer_ = ! this->cameraFollowPlayer_;
	#ifdef __DEBUG__
		else if ( key == Urho3D::KEY_SPACE ) {
			auto* level = this->GetSubsystem< Level >();

			level->setDebug( ! level->getDebug() );
		}
	#endif
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
	this->pitch_ = 75;

	this->cameraFollowPlayer_ = false;

	this->GetContext()->RegisterSubsystem< Level >();
	this->GetContext()->RegisterSubsystem< WorldCamera >();
	this->GetContext()->RegisterSubsystem< Player >();
	this->GetContext()->RegisterSubsystem< Cylinders >();

	this->GetContext()->RegisterFactory< ObjectMovement >();

	this->GetSubsystem< Level >()->Start();
	this->GetSubsystem< WorldCamera >()->Start();
	this->GetSubsystem< Player >()->Start();
	this->GetSubsystem< Cylinders >()->Start();

	this->player_ = this->GetSubsystem< Player >()->GetPlayer();

	this->SubscribeToEvent( Urho3D::E_KEYDOWN, URHO3D_HANDLER( World, HandleKeyDown ) );
	this->SubscribeToEvent( Urho3D::E_KEYUP, URHO3D_HANDLER( World, HandleKeyUp ) );
	this->SubscribeToEvent( Urho3D::E_JOYSTICKCONNECTED, URHO3D_HANDLER( World, GamePadConnected ) );
	this->SubscribeToEvent( Urho3D::E_JOYSTICKDISCONNECTED, URHO3D_HANDLER( World, GamePadDisconnected ) );
	this->SubscribeToEvent( Urho3D::E_JOYSTICKBUTTONDOWN, URHO3D_HANDLER( World, GamePadButtonDown ) );
	this->SubscribeToEvent( Urho3D::E_JOYSTICKBUTTONUP, URHO3D_HANDLER( World, GamePadButtonUp ) );
	this->SubscribeToEvent( Urho3D::E_JOYSTICKAXISMOVE, URHO3D_HANDLER( World, GamePadAxisMove ) );
	this->SubscribeToEvent( Urho3D::E_JOYSTICKHATMOVE, URHO3D_HANDLER( World, GamePadHatMove ) );
};

void World::Stop( void ) {
	this->UnsubscribeFromEvent( Urho3D::E_JOYSTICKHATMOVE );
	this->UnsubscribeFromEvent( Urho3D::E_JOYSTICKAXISMOVE );
	this->UnsubscribeFromEvent( Urho3D::E_JOYSTICKBUTTONUP );
	this->UnsubscribeFromEvent( Urho3D::E_JOYSTICKBUTTONDOWN );
	this->UnsubscribeFromEvent( Urho3D::E_JOYSTICKDISCONNECTED );
	this->UnsubscribeFromEvent( Urho3D::E_JOYSTICKCONNECTED );
	this->UnsubscribeFromEvent( Urho3D::E_KEYUP );
	this->UnsubscribeFromEvent( Urho3D::E_KEYDOWN );

	this->GetSubsystem< Level >()->Stop();
};

void World::Update( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
	const auto* input = this->GetSubsystem< Urho3D::Input >();
	auto* camera = this->GetSubsystem< WorldCamera >();

	if ( this->cameraFollowPlayer_ ) {
		auto worldPosition = this->player_->GetWorldPosition();

		this->yaw_ = camera->getYaw();
		this->pitch_ = camera->getPitch();

		Urho3D::VariantMap data;
		data[ "position" ] = worldPosition;
		camera->Update( eventType, data );
	}
	else {
		const auto mouseMove = input->GetMouseMove();

		this->yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
		this->pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
		this->pitch_ = Urho3D::Clamp( this->pitch_, -90.0f, 90.0f );

		camera->rotate( this->pitch_, this->yaw_ );
	}

	const float timeStep = eventData[ Urho3D::Update::P_TIMESTEP ].GetFloat();

	if ( input->GetKeyDown( Urho3D::KEY_UP ) )
		camera->move( Urho3D::Vector3::FORWARD * MOVE_SPEED * timeStep );
	if ( input->GetKeyDown( Urho3D::KEY_DOWN ) )
		camera->move( Urho3D::Vector3::BACK * MOVE_SPEED * timeStep );
	if ( input->GetKeyDown( Urho3D::KEY_LEFT ) )
		camera->move( Urho3D::Vector3::LEFT * MOVE_SPEED * timeStep );
	if ( input->GetKeyDown( Urho3D::KEY_RIGHT ) )
		camera->move( Urho3D::Vector3::RIGHT * MOVE_SPEED * timeStep );

	auto* playerComponent = this->player_->GetComponent< ObjectMovement >();

	if ( input->GetKeyDown( Urho3D::KEY_W ) )
		playerComponent->MoveZ( 1 );
	if ( input->GetKeyDown( Urho3D::KEY_S ) )
		playerComponent->MoveZ( -1 );
	if ( input->GetKeyDown( Urho3D::KEY_A ) )
		playerComponent->MoveX( -1 );
	if ( input->GetKeyDown( Urho3D::KEY_D ) )
		playerComponent->MoveX( 1 );
};
