/*
    Author: Sumeet Singh
    Dated: 29/04/2024
    Minimum C++ Standard: C++17
    Purpose: Class declarations file
    License: MIT License


    _________________________________________________________________________________________________

                                BubbleUp LEVEL EDITOR CLASS DECLARATIONS
    _________________________________________________________________________________________________


    DESCRIPTION

    for creating custom game map files (.wad) for the BubbleUp game engine.
    Includes EntityManager.hpp for placing entities to a map scene to export to a .wad file format
    on game engine game startup, game will read the ./assets/xxx.wad files to load custom game map 
    scenes.


    EXAMPLE

    1. 



*/

#pragma once

#include <iostream>
#include <string>

/**
 * @brief save custom map
*/
void save_map();
/**
 * @brief add custom map
 * 
 * @param fileName The name of the map file
*/
void import_map(const std::string fileName);
/**
 * @brief get all map filenames in list
 * 
 * @param directoryPath The directory of files
*/
void get_map(const std::string &directoryPath);
/**
 * @brief load map file
 * 
 * @param fileName The name of the map file
*/
void load_map(const std::string &fileName);
/**
 * @brief create custom map
 * 
 * @param fileName The name of the map file
*/
void new_map(const std::string &fileName, const std::string &mapSize);
/**
 * @brief delete map
 * 
 * @param fileName The name of the map file
*/
void delete_map(const std::string &fileName);

/**
 * @brief add custom entity
 * 
 * @param fileName The name of the entity file
*/
void import_entities(const std::string fileName);
/**
 * @brief get all entity filenames in list
 * 
 * @param directoryPath The directory of files
*/
void get_entities(const std::string directoryPath);
/**
 * @brief load entity file
 * 
 * @param fileName The name of the map file
*/
void load_entity(const std::string &fileName);
/**
 * @brief create custom entity
 * 
 * @param fileName The name of the entity file
*/
void create_entities();
/**
 * @brief delete entity
 * 
 * @param fileName The name of the entity file
*/
void delete_entities(const std::string fileName);

/**
 * @brief add custom sounds
 * 
 * @param fileName The name of the sound file
*/
void import_sounds(const std::string fileName);
/**
 * @brief get all sounds filenames in list
 * 
 * @param directoryPath The directory of files
*/
void get_sounds(const std::string directoryPath);
/**
 * @brief play sound
 * 
 * @param fileName The name of the sound file
*/
void play_sound(const std::string fileName);
/**
 * @brief delete sounds
 * 
 * @param fileName The name of the sound file
*/
void delete_sounds(const std::string fileName);

/**
 * @brief add custom music
 * 
 * @param fileName The name of the music file
*/
void import_music(const std::string fileName);
/**
 * @brief get all music filenames in list
 * 
 * @param directoryPath The directory of files
*/
void get_music(const std::string directoryPath);
/**
 * @brief play music
 * 
 * @param fileName The name of the music file
*/
void play_music(const std::string fileName);
/**
 * @brief delete music
 * 
 * @param fileName The name of the music file
*/
void delete_music(const std::string fileName);

/**
 * @brief add custom texture
 * 
 * @param fileName The name of the image file
*/
void import_textures(const std::string fileName);
/**
 * @brief get all textures filenames in list
 * 
 * @param directoryPath The directory of files
*/
void get_textures(const std::string directoryPath);
/**
 * @brief display a texture thumbnail
 * 
 * @param fileName The name of the image file
*/
void display_texture(const std::string fileName);
/**
 * @brief delete textures
 * 
 * @param fileName The name of the image file
*/
void delete_textures(const std::string fileName);

/**
 * @brief create a point in rect reached trigger
 * 
 * You can combine this with other entities such as NPC's or journal objects to create 
 * custom quests, jobs, stories, scripts
 * 
 * Example if point in rect is equal to player subclass type, and x other entity type
 * then you reached the end of cave and won game
*/
void create_point_in_rect_trigger();

/**
 * @brief Draw the software GUI interface
 * 
 * Canvas for adding SDL buttons and fields and text to create the GUI for the software
 * 
*/
void draw_software_GUI();