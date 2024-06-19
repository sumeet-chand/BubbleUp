/*
    Author: Sumeet Singh
    Dated: 28/02/2024
    Minimum C++ Standard: C++11
    Purpose: Class Definition file
    License: MIT License
*/

#include "../headers/EntityManager.hpp"

EntityManager::EntityManager()
{
    std::cout << "Constructed: EntityManager" << std::endl;
}

EntityManager::~EntityManager()
{
    std::cout << "Destroyed: EntityManager" << std::endl;
}

void EntityManager::create_player_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT, int playerCount)
{
    if (playerCount >= 5) {
        playerCount = 4; // limit to max 4 players if function overloaded with playerCount greater then 5 players
    }
    for (int i{}; i < playerCount; ++i)
    {
        /*
            For every existing player entity, playerNumber will increment and that's used to name new players
            and for loading new textures.
            e.g. player1 = green, player2 = red etc.,
        */
        int playerID = 1;
        for (Entity *e : entities)
        {
            if (dynamic_cast<Player *>(e) != nullptr)
            {
                playerID++;
            }
        }

        std::string name = "player";
        name = name + std::to_string(playerID);
        std::string textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0000.png";
        int x = static_cast<int>(SCREEN_WIDTH * 0.1);
        int y = static_cast<int>(SCREEN_HEIGHT * 0.1);
        int width = (SCREEN_WIDTH * 0.05);
        int height = (SCREEN_HEIGHT * 0.05);
        int health = 3;
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/bump 7 - Pixabay.wav";
        std::vector<std::string> defaultTextures{};
        if (playerID == 1)
        {
            std::vector<std::string> defaultTextures = {
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0000.png",
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0001.png",
            };
        }
        else if (playerID == 2)
        {
            std::vector<std::string> defaultTextures = {
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0002.png",
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0003.png",
            };
        }
        else if (playerID == 3)
        {
            std::vector<std::string> defaultTextures = {
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0004.png",
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0005.png",
            };
        }
        else if (playerID == 4)
        {
            std::vector<std::string> defaultTextures = {
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0006.png",
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0007.png",
            };
        }
        Player *player = new Player(playerID, name, x, y, width, height, health, collisionSoundString, defaultTextures);
        player->set_renderer(renderer);
        player->set_sound();
        entities.push_back(player);
    }
    int totalPlayers{};
    for (Entity *e : entities)
    {
        if (dynamic_cast<Player *>(e) != nullptr)
        {
            totalPlayers++;
        }
    }
    std::cout << "Total players are: " << totalPlayers << std::endl;
}
void EntityManager::create_bot_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT, int botCount)
{
    if (botCount >= 5) {
        botCount = 4; // limit to max 4 players if function overloaded with playerCount greater then 5 players
    }
    for (int i{}; i < botCount; ++i)
    {
        /*
            For every existing player entity, playerNumber will increment and that's used to name new players
            and for loading new textures.
            e.g. player1 = green, player2 = red etc.,
        */
        int playerID = 1;
        for (Entity *e : entities)
        {
            if (dynamic_cast<Player *>(e) != nullptr)
            {
                playerID++;
            }

            if (dynamic_cast<Bot *>(e) != nullptr)
            {
                playerID++;
            }
        }

        std::string name = "bot";
        name = name + std::to_string(playerID);
        std::string textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0000.png";
        int x = static_cast<int>(SCREEN_WIDTH * 0.1);
        int y = static_cast<int>(SCREEN_HEIGHT * 0.1);
        int width = (SCREEN_WIDTH * 0.05);
        int height = (SCREEN_HEIGHT * 0.05);
        int health = 3;
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/bump 7 - Pixabay.wav";
        std::vector<std::string> defaultTextures{};
        if (playerID == 1)
        {
            std::vector<std::string> defaultTextures = {
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0000.png",
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0001.png",
            };
        }
        else if (playerID == 2)
        {
            std::vector<std::string> defaultTextures = {
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0002.png",
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0003.png",
            };
        }
        else if (playerID == 3)
        {
            std::vector<std::string> defaultTextures = {
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0004.png",
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0005.png",
            };
        }
        else if (playerID == 4)
        {
            std::vector<std::string> defaultTextures = {
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0006.png",
                "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0007.png",
            };
        }
        Bot *bot = new Bot(playerID, name, x, y, width, height, health, collisionSoundString, defaultTextures);
        bot->set_renderer(renderer);
        bot->set_sound();
        entities.push_back(bot);
    }
    int totalPlayers{};
    int totalBots{};
    for (Entity *e : entities)
    {
        if (dynamic_cast<Player *>(e) != nullptr)
        {
            totalPlayers++;
        }

        if (dynamic_cast<Bot *>(e) != nullptr)
        {
            totalBots++;
        }
    }
    std::cout << "Total players: " << totalPlayers << "Total bots: " << totalBots<< std::endl;
}

