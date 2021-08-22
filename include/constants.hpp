#pragma once

enum LayerFlags {
	LayerFlagsUndefined						= 0x0,
	LayerFlagsTerrain						= 0x1,
	LayerFlagsPlayer						= 0x2,
	LayerFlagsBall							= 0x4,
	LayerFlagsAny							= 0xff
};

#define MILLISECONDS_NOW					std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now().time_since_epoch() ).count()
#define SECONDS_NOW							std::chrono::duration_cast< std::chrono::seconds >( std::chrono::system_clock::now().time_since_epoch() ).count()

#define WINDOW_TITLE						"Urho3D Architecture"
#define WINDOW_ICON							"Textures/FishBoneLogo.png"
#define WINDOW_FPS_MINIMUM					30
#define WINDOW_FPS_INACTIVE					30

#ifdef __DEBUG__
	#define ASSETS_PATHS					"coreData/;data/"

	#define SCREEN_WIDTH					1280
	#define SCREEN_HEIGHT					720

	#define LOGO_TIMEOUT					1
#elif __RELEASE__
	#define ASSETS_PATHS					""
	#define ASSETS_PATHS_PACKAGES			std::vector< std::string >{ "coreData.pak", "data.pak" }

	#define SCREEN_WIDTH					1920
	#define SCREEN_HEIGHT					1080

	#define LOGO_TIMEOUT					5
#endif

#define WORLD_GRAVITY						-25

#define BALLS_COUNT							25
#define BALLS_SPEED							25

#define PLAYER_SPEED						15

#define JOYSTICK_BUTTON_FIRE				10
#define JOYSTICK_BUTTON_FIRESTOP			10

#define JOYSTICK_BUTTON_ACTIVATED			9
#define JOYSTICK_BUTTON_ACTIVATEDSTOP		9
