/*
    Project: BubbleUP
    Author: Sumeet Singh
    Dated: 13/04/2024
    Minimum C++ Standard: C++17
    Purpose: Definition file
    License: MIT License


    _________________________________________________________________________________________________

                                        GLOBAL VARIABLES DEFINITIONS
    _________________________________________________________________________________________________


    DESCRIPTION

    Definition file of all global variables

    Declarations: ./headers/globals.hpp
    Definitions: ./src/globals.cpp


    EXAMPLE

    1. Only the header file needs including anywhere
    #include <globals.hpp>

    2. If you create any new global variables for this program. Place them here, and place as extern
    in globals.hpp


*/

#include "../headers/globals.hpp"

// Standard SDL Library
SDL_Window *window{};
SDL_Renderer *renderer{};

// Textures
SDL_Texture *background1Texture{};
SDL_Texture *heartTexture{};
SDL_Texture *hearts2Texture{};
SDL_Texture *hearts3Texture{};
SDL_Texture *hearts4Texture{};
SDL_Texture *hearts5Texture{};
SDL_Texture *timerTexture{};

// SDL_TTF
TTF_Font *defaultFont{};
TTF_Font *font24{};
TTF_Font *font36{};
TTF_Font *font48{};
TTF_Font *fontBold24{};
TTF_Font *fontBold36{};
TTF_Font *fontBold48{};
TTF_Font *europeanfont24{};
TTF_Font *europeanfont36{};
TTF_Font *europeanfont48{};
TTF_Font *europeanBoldfont24{};
TTF_Font *europeanBoldfont36{};
TTF_Font *europeanBoldfont48{};
TTF_Font *japanesefont24{};
TTF_Font *japanesefont36{};
TTF_Font *japanesefont48{};
TTF_Font *japaneseBoldfont24{};
TTF_Font *japaneseBoldfont36{};
TTF_Font *japaneseBoldfont48{};
TTF_Font *thaifont24{};
TTF_Font *thaifont36{};
TTF_Font *thaifont48{};
TTF_Font *thaiBoldfont24{};
TTF_Font *thaiBoldfont36{};
TTF_Font *thaiBoldfont48{};
TTF_Font *devanagarifont24{};
TTF_Font *devanagarifont36{};
TTF_Font *devanagarifont48{};
TTF_Font *devanagariBoldfont24{};
TTF_Font *devanagariBoldfont36{};
TTF_Font *devanagariBoldfont48{};
TTF_Font *chinesefont24{};
TTF_Font *chinesefont36{};
TTF_Font *chinesefont48{};
TTF_Font *chineseBoldfont24{};
TTF_Font *chineseBoldfont36{};
TTF_Font *chineseBoldfont48{};
TTF_Font *arabicfont24{};
TTF_Font *arabicfont36{};
TTF_Font *arabicfont48{};
TTF_Font *arabicBoldfont24{};
TTF_Font *arabicBoldfont36{};
TTF_Font *arabicBoldfont48{};
TTF_Font *geezfont24{};
TTF_Font *geezfont36{};
TTF_Font *geezfont48{};
TTF_Font *geezBoldfont24{};
TTF_Font *geezBoldfont36{};
TTF_Font *geezBoldfont48{};

// SDL_Mixer
Mix_Music *music{};
Mix_Chunk *treeSound{};
Mix_Chunk *waterSound{};
Mix_Chunk *barkSound{};
Mix_Chunk *heartSound{};
Mix_Chunk *moneySound{};
Mix_Chunk *drinkSound{};
Mix_Chunk *paperSound{};
Mix_Chunk *shootSound{};
Mix_Chunk *bumpSound{};
Mix_Chunk *popSound{};
Mix_Chunk *unlockSound{};
Mix_Chunk *lockSound{};
Mix_Chunk *winGameSound{};
Mix_Chunk *loseGameSound{};
Mix_Chunk *explosionSound{};
Mix_Chunk *clothesSound{};

