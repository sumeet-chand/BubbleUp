/*
    Author: Sumeet Singh
    Dated: 29/04/2024
    Minimum C++ Standard: C++17
    Purpose: Class definitions file
    License: MIT License
*/

#include <fstream>
#include <filesystem>
#include "../headers/EntityManager.hpp"      // Classes for creating entities
#include "../headers/buttons/BaseButton.hpp" // Classes for creating and drawing GUI elements

// Modify Maps
void save_map() {
    // render popup to add map name
}
void import_map(const std::string fileName)
{
}
void get_map(const std::string &directoryPath)
{
}
void load_map(const std::string &fileName)
{
}
void new_map(const std::string &fileName, const std::string &mapSize)
{
    std::string fileNameString = fileName + ".wad";
    std::ofstream file(fileNameString);
    if (!file.is_open())
    {
        std::cerr << "Error: Failed to save map .wad file" << std::endl;
    }

    file << "map_name=" << fileName << std::endl;
    file << "map_size=" << mapSize << std::endl;

    file.close();

    if (std::filesystem::exists(fileNameString))
    {
        std::cout << "Success: Saved new map file: " << fileNameString << std::endl;
    }
    else
    {
        std::cerr << "Error: Failed to save map .wad file" << std::endl;
    }
}
void delete_map(const std::string &fileName)
{
    if (std::remove(fileName.c_str()) != 0)
    {
        std::cerr << "Error: deleting file: " << fileName << std::endl;
    }
    else
    {
        std::cout << "Success: deleted file: " << fileName << std::endl;
    }
}

// Modify Entities
void import_entities(const std::string &fileName)
{
}
void get_entities(const std::string directoryPath)
{
}
void load_entity(const std::string fileName)
{
}
void create_entities()
{
}
void delete_entities(const std::string fileName)
{
}

// Modify Sounds
void import_sounds(const std::string fileName)
{
}
void get_sounds(const std::string directoryPath)
{
}
void play_sound(const std::string fileName)
{
}
void delete_sounds(const std::string fileName)
{
}

// Modify Music
void import_music(const std::string fileName)
{
}
void get_music(const std::string directoryPath)
{
}
void play_music(const std::string fileName)
{
}
void delete_music(const std::string fileName)
{
}

// Modify Textures
void import_textures(const std::string fileName)
{
}
void get_textures(const std::string directoryPath)
{
}
void display_textures(const std::string &fileName)
{
}
void delete_textures(const std::string fileName)
{
}

// Modify Triggers
void create_point_in_rect_trigger() {
    // choose entity A e.g. if (e, dynamic_cast<Player> e)
    // choose entity B e.g. if (e->get_name() == "cave door")
    // choose response e.g. scene = 47; // you left the cave
}

void draw_software_GUI()
{
    std::string fileName = "SumeetsCustomMap";
    std::string mapSize = "1024x768";
}