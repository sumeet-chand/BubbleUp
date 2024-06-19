/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Class Declaration/Definition file combined
    License: MIT License
*/

#pragma once

#if defined(_WIN32)
#define OS_WINDOWS
#elif defined(__linux__)
#define OS_LINUX
#elif defined(__APPLE__)
#define OS_MACOS
#else
#error "Unsupported OS"
#endif

#include <iostream>
#include <string>      // For getline()
#include <curl/curl.h> // for downloading latest application from Github

/**
 * @brief class For updating a software by comparing strings of version numbers from remote sources, and promptig
 * user to accept download which copies save file, overwrites and starts new version
 *
 * Class for using curl to compare a parameter version number e.g. this current apps version
 * with a remote webpage string version: x.x, if versions are different, prompt to download latest
 * version on accept will;
 * * download latest zip,
 * * extract zip,
 * * copy over save file from old old game directory
 * * close app,
 * * delete old folder,
 * * rename new folder to old folder name
 * * then start new game
 *
 * REQUIREMENTS
 * include <curl/curl.h> // for downloading latest application from Github
 * include <zip.h>      // for unzipping downloaded application from GitHub/source repo
 *
 *
 * PARAMETERS
 *
 * currentVersion: pass a string or variable of current game e.g. std::string softwareVersion = "0.1";
 * osName: the platform OS, can be found with MACROS e.g. # ifdef __WIN32 {osName = "Windows"}
 * urlPath: website address of any page which has the words "Version: " in it to scrap the string after e.g; "0.2"
 * downloadLink: Once currentVersion and urlPath returned foundString are compared and user prompts to download
 * new version, downloadLink holds address of path to download .zip file for further function extractions
 * certPath: included within ./keys is a CA cert for convenience however can leave blank to skip SSL verification.
 * dataFileName: Name of the save file of existing game to copy to new folder before deleting old out of date directory
 * executableName: Name of the executable to start after deleting old directory (Note: function will strip .exe for
 * unix like OS's) directoryName: directory name of project
 *
 * _________________________________________________________________________________________________
 *
 * EXAMPLE
 *
 * 1. Create global variable with details
 *
 * UpdateApp updateApp = {softwareVersion, "Windows", "https://github.com/SumeetSinghJi/BubbleUp",
 *                         "https://github.com/SumeetSinghJi/BubbleUp/archive/refs/heads/main.zip",
 *                         "./keys/curl-ca-bundle.crt", "gamesave.txt", "BubbleUp.exe", "BubbleUp"};
 *
 * 2. Draw prompts to update
 *
 * void draw_scene_7()
 * {
 *     // row 1
 *     render_text("CHECK FOR UPDATES", (SCREEN_WIDTH * 0.35), (SCREEN_HEIGHT * 0.1), 0, 0, 0, 255, defaultFont);
 *
 *     render_text("To access online services your game needs to be updated to the latest version.", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.3), 0, 0, 0, 255, defaultFont);
 *     render_text("Checking online to see if new game version is available. Current version is: " + updateApp.currentVersion,(SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.4), 0, 0, 0, 255, defaultFont);
 *
 *     if (updateApp.clickedCheckForUpdates)
 *     {
 *         updateApp.curl_website_to_find_string();
 *         updateApp.clickedCheckForUpdates = false;
 *     }
 *
 *     if (updateApp.newVersionAvailable)
 *     {
 *         render_text("New version is available: " + updateApp.foundString, (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.5), 0, 0, 0, 255, defaultFont);
 *         render_text("Would you like to download?", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.6), 0, 0, 0, 255, defaultFont);
 *
 *     if (!updateApp.startUpdate)
 *     {
 *         scene7updateButton.render_button_rect(renderer);
 *         scene7cancelButton.render_button_rect(renderer);
 *         scene7returnToTitleButton.render_button_rect(renderer);
 *     }
 *     if (updateApp.startUpdate)
 *     {
 *         render_text("UPDATING GAME. PLEASE BE PATIENT. DO NOT CLOSE...", (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.7), 0, 0, 0, 255, defaultFont);
 *     }
 *     if (updateApp.applicationUpdated)
 *     {
 *         softwareVersion = updateApp.newVersionAvailable;
 *         render_text("You have downloaded latest version: " + softwareVersion, (SCREEN_WIDTH * 0.1), (SCREEN_HEIGHT * 0.7), 0, 0, 0, 255, defaultFont);
 *         SDL_Delay(3000);
 *         scene = 8;
 *     }
 *     }
 *     else
 *     {
 *         scene = 8;
 *     }
 * }
 *
 * 3. Create your handles to trigger starting update
 *
 * else if (scene7updateButton.is_clicked(mousePosition))
 * {
 *     std::cout << "You clicked: Update" << std::endl;
 *     updateApp.start_update();
 * }
 *
 */