bool quitEventLoop{};
std::string language = "English";
bool boldFont{};
/*
    Common 16:9 Resolutions
    1920 x 1080 (Full HD)
    1600 x 900
    1366 x 768
    1280 x 720 (HD)
    1024 x 576
    960 x 540
    854 x 480
*/
std::string softwareVersion = "0.1";
int GAME_WORLD_WIDTH = 2560;  // SCREEN_WIDTH x 2
int GAME_WORLD_HEIGHT = 1440; // SCREEN_HEIGHT x 2
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;
int MINIMAP_SIZE = 200;
SDL_Rect cameraRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
std::string currentResolution = "Resolution: " + std::to_string(SCREEN_WIDTH) + "x" + std::to_string(SCREEN_HEIGHT);
float acceleration = 0.5f;
float deceleration = 0.01f;
int xDragOffset{};
int yDragOffset{};
bool mousePressed{};
bool keyPressed{};
std::string buttonDirection{};
int soundVolume = 100;
int musicVolume = 100;
int scene = 1;
int lastScene{};                              // keep track of last scene e.g. to return to scene from viewing settings
int scrollYpos{};                             // For draw_file_contents_to_screen() - handle()  - Current scroll position
int scrollSpeed = 100;                        // For draw_file_contents_to_screen() - handle() - Speed of mouse wheel and forward and back button page scrolling e.g. in help scene 5
std::atomic<bool> startTimer{};               // for toggle_countdown()
int countdownSeconds = 300;                   // For toggle_countdown() - Initial countdown time
std::vector<int> unlockedAchievements(10, 0); // For integrating with gaming platforms for achievement tracking
std::string saveFileName = "gamesave.txt";
std::string readmeFileName = "README.md";                                                    // global variables because there are different language files
std::string creditsFileName = "CREDITS.md";                                                  // global variables because there are different language files
std::string privacyPolicyFileName = "assets/docs/EN/policies/PRIVACY_POLICY.txt";            // global variables because there are different language files
std::string termsAndConditionsFileName = "assets/docs/EN/policies/TERMS_AND_CONDITIONS.txt"; // global variables because there are different language files
int highestScore{};
bool gameStarted{};
bool gameOver{}; // used in toggle_countdown() on countdown gameover
bool wonlevel{};
bool wonGame{};
bool musicPlaying = true;   // toggle for settings menu option to play in game game
bool vsyncEnabled = true;   // toggle for settings menu option to enable/disable vysnc which triggers renderer recreation
bool displayOnScreenKeys{}; // for mobile games toggle in settings menu to show on screen touch controls
bool displayFPS{};          // for settings menu option to show FPS on screen
bool windowResized{};       // for SDL handle key input WIDOW minimised/maximised or resized event to update window*
bool windowMinimized{};     // for SDL handle key input WIDOW minimised event to pause rendering when minimised
bool isMultiplayerGame{};
int clientPlayerID{};
std::mt19937 gen(std::random_device{}());                    // for bot simulation
std::uniform_int_distribution<> dis(0, 3);                   // for bot simulation
std::chrono::steady_clock::time_point lastBotMovementTime{}; // for bot simulation

bool scene100setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool scene101setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool scene102setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool scene103setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool scene104setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool scene105setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool scene106setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool scene107setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool scene108setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool scene109setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool scene110setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool scene111setup{};         // one time flags called during game scene/level to setup new game e.g. reset timer, spawn entities
bool sceneMultiplayersetup{}; // one time flags called during multiplayer game scene/level to setup new game e.g. reset timer, spawn entities

// Translations
std::map<std::string, std::map<std::string, std::string>> languageTranslations = {
    {"English", {{"change_font_txt", "CHANGE FONT"}, {"change_language_txt", "CHANGE LANGUAGE"}, {"enter_name_txt", "ENTER NAME"}, {"high_score_txt", "HIGH SCORE"}, {"new_game_txt", "NEW GAME"}, {"player_txt", "PLAYER"}, {"quit_game_txt", "QUIT GAME"}, {"return_txt", "RETURN"}, {"score_txt", "SCORE"}, {"settings_txt", "SETTINGS"}, {"sound_control_txt", "SOUND CONTROL"}, {"volume_control_txt", "VOLUME CONTROL"}}},
    {"日本語", {{"change_font_txt", "フォントを変更する"}, {"change_language_txt", "言語を変えてください"}, {"enter_name_txt", "ENTER NAME"}, {"high_score_txt", "名前を入力"}, {"new_game_txt", "新しいゲーム"}, {"player_txt", "プレーヤー"}, {"quit_game_txt", "ゲームをやめる"}, {"return_txt", "戻る"}, {"score_txt", "スコア"}, {"settings_txt", "設定"}, {"sound_control_txt", "サウンドコントロール"}, {"volume_control_txt", "音量調節"}}}};

