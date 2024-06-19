/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Definition file
    License: MIT License


    _________________________________________________________________________________________________

                                SDL INITIALISE FUNCTIONS DEFINITIONS
    _________________________________________________________________________________________________


    DESCRIPTION

    SDL Initialisation, running and destruction functions
    
    Declarations: ./headers/game_engine_initialise.hpp
    Definitions: ./src/game_engine_initialise.cpp


    EXAMPLE


*/

#include "../headers/game_engine_initialise.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "../headers/game_engine_draws.hpp"
#include "../headers/game_engine_handles.hpp"
#include "../headers/game_engine_updates.hpp"

// FORWARD DECLARATIONS
void handle(bool gamePaused);
void update(int &soundVolume, int &musicVolume, int &scene, bool gamePaused);
void draw(SDL_Renderer *&renderer, int &scene, SDL_Texture *&background1Texture, float fps, bool gamePaused);
void render_text(const std::string &text, int x, int y, Uint8 redText, Uint8 greenText, Uint8 blueText, Uint8 alphaText, TTF_Font *font);

void add_buttons_to_dropdown_buttons() {
    scene2resolutionsDropdownButton.add_button_to_dropdown_list(scene2resolutionsDropdown1366x768Button);
    scene2resolutionsDropdownButton.add_button_to_dropdown_list(scene2resolutionsDropdown800x640Button);
    scene15FileDropdownButton.add_button_to_dropdown_list(scene15saveMapButton);
    scene15FileDropdownButton.add_button_to_dropdown_list(scene15loadMapButton);
    scene15FileDropdownButton.add_button_to_dropdown_list(scene15newMapButton);
    scene15FileDropdownButton.add_button_to_dropdown_list(scene15deleteMapButton);
    scene15FileDropdownButton.add_button_to_dropdown_list(scene15importMapButton);
}
void load_buttons_to_scene_vectors()
{
    // Scene 1 - Main menu
    scene1buttons.push_back(&scene1newGameButton);
    scene1buttons.push_back(&scene1settingsButton);
    scene1buttons.push_back(&scene1unlockablesButton);
    scene1buttons.push_back(&scene1scoreButton);
    scene1buttons.push_back(&scene1helpButton);
    scene1buttons.push_back(&scene1achievementsButton);
    scene1buttons.push_back(&scene1multiplayerButton);
    scene1buttons.push_back(&scene1levelEditorButton);
    scene1buttons.push_back(&scene1modStoreButton);
    scene1buttons.push_back(&scene1quitGameButton);
    // Scene 2 - Settings
    // col 1
    scene2buttons.push_back(&scene2ChangeFontButton);
    scene2buttons.push_back(&scene2ChangeLanguageButton);
    scene2buttons.push_back(&scene2changeKeymappingButton);
    scene2buttons.push_back(&scene2displayOnScreenKeysButton);
    // col 3
    scene2buttons.push_back(&scene2fullscreenToggleButton);
    scene2buttons.push_back(&scene2enableVsyncButton);
    scene2buttons.push_back(&scene2toggleFPSButton);
    scene2buttons.push_back(&scene2resolutionsDropdownButton);
    scene2resolutionsDropdownButtonVector.push_back(&scene2resolutionsDropdown1366x768Button);
    scene2resolutionsDropdownButtonVector.push_back(&scene2resolutionsDropdown800x640Button);
    // col 5
    scene2buttons.push_back(&scene2toggleSoundButton);
    scene2buttons.push_back(&scene2toggleMusicButton);
    scene2buttons.push_back(&scene2SFXSliderButton);
    scene2buttons.push_back(&scene2VolumeSliderButton);
    scene2buttons.push_back(&scene2scrollSpeedSliderButton);
    // col 8
    scene2buttons.push_back(&scene2returnToTitleButton);
    scene2buttons.push_back(&scene2returnToGameButton);
    scene2buttons.push_back(&scene2saveSettingsButton);
    scene2buttons.push_back(&scene2ResetToDefaultSettingsButton);

    // Scene 3 - Unlockables
    scene3buttons.push_back(&scene3returnToTitleButton);
    scene3buttons.push_back(&scene3creditsButton);
    scene3buttons.push_back(&scene3sandboxButton);
    scene3buttons.push_back(&scene3soundtrackButton);
    // Scene 4 - Scoreboard
    scene4buttons.push_back(&scene4submitNameButton);
    scene4buttons.push_back(&scene4inputPlayerNameButton);
    scene4buttons.push_back(&scene4returnToTitleButton);
    // Scene 5 - Help
    scene5buttons.push_back(&scene5returnToTitleButton);
    scene5buttons.push_back(&scene5backButton);
    scene5buttons.push_back(&scene5forwardButton);
    // Scene 6 - Achievements
    scene6buttons.push_back(&scene6returnToTitleButton);
    // scene 7 - Check for updates
    scene7buttons.push_back(&scene7returnToTitleButton);
    scene7buttons.push_back(&scene7updateButton);
    scene7buttons.push_back(&scene7cancelButton);
    // scene 8 - Online login
    scene8buttons.push_back(&scene8returnToTitleButton);
    scene8buttons.push_back(&scene8loginButton);
    scene8buttons.push_back(&scene8registerButton);
    scene8buttons.push_back(&scene8inputemailButton);
    scene8buttons.push_back(&scene8inputpasswordButton);
    // scene 9 - Create account
    scene9buttons.push_back(&scene9returnToTitleButton);
    scene9buttons.push_back(&scene9submitButton);
    scene9buttons.push_back(&scene9inputusernameButton);
    scene9buttons.push_back(&scene9inputemailButton);
    scene9buttons.push_back(&scene9inputpasswordNameButton);
    // scene 10 - Show policies
    scene10buttons.push_back(&scene10returnToTitleButton);
    scene10buttons.push_back(&scene10acceptPrivacyPolicyButton);
    scene10buttons.push_back(&scene10denyPrivacyPolicyButton);
    scene10buttons.push_back(&scene10acceptTermsPolicyButton);
    scene10buttons.push_back(&scene10denyTermsPolicyButton);
    // scene 11 - Multiplayer Lobby
    scene11buttons.push_back(&scene11returnToTitleButton);
    scene11buttons.push_back(&scene11createGameButton);
    scene11buttons.push_back(&scene11joinGameButton);
    scene11buttons.push_back(&scene11refreshGamesButton);
    scene11buttons.push_back(&scene11sendMessageButton);
    scene11buttons.push_back(&scene11addFriendButton);
    scene11buttons.push_back(&scene11refreshFriendsButton);
    // scene 12 - Keybindings
    scene12buttons.push_back(&scene12returnToTitleButton);
    scene12buttons.push_back(&scene12acceptButton);
    scene12buttons.push_back(&scene12resetButton);
    // scene 13 - Create Game
    scene13buttons.push_back(&scene13cancelButton);
    scene13buttons.push_back(&scene13createButton);
    // scene 14 - Credits
    scene14buttons.push_back(&scene14returnToTitleButton);
    // scene 15 - Level editor
    scene15buttons.push_back(&scene15FileDropdownButton);
    scene15buttons.push_back(&scene15returnToTitleButton);
    scene15FileDropdownButtonVector.push_back(&scene15saveMapButton);
    scene15FileDropdownButtonVector.push_back(&scene15loadMapButton);
    scene15FileDropdownButtonVector.push_back(&scene15newMapButton);
    scene15FileDropdownButtonVector.push_back(&scene15deleteMapButton);
    scene15FileDropdownButtonVector.push_back(&scene15importMapButton);
    // scene 16 - 
    scene16buttons.push_back(&scene16returnToTitleButton);
    // scene 17
    scene17buttons.push_back(&scene17returnToTitleButton);
    // scene 18
    scene18buttons.push_back(&scene18returnToTitleButton);
    // scene 19
    scene19buttons.push_back(&scene19returnToTitleButton);
    // scene 20
    scene20buttons.push_back(&scene20returnToTitleButton);
    // scene 21
    scene21buttons.push_back(&scene21returnToTitleButton);
    // scene 22 - mod store
    scene22buttons.push_back(&scene22returnToTitleButton);
    // scene 23
    scene23buttons.push_back(&scene23returnToTitleButton);
    // scene 24
    scene24buttons.push_back(&scene24returnToTitleButton);
    // scene 25
    scene25buttons.push_back(&scene25returnToTitleButton);
    // scene 26 - soundtrack
    scene26buttons.push_back(&scene26returnToTitleButton);
    // scene 27 - player select
    scene27buttons.push_back(&scene27returnToTitleButton);
    scene27buttons.push_back(&scene27backButton);
    scene27buttons.push_back(&scene27nextButton);
    scene27buttons.push_back(&scene27acceptButton);
    scene27buttons.push_back(&scene27denyButton);
    // scene 28 - cutscene
    scene28buttons.push_back(&scene28returnToTitleButton);
    // scene 29
    scene29buttons.push_back(&scene29returnToTitleButton);
    // scene 30
    scene30buttons.push_back(&scene30returnToTitleButton);
    // scene 31
    scene31buttons.push_back(&scene31returnToTitleButton);
    // scene - any gameplay scene
    sceneGameplaybuttons.push_back(&sceneGameplayMenuButton);
    sceneGameplaybuttons.push_back(&sceneGameplayUpButton);
    sceneGameplaybuttons.push_back(&sceneGameplayDownButton);
    sceneGameplaybuttons.push_back(&sceneGameplayLeftButton);
    sceneGameplaybuttons.push_back(&sceneGameplayRightButton);
    sceneGameplaybuttons.push_back(&sceneGameplayUseButton);
}
void load_buttons_to_all_buttons_vector(std::vector<BaseButton *> &allButtons)
{
    allButtons.insert(allButtons.end(), scene1buttons.begin(), scene1buttons.end());
    allButtons.insert(allButtons.end(), scene2buttons.begin(), scene2buttons.end());
    allButtons.insert(allButtons.end(), scene2resolutionsDropdownButtonVector.begin(), scene2resolutionsDropdownButtonVector.end());
    allButtons.insert(allButtons.end(), scene3buttons.begin(), scene3buttons.end());
    allButtons.insert(allButtons.end(), scene4buttons.begin(), scene4buttons.end());
    allButtons.insert(allButtons.end(), scene5buttons.begin(), scene5buttons.end());
    allButtons.insert(allButtons.end(), scene6buttons.begin(), scene6buttons.end());
    allButtons.insert(allButtons.end(), scene7buttons.begin(), scene7buttons.end());
    allButtons.insert(allButtons.end(), scene8buttons.begin(), scene8buttons.end());
    allButtons.insert(allButtons.end(), scene9buttons.begin(), scene9buttons.end());
    allButtons.insert(allButtons.end(), scene10buttons.begin(), scene10buttons.end());
    allButtons.insert(allButtons.end(), scene11buttons.begin(), scene11buttons.end());
    allButtons.insert(allButtons.end(), scene12buttons.begin(), scene12buttons.end());
    allButtons.insert(allButtons.end(), scene13buttons.begin(), scene13buttons.end());
    allButtons.insert(allButtons.end(), scene14buttons.begin(), scene14buttons.end());
    allButtons.insert(allButtons.end(), scene15buttons.begin(), scene15buttons.end());
    allButtons.insert(allButtons.end(), scene15FileDropdownButtonVector.begin(), scene15FileDropdownButtonVector.end());
    allButtons.insert(allButtons.end(), scene16buttons.begin(), scene16buttons.end());
    allButtons.insert(allButtons.end(), scene17buttons.begin(), scene17buttons.end());
    allButtons.insert(allButtons.end(), scene18buttons.begin(), scene18buttons.end());
    allButtons.insert(allButtons.end(), scene19buttons.begin(), scene19buttons.end());
    allButtons.insert(allButtons.end(), scene20buttons.begin(), scene20buttons.end());
    allButtons.insert(allButtons.end(), scene21buttons.begin(), scene21buttons.end());
    allButtons.insert(allButtons.end(), scene22buttons.begin(), scene22buttons.end());
    allButtons.insert(allButtons.end(), scene23buttons.begin(), scene23buttons.end());
    allButtons.insert(allButtons.end(), scene24buttons.begin(), scene24buttons.end());
    allButtons.insert(allButtons.end(), scene25buttons.begin(), scene25buttons.end());
    allButtons.insert(allButtons.end(), scene26buttons.begin(), scene26buttons.end());
    allButtons.insert(allButtons.end(), scene27buttons.begin(), scene27buttons.end());
    allButtons.insert(allButtons.end(), scene28buttons.begin(), scene28buttons.end());
    allButtons.insert(allButtons.end(), scene29buttons.begin(), scene29buttons.end());
    allButtons.insert(allButtons.end(), scene30buttons.begin(), scene30buttons.end());
    allButtons.insert(allButtons.end(), scene31buttons.begin(), scene31buttons.end());
    allButtons.insert(allButtons.end(), sceneGameplaybuttons.begin(), sceneGameplaybuttons.end());
}
void initialise_button_renderer(SDL_Renderer *renderer)
{
    for (BaseButton *button : allButtons)
    {
        button->set_renderer(renderer);
    }
}
void initialise_button_textures(std::vector<BaseButton *> &allButtons)
{
    for (BaseButton *button : allButtons)
    {
        button->set_button_texture();
        if (SliderButton *x = dynamic_cast<SliderButton *>(button))
        {
            x->set_slider_dot_texture();
        }
    }
}
void initialise_button_fonts(std::vector<BaseButton *> &allButtons)
{
    for (BaseButton *button : allButtons)
    {
        button->set_font_size(defaultFont, 24);
    }
}

