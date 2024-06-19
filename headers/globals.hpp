/*
    Project: BubbleUP
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++17
    Purpose: Declaration file
    License: MIT License


    DESCRIPTION

    Declaration file of all global variables. Created to prevent polluting namespace with conflicting
    variables. This way the variables are controlled by including this header only in required files

    Declarations: ./globals.hpp
    Definitions: ./src/globals.cpp


    EXAMPLE

    1. Include in files that need to access global variables e.g;
    #include <globals.hpp>

*/

#pragma once

#include <iostream>
#include <atomic>    // for making toggle_countdown() startTimer thread safe
#include <map>       // For translations
#include <chrono> // for bot simulated movement
#include <random>    // for random bot simulated movement/entity generation etc.,
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "buttons/ClickableButton.hpp"
#include "buttons/DropdownButton.hpp"
#include "buttons/InputButton.hpp"
#include "buttons/SliderButton.hpp"
#include "entities/Player.hpp"
#include "entities/Bot.hpp" // for game_engine_updates.hpp/cpp to move bots in update_scene_gameplays_xx()
#include "entities/Item.hpp"
#include "entities/Enemy.hpp"
#include "entities/Obstacle.hpp"
#include "UpdateApp.hpp"
#include "DebugLogging.hpp"
#include "WebserverHost.hpp"
#include "WebserverClient.hpp"
#include "ParticleGenerator.hpp"
#include "SaveLoadData.hpp"
#include "FFmpegVideoPlayer.hpp"
// Score.hpp is included from WebserverHost.hpp no need to include twice

// Standard SDL Library
extern SDL_Window *window;
extern SDL_Renderer *renderer;

// Textures
extern SDL_Texture *background1Texture;
extern SDL_Texture *heartTexture;
extern SDL_Texture *hearts2Texture;
extern SDL_Texture *hearts3Texture;
extern SDL_Texture *hearts4Texture;
extern SDL_Texture *hearts5Texture;
extern SDL_Texture *timerTexture;

// SDL_TTF
extern TTF_Font *defaultFont;

extern TTF_Font *font24;     // default font
extern TTF_Font *font36;     // default font
extern TTF_Font *font48;     // default font
extern TTF_Font *fontBold24; // default font
extern TTF_Font *fontBold36; // default font
extern TTF_Font *fontBold48; // default font

extern TTF_Font *europeanfont24;     // Supports all European languages
extern TTF_Font *europeanfont36;     // Supports all European languages
extern TTF_Font *europeanfont48;     // Supports all European languages
extern TTF_Font *europeanBoldfont24; // Supports all European languages
extern TTF_Font *europeanBoldfont36; // Supports all European languages
extern TTF_Font *europeanBoldfont48; // Supports all European languages

extern TTF_Font *japanesefont24;
extern TTF_Font *japanesefont36;
extern TTF_Font *japanesefont48;
extern TTF_Font *japaneseBoldfont24;
extern TTF_Font *japaneseBoldfont36;
extern TTF_Font *japaneseBoldfont48;

extern TTF_Font *thaifont24;
extern TTF_Font *thaifont36;
extern TTF_Font *thaifont48;
extern TTF_Font *thaiBoldfont24;
extern TTF_Font *thaiBoldfont36;
extern TTF_Font *thaiBoldfont48;

extern TTF_Font *devanagarifont24;
extern TTF_Font *devanagarifont36;
extern TTF_Font *devanagarifont48;
extern TTF_Font *devanagariBoldfont24;
extern TTF_Font *devanagariBoldfont36;
extern TTF_Font *devanagariBoldfont48;

extern TTF_Font *chinesefont24;
extern TTF_Font *chinesefont36;
extern TTF_Font *chinesefont48;
extern TTF_Font *chineseBoldfont24;
extern TTF_Font *chineseBoldfont36;
extern TTF_Font *chineseBoldfont48;

extern TTF_Font *arabicfont24;
extern TTF_Font *arabicfont36;
extern TTF_Font *arabicfont48;
extern TTF_Font *arabicBoldfont24;
extern TTF_Font *arabicBoldfont36;
extern TTF_Font *arabicBoldfont48;