std::vector<Entity *> entities{};
std::vector<ParticleGenerator> particles{};

// Scene 1 - Main Menu
/*

       COLUMN 1     COLUMN 2     COLUMN 3     COLUMN 4     COLUMN 5     COLUMN 6     COLUMN 7     COLUMN 8     COLUMN 9     COLUMN 10
     __________________________________________________________________________________________________________________________________ 0
    |            |            |            |                         |            |            |            |            |            |
    |            |            |            |      Title              |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 1
    |            |            |            |                         |            |            |            |            |            |
    |            |            |            |      New Game           |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 2
    |            |            |            |                         |            |            |            |            |            |
    |            |            |            |      Settings           |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 3
    |            |            |            |                         |            |            |            |            |            |
    |            |            |            |      Unlockables        |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 4
    |            |            |            |                         |            |            |            |            |            |
    |            |            |            |      Scores             |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 5
    |            |            |            |                         |            |            |            |            |            |
    |            |            |            |      Help               |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 6
    |            |            |            |                         |            |            |            |            |            |
    |            |            |            |      Achievemens        |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 7
    |            |            |            |                         |            |            |            |            |            |
    |            |            |            |      Multiplayer        |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 8
    |            |            |            |                         |            |            |            |            |            |
    |            |            |            |      Quit               |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 9
    |            |            |            |            |            |            |            |            |            |            |
    |            |            |            |            |            |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________|

*/
ClickableButton scene1newGameButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "New Game",                             // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
ClickableButton scene1settingsButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.2),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Settings",                             // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
ClickableButton scene1unlockablesButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.3),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Unlockables",                          // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
ClickableButton scene1scoreButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.4),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Score",                                // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
ClickableButton scene1helpButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.5),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Help",                                 // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
ClickableButton scene1achievementsButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.6),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Achievements",                         // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
ClickableButton scene1multiplayerButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.7),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Multiplayer",                          // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
ClickableButton scene1levelEditorButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.8),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Level Editor",                          // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
ClickableButton scene1modStoreButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.9),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Mod Store",                          // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
ClickableButton scene1quitGameButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 1),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Quit Game",                            // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)

// Scene 2 - Settings
/*
     0           1            2            3            4            5            6            7            8            9            10
     __________________________________________________________________________________________________________________________________ 0
    |            |            |            |            |            |            |            |            |            |            |
    |            |            |            |            |            |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 1
    |            |            |            |            |            |            |            |            |            |            |
    |            |            |            |            |            |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 2
    |            |                         |                         |                         |            | RETURN                  |
    |            | FONT                    | FULLSCREEN              | SOUND                   |            | TITLE                   |
    |____________|_________________________|_________________________|_________________________|____________|_________________________| 3
    |            |                         |                         |                         |            | RETURN                  |
    |            | LANGUAGE                | VSYNC                   | MUSIC                   |            | GAME                    |
    |____________|_________________________|_________________________|_________________________|____________|_________________________| 4
    |            |                         |                         | SOUND                                | SAVE                    |
    |            | KEYMAPPING              | FPS                     | SLIDER                               | SETTINGS                |
    |____________|_________________________|_________________________|______________________________________|_________________________| 5
    |            | DISPLAY    |            |                         | MUSIC                                | RESET                   |
    |            |Touch Buttons            | RESOLUTIONS             | SLIDER                               | SETTINGS                |
    |____________|____________|____________|_________________________|______________________________________|_________________________| 6
    |            |            |            |            |            | SCROLL                               |            |            |
    |            |            |            |            |            | SLIDER                               |            |            |
    |____________|____________|____________|_________________________|______________________________________|____________|____________| 7
    |            |            |            |            |            |            |            |            |            |            |
    |            |            |            |            |            |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 8
    |            |            |            |            |            |            |            |            |            |            |
    |            |            |            |            |            |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________| 9
    |            |            |            |            |            |            |            |            |            |            |
    |            |            |            |            |            |            |            |            |            |            |
    |____________|____________|____________|_________________________|____________|____________|____________|____________|____________|

*/
// col 1
ClickableButton scene2ChangeFontButton{
    static_cast<int>(SCREEN_WIDTH * 0.1),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.2), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Change Font",                         // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene2ChangeLanguageButton{
    static_cast<int>(SCREEN_WIDTH * 0.1),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.3), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Change Language",                     // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene2changeKeymappingButton{
    static_cast<int>(SCREEN_WIDTH * 0.1),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.4), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Keymapping",                          // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene2displayOnScreenKeysButton{
    static_cast<int>(SCREEN_WIDTH * 0.1),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.5), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Display Touchscreen buttons",         // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