SDL_Texture *load_texture(const std::string &textureFilePath)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, textureFilePath.c_str());
    if (!texture)
    {
        logger.log_critical("Error: Failed to load texture: " + textureFilePath + ": " + std::string(IMG_GetError()));
    }
    return texture;
}
Mix_Chunk *load_sound(const std::string sfxFilePath)
{
    Mix_Chunk *sound = Mix_LoadWAV(sfxFilePath.c_str());
    if (sound == nullptr)
    {
        logger.log_critical("Error: Failed to load sound: " + sfxFilePath + ": " + Mix_GetError());
    }
    return sound;
}
TTF_Font *load_font(const std::string &fontFilePath, const int &fontSize)
{
    TTF_Font *font = TTF_OpenFont(fontFilePath.c_str(), fontSize);
    if (!font)
    {
        logger.log_critical("Error: Failed to load font: " + fontFilePath + ": " + std::string(TTF_GetError()));
    }
    return font;
}
void load_controllers()
{
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
        {
            SDL_GameController *controller = SDL_GameControllerOpen(i);
            if (controller)
            {
                SDL_JoystickID instance_id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
                for (Entity *e : entities)
                {
                    if (Player *player = dynamic_cast<Player *>(e))
                    {
                        if (player->get_controller() == nullptr)
                        {
                            player->set_controller(controller);
                            player->set_controller_instance_id(instance_id);
                            std::cout << "Controller " << i << " is open and assigned to player " << player->get_player_id() << "." << std::endl;
                            break;
                        }
                    }
                }
            }
            else
            {
                logger.log_critical("Could not open controller " + std::to_string(i) + ": " + std::string(SDL_GetError()));
            }
        }
    }
}
void load_textures()
{
    // backgrounds
    background1Texture = load_texture("assets/graphics/backgrounds/Background 01/PNG/1920x1080.png");

    // HUD textures
    heartTexture = load_texture("assets/graphics/HUD/heart.png");
    hearts2Texture = load_texture("assets/graphics/HUD/2hearts.png");
    hearts3Texture = load_texture("assets/graphics/HUD/3hearts.png");
    hearts4Texture = load_texture("assets/graphics/HUD/4hearts.png");
    hearts5Texture = load_texture("assets/graphics/HUD/5hearts.png");
    timerTexture = load_texture("assets/graphics/HUD/timer.png");
}
void load_sounds()
{
    barkSound = load_sound("assets/sounds/sound-effects/wavs/Single bark of a dog - Pixabay.wav");
    treeSound = load_sound("assets/sounds/sound-effects/wavs/Knife thrust into wall- Pixabay.wav");
    waterSound = load_sound("assets/sounds/sound-effects/wavs/Water splash - Pixabay.wav");
    heartSound = load_sound("assets/sounds/sound-effects/wavs/Level Up  2 UNIVERSFIELD.wav");
    loseGameSound = load_sound("assets/sounds/sound-effects/wavs/failure drum sound effect 2 - Pixabay.wav");
    winGameSound = load_sound("assets/sounds/sound-effects/wavs/Success Fanfare Trumpets - Pixabay.wav");
    moneySound = load_sound("assets/sounds/sound-effects/wavs/Money Pickup 2 - Pixabay.wav");
    drinkSound = load_sound("assets/sounds/sound-effects/wavs/Health Pickup - Pixabay.wav");
    paperSound = load_sound("assets/sounds/sound-effects/wavs/pickup_paper - Pixabay.wav");
    shootSound = load_sound("assets/sounds/sound-effects/wavs/Shooting Sound FX - lucadialessandro.wav");
    bumpSound = load_sound("assets/sounds/sound-effects/wavs/bump 7 - Pixabay.wav");
    popSound = load_sound("assets/sounds/sound-effects/wavs/Happy Pop 2 - floraphonic.wav");
    unlockSound = load_sound("assets/sounds/sound-effects/wavs/Key Twist in lock - Pixabay.wav");
    lockSound = load_sound("assets/sounds/sound-effects/wavs/Lock the door - Pixabay.wav");
    explosionSound = load_sound("assets/sounds/sound-effects/wavs/Medium Explosion - Pixabay.wav");
    clothesSound = load_sound("assets/sounds/sound-effects/wavs/clothes drop 2 - Pixabay.wav");
}
void load_music(const std::string &songTitle)
{
    if (musicPlaying)
    {
        music = Mix_LoadMUS(songTitle.c_str());
        if (!music)
        {
            logger.log_critical("Error: Failed to load music: " + std::string(Mix_GetError()));
            music = nullptr;
        }
        else
        {
            Mix_PlayMusic(music, -1); // Set loops to -1 for infinite looping
            logger.log_non_critical("Music playing is: " + songTitle);
        }
    }
}
void load_fonts()
{
    defaultFont = load_font("assets/fonts/noto-sans/NotoSans-Regular.ttf", 24);

    europeanfont24 = load_font("assets/fonts/noto-sans/NotoSans-Regular.ttf", 24);
    europeanfont36 = load_font("assets/fonts/noto-sans/NotoSans-Regular.ttf", 36);
    europeanfont48 = load_font("assets/fonts/noto-sans/NotoSans-Regular.ttf", 48);
    europeanBoldfont24 = load_font("assets/fonts/noto-sans/NotoSans-Bold.ttf", 24);
    europeanBoldfont36 = load_font("assets/fonts/noto-sans/NotoSans-Bold.ttf", 36);
    europeanBoldfont48 = load_font("assets/fonts/noto-sans/NotoSans-Bold.ttf", 48);

    japanesefont24 = load_font("assets/fonts/noto-sans/NotoSansJP-Regular.ttf", 24);
    japanesefont36 = load_font("assets/fonts/noto-sans/NotoSansJP-Regular.ttf", 36);
    japanesefont48 = load_font("assets/fonts/noto-sans/NotoSansJP-Regular.ttf", 48);
    japaneseBoldfont24 = load_font("assets/fonts/noto-sans/NotoSansJP-Bold.ttf", 24);
    japaneseBoldfont36 = load_font("assets/fonts/noto-sans/NotoSansJP-Bold.ttf", 36);
    japaneseBoldfont48 = load_font("assets/fonts/noto-sans/NotoSansJP-Bold.ttf", 48);

    thaifont24 = load_font("assets/fonts/noto-sans/NotoSansThai-Regular.ttf", 24);
    thaifont36 = load_font("assets/fonts/noto-sans/NotoSansThai-Regular.ttf", 36);
    thaifont48 = load_font("assets/fonts/noto-sans/NotoSansThai-Regular.ttf", 48);
    thaiBoldfont24 = load_font("assets/fonts/noto-sans/NotoSansThai-Bold.ttf", 24);
    thaiBoldfont36 = load_font("assets/fonts/noto-sans/NotoSansThai-Bold.ttf", 36);
    thaiBoldfont48 = load_font("assets/fonts/noto-sans/NotoSansThai-Bold.ttf", 48);

    devanagarifont24 = load_font("assets/fonts/noto-sans/NotoSansDevanagari-Regular.ttf", 24);
    devanagarifont36 = load_font("assets/fonts/noto-sans/NotoSansDevanagari-Regular.ttf", 36);
    devanagarifont48 = load_font("assets/fonts/noto-sans/NotoSansDevanagari-Regular.ttf", 48);
    devanagariBoldfont24 = load_font("assets/fonts/noto-sans/NotoSansDevanagari-Bold.ttf", 24);
    devanagariBoldfont36 = load_font("assets/fonts/noto-sans/NotoSansDevanagari-Bold.ttf", 36);
    devanagariBoldfont48 = load_font("assets/fonts/noto-sans/NotoSansDevanagari-Bold.ttf", 48);

    chinesefont24 = load_font("assets/fonts/noto-sans/NotoSansTC-Regular.ttf", 24);
    chinesefont36 = load_font("assets/fonts/noto-sans/NotoSansTC-Regular.ttf", 36);
    chinesefont48 = load_font("assets/fonts/noto-sans/NotoSansTC-Regular.ttf", 48);
    chineseBoldfont24 = load_font("assets/fonts/noto-sans/NotoSansTC-Bold.ttf", 24);
    chineseBoldfont36 = load_font("assets/fonts/noto-sans/NotoSansTC-Bold.ttf", 36);
    chineseBoldfont48 = load_font("assets/fonts/noto-sans/NotoSansTC-Bold.ttf", 48);

    arabicfont24 = load_font("assets/fonts/noto-sans/NotoSansArabic-Regular.ttf", 24);
    arabicfont36 = load_font("assets/fonts/noto-sans/NotoSansArabic-Regular.ttf", 36);
    arabicfont48 = load_font("assets/fonts/noto-sans/NotoSansArabic-Regular.ttf", 48);
    arabicBoldfont24 = load_font("assets/fonts/noto-sans/NotoSansArabic-Bold.ttf", 24);
    arabicBoldfont36 = load_font("assets/fonts/noto-sans/NotoSansArabic-Bold.ttf", 36);
    arabicBoldfont48 = load_font("assets/fonts/noto-sans/NotoSansArabic-Bold.ttf", 48);

    geezfont24 = load_font("assets/fonts/noto-sans/NotoSansEthiopic-Regular.ttf", 24);
    geezfont36 = load_font("assets/fonts/noto-sans/NotoSansEthiopic-Regular.ttf", 36);
    geezfont48 = load_font("assets/fonts/noto-sans/NotoSansEthiopic-Regular.ttf", 48);
    geezBoldfont24 = load_font("assets/fonts/noto-sans/NotoSansEthiopic-Bold.ttf", 24);
    geezBoldfont36 = load_font("assets/fonts/noto-sans/NotoSansEthiopic-Bold.ttf", 36);
    geezBoldfont48 = load_font("assets/fonts/noto-sans/NotoSansEthiopic-Bold.ttf", 48);
}
void set_font(const std::string &language)
{
    // This function is to change the font file, to support other unicode langauges
    std::cout << "Starting: set_font_language()" << std::endl;
    if (language == "English" || language == "Greek" || language == "Latin")
    {
        {
            font24 = europeanfont24;
            font36 = europeanfont36;
            font48 = europeanfont48;
            fontBold24 = europeanBoldfont24;
            fontBold36 = europeanBoldfont36;
            fontBold48 = europeanBoldfont48;
        }
    }
    else if (language == "japanese")
    {
        font24 = japanesefont24;
        font36 = japanesefont36;
        font48 = japanesefont48;
        fontBold24 = japaneseBoldfont24;
        fontBold36 = japaneseBoldfont36;
        fontBold48 = japaneseBoldfont48;
    }
    else if (language == "thai")
    {
        font24 = thaifont24;
        font36 = thaifont36;
        font48 = thaifont48;
        fontBold24 = thaiBoldfont24;
        fontBold36 = thaiBoldfont36;
        fontBold48 = thaiBoldfont48;
    }
    else if (language == "devanagari")
    {
        font24 = devanagarifont24;
        font36 = devanagarifont36;
        font48 = devanagarifont48;
        fontBold24 = devanagariBoldfont24;
        fontBold36 = devanagariBoldfont36;
        fontBold48 = devanagariBoldfont48;
    }
    else if (language == "chinese")
    {
        font24 = chinesefont24;
        font36 = chinesefont36;
        font48 = chinesefont48;
        fontBold24 = chineseBoldfont24;
        fontBold36 = chineseBoldfont36;
        fontBold48 = chineseBoldfont48;
    }
    else if (language == "arabic")
    {
        font24 = arabicfont24;
        font36 = arabicfont36;
        font48 = arabicfont48;
        fontBold24 = arabicBoldfont24;
        fontBold36 = arabicBoldfont36;
        fontBold48 = arabicBoldfont48;
    }
    else if (language == "geez")
    {
        font24 = geezfont24;
        font36 = geezfont36;
        font48 = geezfont48;
        fontBold24 = geezBoldfont24;
        fontBold36 = geezBoldfont36;
        fontBold48 = geezBoldfont48;
    }
}
void render_text(const std::string &text, int x, int y, Uint8 redText, Uint8 greenText, Uint8 blueText, Uint8 alphaText, TTF_Font *font)
{
    SDL_Color textColor = {redText, greenText, blueText, alphaText};
    SDL_Surface *textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), textColor);

    if (textSurface)
    {
        int textWidth, textHeight;
        // Calculate textWidth and textHeight using TTF_SizeText
        TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);

        if (textTexture)
        {
            SDL_Rect textRect = {x, y, textWidth, textHeight};
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        }
        SDL_DestroyTexture(textTexture);
    }
}
void start_SDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logger.log_critical("Error: Failed to initialise SDL" + std::string(SDL_GetError()));
        exit(1);
    }
    else
    {
        logger.log_critical("Success: initialised: SDL2");
    }

    if (TTF_Init() != 0)
    {
        logger.log_critical("Error: Failed to initialize SDL Font: " + std::string(TTF_GetError()));
        SDL_Quit();
        exit(1);
    }
    else
    {
        logger.log_critical("Success: initialised: SDL2 TTF");
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        logger.log_critical("Error: Failed to initialize SDL IMG: " + std::string(IMG_GetError()));
        SDL_Quit();
        exit(1);
    }
    else
    {
        logger.log_critical("Success: initialised: SDL2 Image");
    }

    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        logger.log_critical("Error: Failed to initialize Audio: " + std::string(Mix_GetError()));
        SDL_Quit();
        exit(1);
    }
    else
    {
        logger.log_critical("Success: initialised: SDL2 Mixer");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        logger.log_critical("Error: Failed to open audio channel: " + std::string(Mix_GetError()));
    }
    else
    {
        logger.log_critical("Success: initialised: SDL2 Mixer Audio");
    }

    window = SDL_CreateWindow("BubbleUp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    if (!window)
    {
        logger.log_critical("Error: Failed to create SDL Window: " + std::string(SDL_GetError()));
        SDL_Quit();
        exit(1);
    }
    else
    {
        logger.log_critical("Success: initialised: SDL2 window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        logger.log_critical("Error: Failed to create Renderer: " + std::string(SDL_GetError()));
        SDL_Quit();
        exit(1);
    }
    else
    {
        logger.log_critical("Success: initialised: SDL2 renderer");
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Set blend mode

    load_fonts();
    set_font(language);
    load_textures();
    load_sounds();
    add_buttons_to_dropdown_buttons();
    load_buttons_to_scene_vectors();
    load_buttons_to_all_buttons_vector(allButtons);
    initialise_button_renderer(renderer);
    initialise_button_textures(allButtons);
    initialise_button_fonts(allButtons);
    FFmpegVideoPlayer videoPlayer("assets/videos/sample.mp4", "assets/videos/sample.mp3", window, renderer);
    videoPlayer.playVideo();
    load_music("assets/sounds/music/Game Time - moodmode-studio.mp3");
}
void run_SDL()
{
    bool gamePaused{};

    // FPS variables
    int startTime, endTime{};
    float fps, frameCount, elapsedTime{};

    while (!quitEventLoop)
    {
        startTime = SDL_GetTicks(); // FPS

        handle(gamePaused);
        update(soundVolume, musicVolume, scene, gamePaused);
        draw(renderer, scene, background1Texture, fps, gamePaused);

        // FPS calculation, drawn in draw() with render_text(fps)
        frameCount++;
        endTime = SDL_GetTicks();                      // FPS
        elapsedTime = (endTime - startTime) / 1000.0f; // convert from ms to seconds
        if (elapsedTime > 0)
        {
            fps = frameCount / elapsedTime;
            frameCount = 0.0f;
        }
    }
}
void exit_SDL()
{
    // Delete entities that were dynamically assigned memory on the Heap
    logger.log_critical("Closing: dynamically created entities...");
    for (Entity *e : entities)
    {
        if (dynamic_cast<Player *>(e) == nullptr) // look for anything NOT a player
            delete e;
    }

    logger.log_critical("Closing: Vectors...");
    entities.clear();
    scene1buttons.clear();
    scene2buttons.clear();
    scene3buttons.clear();
    scene4buttons.clear();
    scene5buttons.clear();
    scene6buttons.clear();
    scene7buttons.clear();
    scene8buttons.clear();
    scene9buttons.clear();
    scene10buttons.clear();
    scene11buttons.clear();
    scene12buttons.clear();
    allButtons.clear();

    logger.log_critical("Closing: sound effects...");
    Mix_FreeChunk(moneySound);
    Mix_FreeChunk(drinkSound);
    Mix_FreeChunk(paperSound);
    Mix_FreeChunk(shootSound);
    Mix_FreeChunk(bumpSound);
    Mix_FreeChunk(popSound);
    Mix_FreeChunk(unlockSound);
    Mix_FreeChunk(lockSound);
    Mix_FreeChunk(winGameSound);
    Mix_FreeChunk(loseGameSound);
    Mix_FreeChunk(explosionSound);

    logger.log_critical("Closing: music...");
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    Mix_CloseAudio();

    logger.log_critical("Closing: textures...");
    SDL_DestroyTexture(background1Texture);

    logger.log_critical("Closing: window...");
    SDL_DestroyRenderer(renderer);
    logger.log_critical("Closing: renderer...");
    SDL_DestroyWindow(window);

    logger.log_critical("Closing: SDL Libraries...");
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    logger.log_critical("Success: Quit BubbleUP game engine");
}

void handle(bool gamePaused)
{
    SDL_Event event{};
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            std::cout << "Game Quitting" << std::endl;
            quitEventLoop = true;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            keyPressed = true;
            switch (scene)
            {
            case 1:
                handle_keyboard_scene_1(event);
                break;
            case 2:
                handle_keyboard_scene_2(event, gamePaused);
                break;
            case 3:
                handle_keyboard_scene_3(event);
                break;
            case 4:
                handle_keyboard_scene_4(event);
                break;
            case 5:
                handle_keyboard_scene_5(event);
                break;
            case 6:
                handle_keyboard_scene_6(event);
                break;
            case 7:
                handle_keyboard_scene_7(event);
                break;
            case 8:
                handle_keyboard_scene_8(event);
                break;
            case 9:
                handle_keyboard_scene_9(event);
                break;
            case 10:
                handle_keyboard_scene_10(event);
                break;
            case 11:
                handle_keyboard_scene_11(event);
                break;
            case 12:
                handle_keyboard_scene_12(event);
                break;
            case 13:
                handle_keyboard_scene_13(event);
                break;
            case 14:
                handle_keyboard_scene_14(event);
                break;
            case 15:
                handle_keyboard_scene_15(event);
                break;
            case 16:
                handle_keyboard_scene_16(event);
                break;
            case 17:
                handle_keyboard_scene_17(event);
                break;
            case 18:
                handle_keyboard_scene_18(event);
                break;
            case 19:
                handle_keyboard_scene_19(event);
                break;
            case 20:
                handle_keyboard_scene_20(event);
                break;
            case 21:
                handle_keyboard_scene_21(event);
                break;
            case 22:
                handle_keyboard_scene_22(event);
                break;
            case 23:
                handle_keyboard_scene_23(event);
                break;
            case 24:
                handle_keyboard_scene_24(event);
                break;
            case 25:
                handle_keyboard_scene_25(event);
                break;
            case 26:
                handle_keyboard_scene_26(event);
                break;
            case 27:
                handle_keyboard_scene_27(event);
                break;
            case 28:
                handle_keyboard_scene_28(event);
                break;
            case 29:
                handle_keyboard_scene_29(event);
                break;
            case 30:
                handle_keyboard_scene_30(event);
                break;
            case 31:
                handle_keyboard_scene_31(event);
                break;
            case 100:
            case 101:
            case 102:
            case 103:
            case 104:
            case 105:
            case 106:
            case 107:
            case 108:
            case 109:
            case 110:
            case 111:
            case 150:
                handle_keyboard_scene_gameplay(event, gamePaused);
                break;
            default:
                handle_keyboard_scene_gameplay(event, gamePaused);
                break;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            keyPressed = false;
            switch (scene)
            {
            case 1:
                handle_keyboard_scene_1(event);
                break;
            case 2:
                handle_keyboard_scene_2(event, gamePaused);
                break;
            case 3:
                handle_keyboard_scene_3(event);
                break;
            case 4:
                handle_keyboard_scene_4(event);
                break;
            case 5:
                handle_keyboard_scene_5(event);
                break;
            case 6:
                handle_keyboard_scene_6(event);
                break;
            case 7:
                handle_keyboard_scene_7(event);
                break;
            case 8:
                handle_keyboard_scene_8(event);
                break;
            case 9:
                handle_keyboard_scene_9(event);
                break;
            case 10:
                handle_keyboard_scene_10(event);
                break;
            case 11:
                handle_keyboard_scene_11(event);
                break;
            case 12:
                handle_keyboard_scene_12(event);
                break;
            case 13:
                handle_keyboard_scene_13(event);
                break;
            case 14:
                handle_keyboard_scene_14(event);
                break;
            case 15:
                handle_keyboard_scene_15(event);
                break;
            case 16:
                handle_keyboard_scene_16(event);
                break;
            case 17:
                handle_keyboard_scene_17(event);
                break;
            case 18:
                handle_keyboard_scene_18(event);
                break;
            case 19:
                handle_keyboard_scene_19(event);
                break;
            case 20:
                handle_keyboard_scene_20(event);
                break;
            case 21:
                handle_keyboard_scene_21(event);
                break;
            case 22:
                handle_keyboard_scene_22(event);
                break;
            case 23:
                handle_keyboard_scene_23(event);
                break;
            case 24:
                handle_keyboard_scene_24(event);
                break;
            case 25:
                handle_keyboard_scene_25(event);
                break;
            case 26:
                handle_keyboard_scene_26(event);
                break;
            case 27:
                handle_keyboard_scene_27(event);
                break;
            case 28:
                handle_keyboard_scene_28(event);
                break;
            case 29:
                handle_keyboard_scene_29(event);
                break;
            case 30:
                handle_keyboard_scene_30(event);
                break;
            case 31:
                handle_keyboard_scene_31(event);
                break;
            case 100:
            case 101:
            case 102:
            case 103:
            case 104:
            case 105:
            case 106:
            case 107:
            case 108:
            case 109:
            case 110:
            case 111:
            case 150:
                handle_keyboard_scene_gameplay(event, gamePaused);
                break;
            default:
                handle_keyboard_scene_gameplay(event, gamePaused);
                break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_FINGERDOWN || event.type == SDL_MULTIGESTURE)
        {
            mousePressed = true;
            int mouseX, mouseY;
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
            }
            else if (event.type == SDL_FINGERDOWN || event.type == SDL_MULTIGESTURE)
            {
                mouseX = static_cast<int>(event.tfinger.x * SCREEN_WIDTH);
                mouseY = static_cast<int>(event.tfinger.y * SCREEN_HEIGHT);
            }
            switch (scene)
            {
            case 1:
                handle_mouse_scene_1(mouseX, mouseY);
                break;
            case 2:
                handle_mouse_scene_2(mouseX, mouseY, gamePaused);
                break;
            case 3:
                handle_mouse_scene_3(mouseX, mouseY);
                break;
            case 4:
                handle_mouse_scene_4(mouseX, mouseY);
                break;
            case 5:
                handle_mouse_scene_5(mouseX, mouseY);
                break;
            case 6:
                handle_mouse_scene_6(mouseX, mouseY);
                break;
            case 7:
                handle_mouse_scene_7(mouseX, mouseY);
                break;
            case 8:
                handle_mouse_scene_8(mouseX, mouseY);
                break;
            case 9:
                handle_mouse_scene_9(mouseX, mouseY);
                break;
            case 10:
                handle_mouse_scene_10(mouseX, mouseY);
                break;
            case 11:
                handle_mouse_scene_11(mouseX, mouseY);
                break;
            case 12:
                handle_mouse_scene_12(mouseX, mouseY);
                break;
            case 13:
                handle_mouse_scene_13(mouseX, mouseY);
                break;
            case 14:
                handle_mouse_scene_14(mouseX, mouseY);
                break;
            case 15:
                handle_mouse_scene_15(mouseX, mouseY);
                break;
            case 16:
                handle_mouse_scene_16(mouseX, mouseY);
                break;
            case 17:
                handle_mouse_scene_17(mouseX, mouseY);
                break;
            case 18:
                handle_mouse_scene_18(mouseX, mouseY);
                break;
            case 19:
                handle_mouse_scene_19(mouseX, mouseY);
                break;
            case 20:
                handle_mouse_scene_20(mouseX, mouseY);
                break;
            case 21:
                handle_mouse_scene_21(mouseX, mouseY);
                break;
            case 22:
                handle_mouse_scene_22(mouseX, mouseY);
                break;
            case 23:
                handle_mouse_scene_23(mouseX, mouseY);
                break;
            case 24:
                handle_mouse_scene_24(mouseX, mouseY);
                break;
            case 25:
                handle_mouse_scene_25(mouseX, mouseY);
                break;
            case 26:
                handle_mouse_scene_26(mouseX, mouseY);
                break;
            case 27:
                handle_mouse_scene_27(mouseX, mouseY);
                break;
            case 28:
                handle_mouse_scene_28(mouseX, mouseY);
                break;
            case 29:
                handle_mouse_scene_29(mouseX, mouseY);
                break;
            case 30:
                handle_mouse_scene_30(mouseX, mouseY);
                break;
            case 31:
                handle_mouse_scene_31(mouseX, mouseY);
                break;
            case 100:
            case 101:
            case 102:
            case 103:
            case 104:
            case 105:
            case 106:
            case 107:
            case 108:
            case 109:
            case 110:
            case 111:
            case 150:
                handle_mouse_scene_gameplay(mouseX, mouseY);
                break;
            default:
                handle_mouse_scene_gameplay(mouseX, mouseY);
                break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            mousePressed = false;
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            if (mousePressed)
            {
                for (BaseButton *button : allButtons)
                {
                    if (button->is_selected())
                    {
                        if (SliderButton *b = dynamic_cast<SliderButton *>(button))
                        {
                            int mouseX, mouseY;
                            SDL_GetMouseState(&mouseX, &mouseY);
                            int x = mouseX - xDragOffset;
                            b->set_dot_rect_x_pos(x);
                            int y = mouseY - yDragOffset;
                            b->set_dot_rect_y_pos(y);

                            // Ensure texture stays within the bounds of the SliderButton rectangle
                            if (b->get_dot_rect().x < button->get_rect().x)
                            {
                                b->set_dot_rect_x_pos(button->get_rect().x);
                            }
                            else if (b->get_dot_rect().x + b->get_dot_rect().w > button->get_rect().x + button->get_rect().w)
                            {
                                int xPos = button->get_rect().x + button->get_rect().w - b->get_dot_rect().w;
                                b->set_dot_rect_x_pos(xPos);
                            }

                            if (b->get_dot_rect().y < button->get_rect().y)
                            {
                                b->set_dot_rect_y_pos(button->get_rect().y);
                            }
                            else if (b->get_dot_rect().y + b->get_dot_rect().h > button->get_rect().y + button->get_rect().h)
                            {
                                int yPos = button->get_rect().y + button->get_rect().h - b->get_dot_rect().h;
                                b->set_dot_rect_y_pos(yPos);
                            }

                            if (scene2SFXSliderButton.is_selected())
                            {
                                double relativePosition = (b->get_dot_rect().x - button->get_rect().x) / (double)(button->get_rect().w - b->get_dot_rect().w);
                                soundVolume = static_cast<int>(relativePosition * 100);
                                soundVolume = std::max<int>(0, std::min<int>(100, soundVolume));
                            }
                            else if (scene2VolumeSliderButton.is_selected())
                            {
                                double relativePosition = (b->get_dot_rect().x - button->get_rect().x) / (double)(button->get_rect().w - b->get_dot_rect().w);
                                musicVolume = static_cast<int>(relativePosition * 100);
                                musicVolume = std::max<int>(0, std::min<int>(100, musicVolume));
                            }
                            else if (scene2scrollSpeedSliderButton.is_selected())
                            {
                                double relativePosition = (b->get_dot_rect().x - button->get_rect().x) / (double)(button->get_rect().w - b->get_dot_rect().w);
                                scrollSpeed = static_cast<int>(relativePosition * 100);
                                scrollSpeed = std::max<int>(0, std::min<int>(100, scrollSpeed));
                            }
                        }
                    }
                }
            }
        }
        else if (event.type == SDL_MOUSEWHEEL)
        {
            if (event.wheel.y > 0)
            {
                std::cout << "Mouse wheel moved UP" << std::endl;
                scrollYpos -= scrollSpeed; // Scroll up
            }
            else if (event.wheel.y < 0)
            {
                std::cout << "Mouse wheel moved DOWN" << std::endl;
                scrollYpos += scrollSpeed; // Scroll down
            }
        }
        else if (event.type == SDL_CONTROLLERBUTTONDOWN)
        {
            keyPressed = true;
            SDL_ControllerButtonEvent controllerButtonEvent = event.cbutton;
            int button = controllerButtonEvent.button;

            switch (scene)
            {
            case 1:
                handle_gamepad_scene_1(button);
                break;
            case 2:
                handle_gamepad_scene_2(button, gamePaused);
                break;
            case 3:
                handle_gamepad_scene_3(button);
                break;
            case 4:
                handle_gamepad_scene_4(button);
                break;
            case 5:
                handle_gamepad_scene_5(button);
                break;
            case 6:
                handle_gamepad_scene_6(button);
                break;
            case 7:
                handle_gamepad_scene_7(button);
                break;
            case 8:
                handle_gamepad_scene_8(button);
                break;
            case 9:
                handle_gamepad_scene_9(button);
                break;
            case 10:
                handle_gamepad_scene_10(button);
                break;
            case 11:
                handle_gamepad_scene_11(button);
                break;
            case 12:
                handle_gamepad_scene_12(button);
                break;
            case 13:
                handle_gamepad_scene_13(button);
                break;
            case 14:
                handle_gamepad_scene_14(button);
                break;
            case 15:
                handle_gamepad_scene_15(button);
                break;
            case 16:
                handle_gamepad_scene_16(button);
                break;
            case 17:
                handle_gamepad_scene_17(button);
                break;
            case 18:
                handle_gamepad_scene_18(button);
                break;
            case 19:
                handle_gamepad_scene_19(button);
                break;
            case 20:
                handle_gamepad_scene_20(button);
                break;
            case 21:
                handle_gamepad_scene_21(button);
                break;
            case 22:
                handle_gamepad_scene_22(button);
                break;
            case 23:
                handle_gamepad_scene_23(button);
                break;
            case 24:
                handle_gamepad_scene_24(button);
                break;
            case 25:
                handle_gamepad_scene_25(button);
                break;
            case 26:
                handle_gamepad_scene_26(button);
                break;
            case 27:
                handle_gamepad_scene_27(button);
                break;
            case 28:
                handle_gamepad_scene_28(button);
                break;
            case 29:
                handle_gamepad_scene_29(button);
                break;
            case 30:
                handle_gamepad_scene_30(button);
                break;
            case 31:
                handle_gamepad_scene_31(button);
                break;
            case 100:
            case 101:
            case 102:
            case 103:
            case 104:
            case 105:
            case 106:
            case 107:
            case 108:
            case 109:
            case 110:
            case 111:
            case 150:
                handle_gamepad_scene_gameplay(button, gamePaused);
                break;
            default:
                handle_gamepad_scene_gameplay(button, gamePaused);
                break;
            }
        }
        else if (event.type == SDL_CONTROLLERBUTTONUP)
        {
            keyPressed = false;
            SDL_ControllerButtonEvent controllerButtonEvent = event.cbutton;
            int button = controllerButtonEvent.button;

            switch (scene)
            {
            case 1:
                handle_gamepad_scene_1(button);
                break;
            case 2:
                handle_gamepad_scene_2(button, gamePaused);
                break;
            case 3:
                handle_gamepad_scene_3(button);
                break;
            case 4:
                handle_gamepad_scene_4(button);
                break;
            case 5:
                handle_gamepad_scene_5(button);
                break;
            case 6:
                handle_gamepad_scene_6(button);
                break;
            case 7:
                handle_gamepad_scene_7(button);
                break;
            case 8:
                handle_gamepad_scene_8(button);
                break;
            case 9:
                handle_gamepad_scene_9(button);
                break;
            case 10:
                handle_gamepad_scene_10(button);
                break;
            case 11:
                handle_gamepad_scene_11(button);
                break;
            case 12:
                handle_gamepad_scene_12(button);
                break;
            case 13:
                handle_gamepad_scene_13(button);
                break;
            case 14:
                handle_gamepad_scene_14(button);
                break;
            case 15:
                handle_gamepad_scene_15(button);
                break;
            case 16:
                handle_gamepad_scene_16(button);
                break;
            case 17:
                handle_gamepad_scene_17(button);
                break;
            case 18:
                handle_gamepad_scene_18(button);
                break;
            case 19:
                handle_gamepad_scene_19(button);
                break;
            case 20:
                handle_gamepad_scene_20(button);
                break;
            case 21:
                handle_gamepad_scene_21(button);
                break;
            case 22:
                handle_gamepad_scene_22(button);
                break;
            case 23:
                handle_gamepad_scene_23(button);
                break;
            case 24:
                handle_gamepad_scene_24(button);
                break;
            case 25:
                handle_gamepad_scene_25(button);
                break;
            case 26:
                handle_gamepad_scene_26(button);
                break;
            case 27:
                handle_gamepad_scene_27(button);
                break;
            case 28:
                handle_gamepad_scene_28(button);
                break;
            case 29:
                handle_gamepad_scene_29(button);
                break;
            case 30:
                handle_gamepad_scene_30(button);
                break;
            case 31:
                handle_gamepad_scene_31(button);
                break;
            case 100:
            case 101:
            case 102:
            case 103:
            case 104:
            case 105:
            case 106:
            case 107:
            case 108:
            case 109:
            case 110:
            case 111:
            case 150:
                handle_gamepad_scene_gameplay(button, gamePaused);
                break;
            default:
                handle_gamepad_scene_gameplay(button, gamePaused);
                break;
            }
        }
        else if (event.type == SDL_CONTROLLERDEVICEADDED)
        {
            handle_controller_added(event);
            break;
        }
        else if (event.type == SDL_CONTROLLERDEVICEREMOVED)
        {
            handle_controller_removed(event);
            break;
        }
        else if (event.type == SDL_TEXTINPUT)
        {
            // Need to use SDL_TEXTINPUT for live interactive type and render at same time
            for (BaseButton *button : allButtons)
            {
                if (button->is_selected())
                {
                    if (InputButton *x = dynamic_cast<InputButton *>(button))
                    {
                        x->set_text(event);
                    }
                }
            }
            break;
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                SCREEN_WIDTH = event.window.data1;
                SCREEN_HEIGHT = event.window.data2;
                SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
                SDL_UpdateWindowSurface(window);
                windowResized = true;
                logger.log_non_critical("window resized");
                break;
            case SDL_WINDOWEVENT_RESTORED:
            case SDL_WINDOWEVENT_MAXIMIZED:
                windowMinimized = false; // start rendering when window restored
                logger.log_non_critical("window maximised");
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                windowMinimized = true; // stop rendering if window minimised
                logger.log_non_critical("window minimised");
                break;
            default:
                break;
            }
        }
    }
}
void update(int &soundVolume, int &musicVolume, int &scene, bool gamePaused)
{
    if (!gamePaused)
    {
        // Adjust SFX and Music volume
        Mix_Volume(-1, soundVolume);  // Adjust SFX volume
        Mix_VolumeMusic(musicVolume); // Adjust Music volume

        switch (scene)
        {
        case 1:
            update_scene_1();
            break;
        case 2:
            update_scene_2();
            break;
        case 3:
            update_scene_3();
            break;
        case 4:
            update_scene_4();
            break;
        case 5:
            update_scene_5();
            break;
        case 6:
            update_scene_6();
            break;
        case 7:
            update_scene_7();
            break;
        case 8:
            update_scene_8();
            break;
        case 9:
            update_scene_9();
            break;
        case 10:
            update_scene_10();
            break;
        case 11:
            update_scene_11();
            break;
        case 12:
            update_scene_12();
            break;
        case 13:
            update_scene_13();
            break;
        case 14:
            update_scene_14();
            break;
        case 15:
            update_scene_15();
            break;
        case 28:
            update_scene_28();
            break;
        case 100:
        case 101:
        case 102:
        case 103:
        case 104:
        case 105:
        case 106:
        case 107:
        case 108:
        case 109:
        case 110:
        case 111:
        case 150:
            update_scene_gameplay();
        default:
            break;
        }
    }
}
void draw(SDL_Renderer *&renderer, int &scene, SDL_Texture *&background1Texture, float fps, bool gamePaused)
{
    if (!gamePaused)
    {
        if (!windowMinimized)
        {
            SDL_SetRenderDrawColor(renderer, 144, 238, 144, 255);
            SDL_RenderClear(renderer);

            if (windowResized)
            {
                windowResized = false;
            }

            SDL_RenderCopy(renderer, background1Texture, nullptr, nullptr); // default background for all game scenes unless overwritten in individual draw()

            // Show fps
            if (displayFPS)
            {
                render_text("FPS: " + std::to_string(static_cast<int>(fps)), (SCREEN_WIDTH * 0.8), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);
            }

            switch (scene)
            {
            case 1:
                draw_scene_1();
                break;
            case 2:
                draw_scene_2();
                break;
            case 3:
                draw_scene_3();
                break;
            case 4:
                draw_scene_4();
                break;
            case 5:
                draw_scene_5();
                break;
            case 6:
                draw_scene_6();
                break;
            case 7:
                draw_scene_7();
                break;
            case 8:
                draw_scene_8();
                break;
            case 9:
                draw_scene_9();
                break;
            case 10:
                draw_scene_10();
                break;
            case 11:
                draw_scene_11();
                break;
            case 12:
                draw_scene_12();
                break;
            case 13:
                draw_scene_13();
                break;
            case 14:
                draw_scene_14();
                break;
            case 15:
                draw_scene_15();
                break;
            case 16:
                draw_scene_16();
                break;
            case 17:
                draw_scene_17();
                break;
            case 18:
                draw_scene_18();
                break;
            case 19:
                draw_scene_19();
                break;
            case 20:
                draw_scene_20();
                break;
            case 21:
                draw_scene_21();
                break;
            case 22:
                draw_scene_22();
                break;
            case 23:
                draw_scene_23();
                break;
            case 24:
                draw_scene_24();
                break;
            case 25:
                draw_scene_25();
                break;
            case 26:
                draw_scene_26();
                break;
            case 27:
                draw_scene_27();
                break;
            case 28:
                draw_scene_28();
                break;
            case 29:
                draw_scene_29();
                break;
            case 30:
                draw_scene_30();
                break;
            case 31:
                draw_scene_31();
                break;
            case 100:
            case 101:
            case 102:
            case 103:
            case 104:
            case 105:
            case 106:
            case 107:
            case 108:
            case 109:
            case 110:
            case 111:
            case 150:
                draw_scene_gameplay();
                break;
            default:
                draw_scene_gameplay();
                break;
            }

            SDL_RenderPresent(renderer);
        }
    }
}