extern TTF_Font *geezfont24;
extern TTF_Font *geezfont36;
extern TTF_Font *geezfont48;
extern TTF_Font *geezBoldfont24;
extern TTF_Font *geezBoldfont36;
extern TTF_Font *geezBoldfont48;

// SDL_Mixer
extern Mix_Music *music;
extern Mix_Chunk *treeSound;
extern Mix_Chunk *waterSound;
extern Mix_Chunk *barkSound;
extern Mix_Chunk *heartSound;
extern Mix_Chunk *moneySound;
extern Mix_Chunk *drinkSound;
extern Mix_Chunk *paperSound;
extern Mix_Chunk *shootSound;
extern Mix_Chunk *bumpSound;
extern Mix_Chunk *popSound;
extern Mix_Chunk *unlockSound;
extern Mix_Chunk *lockSound;
extern Mix_Chunk *winGameSound;
extern Mix_Chunk *loseGameSound;
extern Mix_Chunk *explosionSound;
extern Mix_Chunk *clothesSound;

extern bool quitEventLoop;
extern std::string language;
extern bool boldFont;
/*
    16:9 Resolutions - https://en.wikipedia.org/wiki/16:9_aspect_ratio#Common_resolutions
    _______________________

    Width	Height	Name
    _______________________
    854	    480	    FWVGA
    960	    540	    qHD
    1024	576	    WSVGA
    1280	720	    HD
    1366	768	    FWXGA
    1600	900	    HD+
    1920	1080	Full HD
    2560	1440	QHD
    3200	1800	QHD+
    3840	2160	4K UHD
    5120	2880	5K
    7680	4320	8K UHD
*/
extern std::string softwareVersion;
extern int GAME_WORLD_WIDTH;
extern int GAME_WORLD_HEIGHT;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int MINIMAP_SIZE;
extern SDL_Rect cameraRect;
extern std::string currentResolution;
extern float acceleration;
extern float deceleration;
extern int xDragOffset;
extern int yDragOffset;
extern bool mousePressed;
extern bool keyPressed;
extern std::string buttonDirection;
extern int soundVolume;
extern int musicVolume;
extern int lastScene;
extern int scene;
extern int scrollYpos;
extern int scrollSpeed;
extern std::atomic<bool> startTimer;
extern int countdownSeconds;
extern std::vector<int> unlockedAchievements;
extern std::string saveFileName;
extern std::string readmeFileName;
extern std::string creditsFileName;
extern std::string privacyPolicyFileName;
extern std::string termsAndConditionsFileName;
extern int highestScore;
extern bool gameStarted;
extern bool gameOver;
extern bool wonlevel;
extern bool wonGame;
extern bool musicPlaying;
extern bool vsyncEnabled;
extern bool displayOnScreenKeys;
extern bool displayFPS;
extern bool windowResized;
extern bool windowMinimized;
extern bool isMultiplayerGame; // flag for indicating game is multiplayer to POST gameplay to webserver host
extern int clientPlayerID;
extern std::mt19937 gen; // for bot simulation
extern std::uniform_int_distribution<> dis; // for bot simulation
extern std::chrono::steady_clock::time_point lastBotMovementTime; // for bot simulation

// Game variables
extern bool scene100setup;
extern bool scene101setup;
extern bool scene102setup;
extern bool scene102setup;
extern bool scene103setup;
extern bool scene104setup;
extern bool scene105setup;
extern bool scene106setup;
extern bool scene107setup;
extern bool scene108setup;
extern bool scene109setup;
extern bool scene110setup;
extern bool scene111setup;
extern bool sceneMultiplayersetup;

// Translations
extern std::map< std::string, std::map< std::string, std::string>> languageTranslations;

extern std::vector<Entity *> entities;

extern std::vector<ParticleGenerator> particles;

extern BaseButton *selectedButton;