// col 3
ClickableButton scene2fullscreenToggleButton{
    static_cast<int>(SCREEN_WIDTH * 0.3),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.2), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Fullscreen Toggle",                   // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene2enableVsyncButton{
    static_cast<int>(SCREEN_WIDTH * 0.3),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.3), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Enable Vsync",                        // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene2toggleFPSButton{
    static_cast<int>(SCREEN_WIDTH * 0.3),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.4), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "toggle FPS",                          // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
DropdownButton scene2resolutionsDropdownButton{
    static_cast<int>(SCREEN_WIDTH * 0.3),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.5), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    currentResolution,                     // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene2resolutionsDropdown800x640Button{
    static_cast<int>(SCREEN_WIDTH * 0.1),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "800 x 640",                           // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene2resolutionsDropdown1366x768Button{
    static_cast<int>(SCREEN_WIDTH * 0.1),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "1366 x 768",                          // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
// col 5
ClickableButton scene2toggleSoundButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.3), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "toggle SFX",                          // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene2toggleMusicButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.4), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "toggle Music",                        // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
SliderButton scene2SFXSliderButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),        // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.5),       // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.3),        // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),       // Height
    "Volume Slider",                             // Button label
    144, 238, 144, 255,                          // Button color (RGBA)
    "assets/graphics/boxes/Slider_button_2.png", // Button texture path
    defaultFont,                                 // Button font
    0, 0, 0, 1,                                  // Text color (RGBA)
    static_cast<int>(SCREEN_WIDTH * 0.6),        // dot int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.5),       // dot int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.05),       // dot Width
    static_cast<int>(SCREEN_HEIGHT * 0.05),      // dot Height
    "assets/graphics/boxes/Slider_dot.png"};     // dot Texture path
SliderButton scene2VolumeSliderButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),        // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.6),       // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.3),        // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),       // Height
    "Volume Slider",                             // Button label
    144, 238, 144, 255,                          // Button color (RGBA)
    "assets/graphics/boxes/Slider_button_2.png", // Button texture path
    defaultFont,                                 // Button font
    0, 0, 0, 1,                                  // Text color (RGBA)
    static_cast<int>(SCREEN_WIDTH * 0.6),        // dot int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.6),       // dot int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.05),       // dot Width
    static_cast<int>(SCREEN_HEIGHT * 0.05),      // dot Height
    "assets/graphics/boxes/Slider_dot.png"};     // dot Texture path
SliderButton scene2scrollSpeedSliderButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),        // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.7),       // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.3),        // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),       // Height
    "Scroll speed",                              // Button label
    144, 238, 144, 255,                          // Button color (RGBA)
    "assets/graphics/boxes/Slider_button_2.png", // Button texture path
    defaultFont,                                 // Button font
    0, 0, 0, 1,                                  // Text color (RGBA)
    static_cast<int>(SCREEN_WIDTH * 0.6),        // dot int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.7),       // dot int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.05),       // dot Width
    static_cast<int>(SCREEN_HEIGHT * 0.05),      // dot Height
    "assets/graphics/boxes/Slider_dot.png"};     // dot Texture path
// col 8
ClickableButton scene2returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.2), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return Menu",                         // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene2returnToGameButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.3), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return Game",                         // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene2saveSettingsButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.4), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Save Settings",                       // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene2ResetToDefaultSettingsButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.5), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Default Settings",                    // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
// Scene 3 - Unlockables
ClickableButton scene3returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
ClickableButton scene3creditsButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Credits",                              // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
ClickableButton scene3sandboxButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.2),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Sandbox",                              // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
ClickableButton scene3soundtrackButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.3),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.28),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Soundtrack",                           // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)

