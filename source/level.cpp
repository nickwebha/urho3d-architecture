#include <level.hpp>

#ifdef __DEBUG__
	void Level::HandlePostRenderUpdate( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData ) {
		if ( this->drawDebug_ )
			this->scene_->GetComponent< Urho3D::PhysicsWorld >()->DrawDebugGeometry( true );
	};
#endif

void Level::DrawLogo( void ) {
	auto* cache = GetSubsystem< Urho3D::ResourceCache >();
	auto* logoTexture = cache->GetResource< Urho3D::Texture2D >( "Textures/FishBoneLogo.png" );
	if ( ! logoTexture )
		return;

	auto* ui = GetSubsystem< Urho3D::UI >();
	auto logoSprite = ui->GetRoot()->CreateChild< Urho3D::Sprite >();

	logoSprite->SetTexture( logoTexture );

	int textureWidth = logoTexture->GetWidth();
	int textureHeight = logoTexture->GetHeight();

	logoSprite->SetScale( 256.0f / textureWidth );
	logoSprite->SetSize( textureWidth, textureHeight );
	logoSprite->SetHotSpot( textureWidth, textureHeight );
	logoSprite->SetAlignment( Urho3D::HA_RIGHT, Urho3D::VA_BOTTOM );
	logoSprite->SetOpacity( 0.9f );
	logoSprite->SetPriority( -100 );
};

void Level::Start( void ) {
	this->scene_ = new Urho3D::Scene( this->GetContext() );

	#ifdef __DEBUG__
		this->scene_->CreateComponent< Urho3D::DebugRenderer >();
	#endif

	this->scene_->CreateComponent< Urho3D::Octree >();

	auto* cache = this->GetSubsystem< Urho3D::ResourceCache >();

	auto* physicsWorld = this->scene_->CreateComponent< Urho3D::PhysicsWorld >();
	physicsWorld->SetGravity( Urho3D::Vector3::DOWN * LEVEL_GRAVITY );

	auto* zoneNode = this->scene_->CreateChild( "Zone" );
	auto* zone = zoneNode->CreateComponent< Urho3D::Zone >();
	zone->SetBoundingBox( Urho3D::BoundingBox( -1000.0f, 1000.0 ) );
	zone->SetAmbientColor( Urho3D::Color( 0.15f, 0.15f, 0.15f ) );
	zone->SetFogColor( Urho3D::Color::WHITE );
	zone->SetFogStart( 900.0f );
	zone->SetFogEnd( 1000.0f );

	auto* lightNode = this->scene_->CreateChild( "Light" );
	lightNode->SetDirection( Urho3D::Vector3( 0.8f, -1.0f, 0.8f ) );
	auto* light = lightNode->CreateComponent< Urho3D::Light >();
	light->SetLightType( Urho3D::LIGHT_DIRECTIONAL );
	light->SetCastShadows( true );
	light->SetSpecularIntensity( 1.0f );
	light->SetColor( Urho3D::Color::WHITE );

	auto* skyNode = this->scene_->CreateChild( "Sky" );
	auto* skybox = skyNode->CreateComponent< Urho3D::Skybox >();
	skybox->SetModel( cache->GetResource< Urho3D::Model >( "Models/Box.mdl" ) );
	skybox->SetMaterial( cache->GetResource< Urho3D::Material >( "Materials/Skybox.xml" ) );

	this->terrainNode_ = this->scene_->CreateChild( "Terrain" );
	this->terrainNode_->SetPosition( Urho3D::Vector3::ZERO );
	auto* terrain = this->terrainNode_->CreateComponent< Urho3D::Terrain >();
	terrain->SetPatchSize( 32 );
	terrain->SetSpacing( Urho3D::Vector3( 2.5f, 0.5f, 2.5f ) );
	terrain->SetSmoothing( true );
	terrain->SetHeightMap( cache->GetResource< Urho3D::Image >( "Textures/HeightMap.png" ) );
	terrain->SetMaterial( cache->GetResource< Urho3D::Material >( "Materials/Terrain.xml" ) );
	terrain->SetOccluder( true );

	auto* rigidBody = this->terrainNode_->CreateComponent< Urho3D::RigidBody >();
	rigidBody->SetFriction( 0.1f );
	rigidBody->SetCollisionLayerAndMask( LayerFlagsTerrain, LayerFlagsControllable | LayerFlagsCylinders );

	auto* collisionShape = this->terrainNode_->CreateComponent< Urho3D::CollisionShape >();
	collisionShape->SetTerrain();

	this->DrawLogo();

	#ifdef __DEBUG__
		this->SubscribeToEvent( Urho3D::E_POSTRENDERUPDATE, URHO3D_HANDLER( Level, HandlePostRenderUpdate ) );
	#endif
};

void Level::Stop( void ) {
	#ifdef __DEBUG__
		this->UnsubscribeFromEvent( Urho3D::E_POSTRENDERUPDATE );
	#endif
};

#ifdef __DEBUG__
	void Level::setDebug( bool enable ) {
		this->drawDebug_ = enable;
	};

	bool Level::getDebug( void ) {
		return this->drawDebug_;
	};
#endif

Urho3D::SharedPtr< Urho3D::Scene > Level::getScene( void ) {
	return this->scene_;
};

Urho3D::SharedPtr< Urho3D::Node > Level::getTerrain( void ) {
	return this->terrainNode_;
};