class UpdateApp
{
private:
public:
    std::string currentVersion{};   /**< The current version of software passed from constructor used to compare with remote version string */
    std::string urlPath{};          /**< url to curl to find version string */
    std::string downloadLink{};     /**< download link of zip file e.g. www.example.com/test.zip */
    std::string certPath{};         /**< CA cert path for CURL, comes with CURL. Leave blank if you want to skip SSL vertification or worried about CA cert expiring */
    std::string dataFileName{};     /**< important file to copy over from old out of date directory to new before old is deleted e.g. savefiles */
    std::string executableName{};   /**< the executable passed from constructor to start the app again */
    std::string directoryName{};    /**< name of softwares folder */
    std::string currentDirectory{}; /**< name of softwares folder as path */
    std::string parentDirectory{};  /**< name of softwares parent folder as path */
    std::string zipFilePath{};      /**< zip file path once downloaded which will be in the existing softwares parent directory */
    std::string newDirectory{};     /**< new directory is the extracted zip file */
    std::string foundString{};      /**< if currentVersion is less then remote string found version set to version number */
    std::string osName{};           /**< host os platform */
    bool clickedCheckForUpdates{};  /**< For your while event loop, one time trigger to updateApp.start_update(); */
    bool newVersionAvailable{};     /**< compare_curl_response_strings() output true comparison result */
    bool startUpdate{};             /**< Trigger for buttons/handles/draws/updates for your app */
    bool applicationUpdated{};      /**< start_update() returns true if updated app */
    double downloadProgress{};      /**< for callback function to write download progress to terminal */

    /**
     * @brief UpdateApp constructor
     *
     * EXAMPLE 
     * 
     * UpdateApp updateApp = {softwareVersion, "Windows", "https://github.com/SumeetSinghJi/BubbleUp",
     *                         "https://github.com/SumeetSinghJi/BubbleUp/archive/refs/heads/main.zip",
     *                         "./keys/curl-ca-bundle.crt", "gamesave.txt", "BubbleUp.exe", "BubbleUp"};
     *
     */
    UpdateApp(std::string currentVersion, std::string urlPath, std::string downloadLink, std::string certPath, std::string dataFileName, std::string executableName, std::string directoryName);

    /**
     * @brief UpdateApp deconstructor
     *
     */
    ~UpdateApp();