// Scene 4 - Scoreboard
ClickableButton scene4submitNameButton{
    static_cast<int>(SCREEN_WIDTH * 0.3),   // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.8),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.2),   // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "SUBMIT",                               // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255};                          // Text color (RGBA)
InputButton scene4inputPlayerNameButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),   // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.8),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.4),   // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Enter name",                           // Button label
    255, 255, 255, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255,                           // Text color (RGBA)
};
ClickableButton scene4returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 5 - Help
ClickableButton scene5returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
ClickableButton scene5backButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),                 // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.9),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Back",                                                // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
ClickableButton scene5forwardButton{
    static_cast<int>(SCREEN_WIDTH * 0.55),                 // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.9),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Forward",                                             // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 6 - Achievements
ClickableButton scene6returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 7 - Check for updates
ClickableButton scene7returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
ClickableButton scene7updateButton{
    static_cast<int>(SCREEN_WIDTH * 0.35), // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.6), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "UPDATE",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene7cancelButton{
    static_cast<int>(SCREEN_WIDTH * 0.55), // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.6), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "CANCEL",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
// scene 8 - Online login
ClickableButton scene8returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.9),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
ClickableButton scene8loginButton{
    static_cast<int>(SCREEN_WIDTH * 0.35), // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.8), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "LOGIN",                               // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
ClickableButton scene8registerButton{
    static_cast<int>(SCREEN_WIDTH * 0.55), // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.8), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "REGISTER",                            // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 255};                         // Text color (RGBA)
InputButton scene8inputemailButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),   // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.3),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.4),   // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Enter Email",                          // Button label
    255, 255, 255, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255,                           // Text color (RGBA)
};
InputButton scene8inputpasswordButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),   // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.4),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.4),   // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Enter Password",                       // Button label
    255, 255, 255, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255,                           // Text color (RGBA)
};
// scene 9 - Create account
ClickableButton scene9returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.9),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
ClickableButton scene9submitButton{
    static_cast<int>(SCREEN_WIDTH * 0.35), // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.9), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
InputButton scene9inputusernameButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),   // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.3),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.4),   // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Enter name",                           // Button label
    255, 255, 255, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255,                           // Text color (RGBA)
};
InputButton scene9inputemailButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),   // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.4),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.4),   // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Enter name",                           // Button label
    255, 255, 255, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255,                           // Text color (RGBA)
};
InputButton scene9inputpasswordNameButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),   // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.5),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.4),   // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Enter name",                           // Button label
    255, 255, 255, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 255,                           // Text color (RGBA)
};
// scene 10 - Show policies
// scene 11 - Multiplayer lobby
ClickableButton scene10returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
ClickableButton scene10acceptPrivacyPolicyButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene10denyPrivacyPolicyButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene10acceptTermsPolicyButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene10denyTermsPolicyButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
// scene 11 - Multiplayer Lobby
ClickableButton scene11returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
ClickableButton scene11createGameButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene11joinGameButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene11refreshGamesButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene11sendMessageButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene11addFriendButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene11refreshFriendsButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "Return",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
// scene 12 - Keybindings
ClickableButton scene12returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
ClickableButton scene12acceptButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.8),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),   // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "ACCEPT",                               // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 1};                            // Text color (RGBA)
ClickableButton scene12resetButton{
    static_cast<int>(SCREEN_WIDTH * 0.55),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.8),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),   // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "RESET",                                // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 1};                            // Text color (RGBA)
// scene 13 - Create Game
ClickableButton scene13cancelButton{
    static_cast<int>(SCREEN_WIDTH * 0.35),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.8),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),   // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Cancel",                               // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 1};                            // Text color (RGBA)
ClickableButton scene13createButton{
    static_cast<int>(SCREEN_WIDTH * 0.55),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.6),  // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),   // Width
    static_cast<int>(SCREEN_HEIGHT * 0.08), // Height
    "Create",                               // Button label
    144, 238, 144, 255,                     // Button color (RGBA)
    "assets/graphics/boxes/button.png",     // Button texture path
    defaultFont,                            // Button font
    0, 0, 0, 1};                            // Text color (RGBA)