// Scene 1 - Main Menu
extern ClickableButton scene1newGameButton;
extern ClickableButton scene1settingsButton;
extern ClickableButton scene1unlockablesButton;
extern ClickableButton scene1scoreButton;
extern ClickableButton scene1helpButton;
extern ClickableButton scene1achievementsButton;
extern ClickableButton scene1multiplayerButton;
extern ClickableButton scene1levelEditorButton;
extern ClickableButton scene1modStoreButton;
extern ClickableButton scene1quitGameButton;

// scene 2 - Settings
// col 1
extern ClickableButton scene2ChangeFontButton;
extern ClickableButton scene2ChangeLanguageButton;
extern ClickableButton scene2changeKeymappingButton;
extern ClickableButton scene2displayOnScreenKeysButton;
// col 3
extern ClickableButton scene2fullscreenToggleButton;
extern ClickableButton scene2toggleFPSButton;
extern ClickableButton scene2enableVsyncButton;
extern DropdownButton scene2resolutionsDropdownButton;
    extern ClickableButton scene2resolutionsDropdown800x640Button;
    extern ClickableButton scene2resolutionsDropdown1366x768Button;
// col 5
extern ClickableButton scene2toggleSoundButton;
extern ClickableButton scene2toggleMusicButton;
extern SliderButton scene2SFXSliderButton;
extern SliderButton scene2VolumeSliderButton;
extern SliderButton scene2scrollSpeedSliderButton;
// col 8
extern ClickableButton scene2returnToTitleButton;
extern ClickableButton scene2returnToGameButton;
extern ClickableButton scene2saveSettingsButton;
extern ClickableButton scene2ResetToDefaultSettingsButton;

// scene 3 - Unlockables
extern ClickableButton scene3returnToTitleButton;
extern ClickableButton scene3creditsButton;
extern ClickableButton scene3sandboxButton;
extern ClickableButton scene3soundtrackButton;
// scene 4 - Scoreboard
extern ClickableButton scene4submitNameButton;
extern InputButton scene4inputPlayerNameButton;
extern ClickableButton scene4returnToTitleButton;
// scene 5 - Help
extern ClickableButton scene5returnToTitleButton;
extern ClickableButton scene5backButton;
extern ClickableButton scene5forwardButton;
// scene 6 - Achievements
extern ClickableButton scene6returnToTitleButton;
// scene 7 - Check for updates
extern ClickableButton scene7returnToTitleButton;
extern ClickableButton scene7updateButton;
extern ClickableButton scene7cancelButton;
// scene 8 - Online login
extern ClickableButton scene8returnToTitleButton;
extern ClickableButton scene8loginButton;
extern ClickableButton scene8registerButton;
extern InputButton scene8inputemailButton;
extern InputButton scene8inputpasswordButton;
// scene 9 - Create account
extern ClickableButton scene9returnToTitleButton;
extern ClickableButton scene9submitButton;
extern InputButton scene9inputusernameButton;
extern InputButton scene9inputemailButton;
extern InputButton scene9inputpasswordNameButton;
// scene 10 - Show policies
extern ClickableButton scene10returnToTitleButton;
extern ClickableButton scene10acceptPrivacyPolicyButton;
extern ClickableButton scene10denyPrivacyPolicyButton;
extern ClickableButton scene10acceptTermsPolicyButton;
extern ClickableButton scene10denyTermsPolicyButton;
// scene 11 - Multiplayer Lobby
extern ClickableButton scene11returnToTitleButton;
extern ClickableButton scene11createGameButton;
extern ClickableButton scene11joinGameButton;
extern ClickableButton scene11refreshGamesButton;
extern ClickableButton scene11sendMessageButton;
extern ClickableButton scene11addFriendButton;
extern ClickableButton scene11refreshFriendsButton;
// scene 12 - Keybindings
extern ClickableButton scene12returnToTitleButton;
extern ClickableButton scene12acceptButton;
extern ClickableButton scene12resetButton;
// scene 13 - Create Game
extern ClickableButton scene13cancelButton;
extern ClickableButton scene13createButton;
// scene 14 - Credits
extern ClickableButton scene14returnToTitleButton;
// scene 15 - Level editor
extern DropdownButton scene15FileDropdownButton;
extern ClickableButton scene15saveMapButton;
extern ClickableButton scene15loadMapButton;
extern ClickableButton scene15newMapButton;
extern ClickableButton scene15deleteMapButton;
extern ClickableButton scene15importMapButton;
extern ClickableButton scene15returnToTitleButton;
// scene 16
extern ClickableButton scene16returnToTitleButton;
// scene 17
extern ClickableButton scene17returnToTitleButton;
// scene 18
extern ClickableButton scene18returnToTitleButton;
// scene 19
extern ClickableButton scene19returnToTitleButton;
// scene 20
extern ClickableButton scene20returnToTitleButton;
// scene 21
extern ClickableButton scene21returnToTitleButton;
// scene 22
extern ClickableButton scene22returnToTitleButton;
// scene 23
extern ClickableButton scene23returnToTitleButton;
// scene 24
extern ClickableButton scene24returnToTitleButton;
// scene 25
extern ClickableButton scene25returnToTitleButton;
// scene 26
extern ClickableButton scene26returnToTitleButton;
// scene 27
extern ClickableButton scene27returnToTitleButton;
extern ClickableButton scene27backButton;
extern ClickableButton scene27nextButton;
extern ClickableButton scene27acceptButton;
extern ClickableButton scene27denyButton;
// scene 28
extern ClickableButton scene28returnToTitleButton;
// scene 29
extern ClickableButton scene29returnToTitleButton;
// scene 30
extern ClickableButton scene30returnToTitleButton;
// scene 31
extern ClickableButton scene31returnToTitleButton;
// scene - any gameplay scene
extern ClickableButton sceneGameplayMenuButton;
extern ClickableButton sceneGameplayUpButton;
extern ClickableButton sceneGameplayDownButton;
extern ClickableButton sceneGameplayLeftButton;
extern ClickableButton sceneGameplayRightButton;
extern ClickableButton sceneGameplayUseButton;