    /**
     * @brief Called during starting update function to find environments directories for saving files to
     * @return bool on success that parent and current directories were found
     */
    bool get_current_and_parent_directory();
    /**
     * @brief Without this cannot write response to std::string response
     *
     * Callback function for curl. Without this cannot write response to std::string response
     *
     * @param contents automatically retrieved from calling function within curl function curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_callback);
     * @param size automatically retrieved from calling function within curl function curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_callback);
     * @param nmemb automatically retrieved from calling function within curl function curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_callback);
     * @param response automatically retrieved from calling function within curl function curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_callback);
     *
     * @return reponse of curl to output somewhere e.g. terminal
     */
    static size_t curl_write_callback(void *contents, size_t size, size_t nmemb, std::string *response);
    /**
     * @brief Start Curl to Github to check for updates
     *
     * Start Curl to Github to check for updates
     *
     * @returns true if curl succesfull and populated std::string foundString for compare_curl_response_strings()
     */
    bool curl_website_to_find_string();
    /**
     * @brief Function to compare string responses from curl
     *
     * Function to compare string responses from curl
     *
     * @param foundString passed from curl_website_to_find_string() with string to compare with local software version
     */
    void compare_curl_response_strings(std::string foundString);
    /**
     * @brief Callback function to write the downloaded data to a file
     *
     * Callback function to write the downloaded data to a file
     *
     * @param contents automatically retrieved from curl response callback from function curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &UpdateApp::download_write_callback);
     * @param size automatically retrieved from curl response callback from function curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &UpdateApp::download_write_callback);
     * @param nmemb automatically retrieved from curl response callback from function curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &UpdateApp::download_write_callback);
     * @param file automatically retrieved from curl response callback from function curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &UpdateApp::download_write_callback);
     *
     * @return the response from curl which in this case is the zip file contents downloaded to the parent directory
     */
    static size_t download_write_callback(void *contents, size_t size, size_t nmemb, FILE *file);
    /**
     * @brief Callback function to display progress
     *
     * Callback function to display progress for download_zip()
     *
     * @param clientp automatically retrived from progress callback from function curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, &UpdateApp::XferInfoCallback);
     * @param dltotal automatically retrived from progress callback from function curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, &UpdateApp::XferInfoCallback);
     * @param dlnow automatically retrived from progress callback from function curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, &UpdateApp::XferInfoCallback);
     * @param ultotal automatically retrived from progress callback from function curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, &UpdateApp::XferInfoCallback);
     * @param ulnow automatically retrived from progress callback from function curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, &UpdateApp::XferInfoCallback);
     *
     * @return the response as an int from curl in this case to show the download progress of the remote zip file
     */
    static int XferInfoCallback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
    /**
     * @brief curl downloadLink. In parentDirectory download directoryName.zip (return: zipFilePath)
     *
     * curl downloadLink. In parentDirectory download directoryName.zip (return: zipFilePath)
     *
     * @param parentDirectory directory to place zip file
     * @param downloadLink download link of zip e.g. www.example.com/test.zip
     * @param directoryName directory name of zip file
     *
     * @return true if zip file downloaded to directory
     */
    bool download_zip(std::string parentDirectory, std::string downloadLink, std::string directoryName);
    /**
     * @brief Extract zipFilePath, return newDirectory = parentDirectory +"-extracted"
     *
     * Extract zipFilePath, return newDirectory = parentDirectory +"-extracted"
     *
     * @param zipFilePath file path of zip file
     * @param parentDirectory zip files parent directory
     *
     * @return true if succesfully extracted zip file contents
     */
    bool extract_zip(std::string zipFilePath, std::string parentDirectory);
    /**
     * @brief copys data from source to destination
     *
     * copys data file e.g. save file from source to destination
     *
     * @param currentDirectory current directory of outdated software
     * @param newDirectory new directory of updated software
     * @param dataFileName file to transfer from old to new directory
     *
     * @return true if file copy successfull
     */
    bool copy_data_from_source_to_destination(std::string currentDirectory, std::string newDirectory, std::string dataFileName);
    /**
     * @brief Close existing executable
     *
     * Close existing executable
     *
     * @return true if stopped running and quit the out of date open software
     */
    bool exit_application() const;
    /**
     * @brief Function to delete the contents of a directory recursively
     *
     * Function to delete the contents of a directory recursively
     *
     * @param currentDirectory the out of date software directory to delete as newDirectory is up to date
     *
     * @return true if succssfully deleted old directory
     */
    bool delete_directory(const std::string &currentDirectory);
    /**
     * @brief Rename unzipped new updated application folder "xxxxx-master" to "xxxxx"
     *
     * Rename unzipped new updated application folder "xxxxx-master" to "xxxxx"
     *
     * @param newDirectory name of new downloaded unzipped up to date software directory
     * @param currentDirectory old directory name to use to rename newDirectory
     *
     * @return true if sucesfully named extracted up to date new software directory to same name as old directory
     */
    bool rename_extracted_folder(std::string newDirectory, std::string currentDirectory);
    /**
     * @brief Open new application executable or binary to complete update application step
     *
     * Open new application executable or binary to complete update application step
     *
     * @param currentDirectory the new directory has been renamed to old directory
     * @param executableName the new software executable to run
     *
     * @return true if successfully started the new up to date software
     */
    bool application_start(std::string currentDirectory, std::string executableName) const;
    /**
     * @brief Function to start all updates
     *
     * Function to start all updates
     *
     * @return true if all downloading, update, unzipping, copying save over, quitting open app, deleting old directory and starting new app is succesfull
     */
    bool start_update();
};