// scene 14 - Credits
ClickableButton scene14returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 15 - Level Editor
DropdownButton scene15FileDropdownButton{
    static_cast<int>(SCREEN_WIDTH * 0.2),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.5), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "FILE",                                // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene15saveMapButton{
    static_cast<int>(SCREEN_WIDTH * 0.1),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "SAVE",                                // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene15loadMapButton{
    static_cast<int>(SCREEN_WIDTH * 0.1),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "LOAD",                                // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene15newMapButton{
    static_cast<int>(SCREEN_WIDTH * 0.1),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "NEW",                                 // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene15deleteMapButton{
    static_cast<int>(SCREEN_WIDTH * 0.1),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "DELETE",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene15importMapButton{
    static_cast<int>(SCREEN_WIDTH * 0.1),  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1), // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1), // Height
    "IMPORT",                              // Button label
    144, 238, 144, 255,                    // Button color (RGBA)
    "assets/graphics/boxes/button.png",    // Button texture path
    defaultFont,                           // Button font
    0, 0, 0, 1};                           // Text color (RGBA)
ClickableButton scene15returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)

// scene 16
ClickableButton scene16returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 17
ClickableButton scene17returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 18
ClickableButton scene18returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 19
ClickableButton scene19returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 20
ClickableButton scene20returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 21
ClickableButton scene21returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 22
ClickableButton scene22returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 23
ClickableButton scene23returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 24
ClickableButton scene24returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 25
ClickableButton scene25returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 26
ClickableButton scene26returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 27
ClickableButton scene27returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
ClickableButton scene27backButton{
    static_cast<int>(SCREEN_WIDTH * 0.3),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.7),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Back",                                                // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 255};                                         // Text color (RGBA)
ClickableButton scene27nextButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.7),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Next",                                                // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 255};                                         // Text color (RGBA)
ClickableButton scene27acceptButton{
    static_cast<int>(SCREEN_WIDTH * 0.3),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.8),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Accept",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 255};                                         // Text color (RGBA)
ClickableButton scene27denyButton{
    static_cast<int>(SCREEN_WIDTH * 0.5),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.8),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Deny",                                                // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 255};                                         // Text color (RGBA)
// scene 28
ClickableButton scene28returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 29
ClickableButton scene29returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 30
ClickableButton scene30returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene 31
ClickableButton scene31returnToTitleButton{
    static_cast<int>(SCREEN_WIDTH * 0.8),                  // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.1),                  // Width
    static_cast<int>(SCREEN_HEIGHT * 0.1),                 // Height
    "Return",                                              // Button label
    144, 238, 144, 255,                                    // Button color (RGBA)
    "assets/graphics/buttons/settings/restart-button.png", // Button texture path
    defaultFont,                                           // Button font
    0, 0, 0, 1};                                           // Text color (RGBA)
// scene - any gameplay scene
ClickableButton sceneGameplayMenuButton{
    static_cast<int>(SCREEN_WIDTH * 0.9),                                       // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.1),                                      // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.05),                                      // Width
    static_cast<int>(SCREEN_HEIGHT * 0.05),                                     // Height
    "MENU",                                                                     // Button label
    144, 238, 144, 255,                                                         // Button color (RGBA)
    "assets/graphics/buttons/onscreenControls/Sprites/flatDark/flatDark41.png", // Button texture path
    defaultFont,                                                                // Button font
    0, 0, 0, 1};                                                                // Text color (RGBA)
ClickableButton sceneGameplayUpButton{
    static_cast<int>(SCREEN_WIDTH * 0.2),                                       // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.7),                                      // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.05),                                      // Width
    static_cast<int>(SCREEN_HEIGHT * 0.05),                                     // Height
    "UP",                                                                       // Button label
    144, 238, 144, 255,                                                         // Button color (RGBA)
    "assets/graphics/buttons/onscreenControls/Sprites/flatDark/flatDark02.png", // Button texture path
    defaultFont,                                                                // Button font
    0, 0, 0, 1};                                                                // Text color (RGBA)
ClickableButton sceneGameplayDownButton{
    static_cast<int>(SCREEN_WIDTH * 0.2),                                       // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.8),                                      // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.05),                                      // Width
    static_cast<int>(SCREEN_HEIGHT * 0.05),                                     // Height
    "DOWN",                                                                     // Button label
    144, 238, 144, 255,                                                         // Button color (RGBA)
    "assets/graphics/buttons/onscreenControls/Sprites/flatDark/flatDark09.png", // Button texture path
    defaultFont,                                                                // Button font
    0, 0, 0, 1};                                                                // Text color (RGBA)