void EntityManager::create_item_heart_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    std::string name = "Heart";
    std::string textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0044.png";
    int x = static_cast<int>(SCREEN_WIDTH * 0.1);
    int y = static_cast<int>(SCREEN_HEIGHT * 0.1);
    int width = (SCREEN_WIDTH * 0.05);
    int height = (SCREEN_HEIGHT * 0.05);
    int health = 3;
    std::string collisionSoundString = "assets/sounds/sound-effects/wavs/Level Up  2 UNIVERSFIELD.wav";
    std::vector<std::string> defaultTextures = {
        "assets/graphics/kenney_pixel-platformer/Tiles/tile_0044.png",
    };

    Heart *item = new Heart(name, x, y, width, height, health, collisionSoundString, defaultTextures);
    item->set_renderer(renderer);
    item->set_sound();
    entities.push_back(item);
}
void EntityManager::create_random_item_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    // Creation logic for item entities
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 5);
    int random = dist(gen);

    std::string name;
    std::string textureFilePath;
    int x = static_cast<int>(SCREEN_WIDTH * 0.1);
    int y = static_cast<int>(SCREEN_HEIGHT * 0.1);
    int width = (SCREEN_WIDTH * 0.05);
    int height = (SCREEN_HEIGHT * 0.05);
    int health = 999;
    if (random == 0)
    {
        name = "Heart";
        textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/tile_0044.png";
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/Level Up  2 UNIVERSFIELD.wav";
        std::vector<std::string> heartsDefaultTextures = {
            "assets/graphics/kenney_pixel-platformer/Tiles/tile_0044.png",
        };
        Heart *item = new Heart(name, x, y, width, height, health, collisionSoundString, heartsDefaultTextures);
        item->set_renderer(renderer);
        item->set_sound();
        entities.push_back(item);
    }
    else if (random == 1)
    {
        name = "Boots";
        textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/tile_0068.png";
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/clothes drop 2 - Pixabay.wav";
        std::vector<std::string> bootsDefaultTextures = {
            "assets/graphics/kenney_pixel-platformer/Tiles/tile_0068.png",
        };
        Boots *item = new Boots(name, x, y, width, height, health, collisionSoundString, bootsDefaultTextures);
        item->set_renderer(renderer);
        item->set_sound();
        entities.push_back(item);
    }
    else if (random == 2)
    {
        name = "Gem";
        textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/tile_0067.png";
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/Money Pickup 2 - Pixabay.wav";
        std::vector<std::string> gemDefaultTextures = {
            "assets/graphics/kenney_pixel-platformer/Tiles/tile_0067.png",
        };
        Gem *item = new Gem(name, x, y, width, height, health, collisionSoundString, gemDefaultTextures);
        item->set_renderer(renderer);
        item->set_sound();
        entities.push_back(item);
    }
    else if (random == 3)
    {
        name = "Ammo";
        textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/tile_0026.png";
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/Health Pickup - Pixabay.wav";
        std::vector<std::string> ammoDefaultTextures = {
            "assets/graphics/kenney_pixel-platformer/Tiles/tile_0026.png",
        };
        Ammo *item = new Ammo(name, x, y, width, height, health, collisionSoundString, ammoDefaultTextures);
        item->set_renderer(renderer);
        item->set_sound();
        entities.push_back(item);
    }
    else
    {
        name = "Key";
        textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/tile_0027.png";
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/Lock the door - Pixabay.wav";
        std::vector<std::string> keyDefaultTextures = {
            "assets/graphics/kenney_pixel-platformer/Tiles/tile_0027.png",
        };
        Key *item = new Key(name, x, y, width, height, health, collisionSoundString, keyDefaultTextures);
        item->set_renderer(renderer);
        item->set_sound();
        entities.push_back(item);
    }
}
void EntityManager::create_random_enemy_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    // Creation logic for enemy entities
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);
    int random = dist(gen);

    std::string name;
    std::string textureFilePath;
    int x = static_cast<int>(SCREEN_WIDTH * 0.1);
    int y = static_cast<int>(SCREEN_HEIGHT * 0.1);
    int width = (SCREEN_WIDTH * 0.1);
    int height = (SCREEN_HEIGHT * 0.1);
    int health = 3;
    if (random == 0)
    {
        name = "Bomb";
        textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0008.png";
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/Medium Explosion - Pixabay.wav";
        std::vector<std::string> bombDefaultTextures = {
            "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0008.png",
        };
        Bomb *enemy = new Bomb(name, x, y, width, height, health, collisionSoundString, bombDefaultTextures);
        enemy->set_renderer(renderer);
        enemy->set_sound();
        entities.push_back(enemy);
    }
    else
    {
        name = "Robot";
        textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0021.png";
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/Single bark of a dog - Pixabay.wav";
        std::vector<std::string> robotDefaultTextures = {
            "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0021.png",
            "assets/graphics/kenney_pixel-platformer/Tiles/Characters/tile_0022.png",
        };
        Robot *enemy = new Robot(name, x, y, width, height, health, collisionSoundString, robotDefaultTextures);
        enemy->set_renderer(renderer);
        enemy->set_sound();
        entities.push_back(enemy);
    }
}
void EntityManager::create_random_obstacle_entity(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    // Creation logic for obstacle entities
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 3);
    int random = dist(gen);

    std::string name;
    std::string textureFilePath;
    int x = static_cast<int>(SCREEN_WIDTH * 0.1);
    int y = static_cast<int>(SCREEN_HEIGHT * 0.1);
    int width = static_cast<int>(SCREEN_WIDTH * (rand() % 5 + 1) / 10);
    int height = static_cast<int>(SCREEN_HEIGHT * (rand() % 5 + 1) / 10);
    int health = 999;
    if (random == 0)
    {
        name = "Mountain";
        textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/tile_0023.png";
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/bump 7 - Pixabay.wav";
        std::vector<std::string> mountainDefaultTextures = {
            "assets/graphics/kenney_pixel-platformer/Tiles/tile_0023.png",
        };
        Mountain *obstacle = new Mountain(name, x, y, width, height, health, collisionSoundString, mountainDefaultTextures);
        obstacle->set_renderer(renderer);
        obstacle->set_sound();
        entities.push_back(obstacle);
    }
    else if (random == 1)
    {
        name = "Tree";
        textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/tile_0126.png";
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/bump 7 - Pixabay.wav";
        std::vector<std::string> treeDefaultTextures = {
            "assets/graphics/kenney_pixel-platformer/Tiles/tile_0126.png",
        };
        Tree *obstacle = new Tree(name, x, y, width, height, health, collisionSoundString, treeDefaultTextures);
        obstacle->set_renderer(renderer);
        obstacle->set_sound();
        entities.push_back(obstacle);
    }
    else
    {
        name = "River";
        textureFilePath = "assets/graphics/kenney_pixel-platformer/Tiles/tile_0054.png";
        std::string collisionSoundString = "assets/sounds/sound-effects/wavs/Water splash - Pixabay.wav";
        std::vector<std::string> riverDefaultTextures = {
            "assets/graphics/kenney_pixel-platformer/Tiles/tile_0054.png",
        };
        River *obstacle = new River(name, x, y, width, height, health, collisionSoundString, riverDefaultTextures);
        obstacle->set_renderer(renderer);
        obstacle->set_sound();
        entities.push_back(obstacle);
    }
}
void EntityManager::random_procedural_generation(SDL_Renderer *renderer, std::vector<Entity *> &entities, int SCREEN_WIDTH, int SCREEN_HEIGHT, int itemsCount, int enemiesCount, int obstaclesCount)
{
    // Clear existing entities vector for setting up new scene
    for (size_t i = 0; i < entities.size(); i++)
    {
        if (dynamic_cast<Player *>(entities[i]) == nullptr) // look for anything NOT a player
        {
            delete entities[i];    // Deleting entities that are not the player
            entities[i] = nullptr; // Optional: set the pointer to nullptr after deletion
        }
    }
    // Remove null pointers from the vector
    entities.erase(std::remove(entities.begin(), entities.end(), nullptr), entities.end());

    // initialise_static_entities(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT);

    // After calling this function
    std::cout << "START: total entities before procedural generation: " << entities.size() << std::endl;

    // Limit counts to 100 for each type of entity
    if (itemsCount > 100)
    {
        itemsCount = 100;
    }
    if (enemiesCount > 100)
    {
        enemiesCount = 100;
    }
    if (obstaclesCount > 100)
    {
        obstaclesCount = 100;
    }

    if (itemsCount > 0)
    {
        int randomItems = rand() % itemsCount;
        for (int i = 0; i < randomItems; i++)
        {
            create_random_item_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    }

    if (enemiesCount > 0)
    {
        int randomEnemies = rand() % enemiesCount;
        for (int i = 0; i < randomEnemies; i++)
        {
            create_random_enemy_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    }

    if (obstaclesCount > 0)
    {
        int randomObstacles = rand() % obstaclesCount;
        for (int i = 0; i < randomObstacles; i++)
        {
            create_random_obstacle_entity(renderer, entities, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    }

    for (Entity *e : entities)
    {
        e->preload_textures();
    }

    std::cout << "END: total entities after procedural generation: " << entities.size() << std::endl;
}
