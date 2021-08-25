#pragma once

enum LayerFlags {
	LayerFlagsUndefined				= 0x0,
	LayerFlagsTerrain				= 0x1,
	LayerFlagsPlayer				= 0x2,
	LayerFlagsCylinders				= 0x4,
	LayerFlagsAny					= 0xff
};

#define WINDOW_TITLE				"Urho3D Architecture"
#define WINDOW_ICON					"Textures/FishBoneLogo.png"
#define WINDOW_FPS_MINIMUM			30
#define WINDOW_FPS_INACTIVE			30

#ifdef __DEBUG__
	#define ASSETS_PATHS			"CoreData/;Data/"

	#define SCREEN_WIDTH			1280
	#define SCREEN_HEIGHT			720

	#define LOGO_TIMEOUT			1
#elif __RELEASE__
	#define ASSETS_PATHS			""
	#define ASSETS_PATHS_PACKAGES	std::vector< std::string >{ "CoreData.pak", "Data.pak" }

	#define SCREEN_WIDTH			1920
	#define SCREEN_HEIGHT			1080

	#define LOGO_TIMEOUT			5
#endif

#define MOVE_SPEED					100.0f
#define MOUSE_SENSITIVITY			0.1f

#define LEVEL_GRAVITY				25

#define PLAYER_SIZE					50
#define PLAYER_SPEED				2

#define CYLINDERS_COUNT				25
#define CYLINDERS_SIZE				25