ClickableButton sceneGameplayLeftButton{
    static_cast<int>(SCREEN_WIDTH * 0.1),                                       // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.75),                                     // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.05),                                      // Width
    static_cast<int>(SCREEN_HEIGHT * 0.05),                                     // Height
    "LEFT",                                                                     // Button label
    144, 238, 144, 255,                                                         // Button color (RGBA)
    "assets/graphics/buttons/onscreenControls/Sprites/flatDark/flatDark04.png", // Button texture path
    defaultFont,                                                                // Button font
    0, 0, 0, 1};                                                                // Text color (RGBA)
ClickableButton sceneGameplayRightButton{
    static_cast<int>(SCREEN_WIDTH * 0.3),                                       // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.75),                                     // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.05),                                      // Width
    static_cast<int>(SCREEN_HEIGHT * 0.05),                                     // Height
    "RIGHT",                                                                    // Button label
    144, 238, 144, 255,                                                         // Button color (RGBA)
    "assets/graphics/buttons/onscreenControls/Sprites/flatDark/flatDark05.png", // Button texture path
    defaultFont,                                                                // Button font
    0, 0, 0, 1};                                                                // Text color (RGBA)
ClickableButton sceneGameplayUseButton{
    static_cast<int>(SCREEN_WIDTH * 0.7),                                       // int X-coordinate
    static_cast<int>(SCREEN_HEIGHT * 0.75),                                     // int Y-coordinate
    static_cast<int>(SCREEN_WIDTH * 0.05),                                      // Width
    static_cast<int>(SCREEN_HEIGHT * 0.05),                                     // Height
    "USE",                                                                      // Button label
    144, 238, 144, 255,                                                         // Button color (RGBA)
    "assets/graphics/buttons/onscreenControls/Sprites/flatDark/flatDark35.png", // Button texture path
    defaultFont,                                                                // Button font
    0, 0, 0, 1};                                                                // Text color (RGBA)

// Vectors to hold all buttons in scene to itterate over for rendering, and handle gui position checking
std::vector<BaseButton *> scene1buttons{};
std::vector<BaseButton *> scene2buttons{};
std::vector<BaseButton *> scene2resolutionsDropdownButtonVector{};
std::vector<BaseButton *> scene3buttons{};
std::vector<BaseButton *> scene4buttons{};
std::vector<BaseButton *> scene5buttons{};
std::vector<BaseButton *> scene6buttons{};
std::vector<BaseButton *> scene7buttons{};
std::vector<BaseButton *> scene8buttons{};
std::vector<BaseButton *> scene9buttons{};
std::vector<BaseButton *> scene10buttons{};
std::vector<BaseButton *> scene11buttons{};
std::vector<BaseButton *> scene12buttons{};
std::vector<BaseButton *> scene13buttons{};
std::vector<BaseButton *> scene14buttons{};
std::vector<BaseButton *> scene15buttons{};
std::vector<BaseButton *> scene15FileDropdownButtonVector{};
std::vector<BaseButton *> scene16buttons{};
std::vector<BaseButton *> scene17buttons{};
std::vector<BaseButton *> scene18buttons{};
std::vector<BaseButton *> scene19buttons{};
std::vector<BaseButton *> scene20buttons{};
std::vector<BaseButton *> scene21buttons{};
std::vector<BaseButton *> scene22buttons{};
std::vector<BaseButton *> scene23buttons{};
std::vector<BaseButton *> scene24buttons{};
std::vector<BaseButton *> scene25buttons{};
std::vector<BaseButton *> scene26buttons{};
std::vector<BaseButton *> scene27buttons{};
std::vector<BaseButton *> scene28buttons{};
std::vector<BaseButton *> scene29buttons{};
std::vector<BaseButton *> scene30buttons{};
std::vector<BaseButton *> scene31buttons{};
std::vector<BaseButton *> sceneGameplaybuttons{};
std::vector<BaseButton *> allButtons{};

BaseButton *BaseButton::selectedButton{};

std::vector<Score> scores{};

UpdateApp updateApp = {softwareVersion, "https://github.com/sumeet_chand/BubbleUp",
                       "https://github.com/sumeet_chand/BubbleUp/archive/refs/heads/main.zip", "", saveFileName, "BubbleUp.exe", "BubbleUp"};

DebugLogging logger("game_log.txt");

WebserverClient webserverClientContext{};
WebserverHost webserverHostContext{};