extern std::vector<BaseButton *> scene1buttons;
extern std::vector<BaseButton *> scene2buttons;
extern std::vector<BaseButton *> scene2resolutionsDropdownButtonVector;
extern std::vector<BaseButton *> scene3buttons;
extern std::vector<BaseButton *> scene4buttons;
extern std::vector<BaseButton *> scene5buttons;
extern std::vector<BaseButton *> scene6buttons;
extern std::vector<BaseButton *> scene7buttons;
extern std::vector<BaseButton *> scene8buttons;
extern std::vector<BaseButton *> scene9buttons;
extern std::vector<BaseButton *> scene10buttons;
extern std::vector<BaseButton *> scene11buttons;
extern std::vector<BaseButton *> scene12buttons;
extern std::vector<BaseButton *> scene13buttons;
extern std::vector<BaseButton *> scene14buttons;
extern std::vector<BaseButton *> scene15buttons;
extern std::vector<BaseButton *> scene15FileDropdownButtonVector;
extern std::vector<BaseButton *> scene16buttons;
extern std::vector<BaseButton *> scene17buttons;
extern std::vector<BaseButton *> scene18buttons;
extern std::vector<BaseButton *> scene19buttons;
extern std::vector<BaseButton *> scene20buttons;
extern std::vector<BaseButton *> scene21buttons;
extern std::vector<BaseButton *> scene22buttons;
extern std::vector<BaseButton *> scene23buttons;
extern std::vector<BaseButton *> scene24buttons;
extern std::vector<BaseButton *> scene25buttons;
extern std::vector<BaseButton *> scene26buttons;
extern std::vector<BaseButton *> scene27buttons;
extern std::vector<BaseButton *> scene28buttons;
extern std::vector<BaseButton *> scene29buttons;
extern std::vector<BaseButton *> scene30buttons;
extern std::vector<BaseButton *> scene31buttons;
extern std::vector<BaseButton *> allButtons;
extern std::vector<BaseButton *> sceneGameplaybuttons;

extern std::vector<Score> scores;
extern UpdateApp updateApp;
extern DebugLogging logger;
extern WebserverClient webserverClientContext;
extern WebserverHost webserverHostContext;
