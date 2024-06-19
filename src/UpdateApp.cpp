/*
    Author: Sumeet Singh
    Dated: 14/02/2024
    Minimum C++ Standard: C++11
    Purpose: Class Definition file
    License: MIT License
*/

#include "../headers/UpdateApp.hpp"

#include <cstdio>  // for curl functions, and fopen_s
#include <cstring> // for curl functions
#include <cstdlib> // For c++, multiplatform code e.g. std::system("pkill") to run system commands e.g terminate app
#ifdef _WIN32
#include <winsock2.h> // For curling on Windows
#include <cstdio>     // for fopen_s
#else
#include <stdio.h> // for fopen
#endif
#include <zip.h>      // for unzipping downloaded application from GitHub/source repo
#include <fstream>    // multiplatform method for for file open read write objects
#include <filesystem> // multiplatform method for creating and deleting directories (folders)

UpdateApp::UpdateApp(std::string currentVersion, std::string urlPath, std::string downloadLink, std::string certPath, std::string dataFileName, std::string executableName, std::string directoryName)
    : currentVersion(currentVersion), urlPath(urlPath), downloadLink(downloadLink), certPath(certPath), dataFileName(dataFileName), executableName(executableName), directoryName(directoryName)
{
#ifdef OS_WINDOWS
    osName = "Windows";
#elif defined(OS_LINUX)
    osName = "Linux";
#elif defined(OS_MACOS)
    osName = "MacOS";
#else
    osName = "Unknown";
#endif

    std::cout << "Success: Constructed a UpdateApp instance" << std::endl;
}

UpdateApp::~UpdateApp(){};

bool UpdateApp::get_current_and_parent_directory()
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path parentPath = currentPath.parent_path();
    currentDirectory = currentPath.string();
    parentDirectory = parentPath.string();
    std::cout << "Current directory path is: " << currentDirectory << std::endl;
    std::cout << "Current Directory Parent path is: " << parentDirectory << std::endl;
    if (!currentDirectory.empty() && !parentDirectory.empty())
    {
        return true;
    }
    return false;
}

size_t UpdateApp::curl_write_callback(void *contents, size_t size, size_t nmemb, std::string *response)
{
    size_t total_size = size * nmemb;
    response->append((char *)contents, total_size);
    return total_size;
}

bool UpdateApp::curl_website_to_find_string()
{
    get_current_and_parent_directory();

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl)
    {
        std::cout << "Success: Curl initialised." << std::endl;
        curl_easy_setopt(curl, CURLOPT_URL, urlPath.c_str());

        /**
         * Leave cert path blank during constructor to not bundle a CA cert in case of expiry
         * You can modify this code to point to your hosts CA store instead, or if it's a trusted hose
         * just ignore SSL verification all together. 
        */
        if (certPath.empty()) {
            // Disable SSL peer verification
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            // Disable SSL host verification
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        }
        else
        {
            curl_easy_setopt(curl, CURLOPT_CAINFO, certPath.c_str());
        }
        

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_callback); // Without this cannot write response to std::string response
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        std::cout << "Status: Now starting to curl: " << urlPath << std::endl;

        // Perform the request
        res = curl_easy_perform(curl);

        if (res == CURLE_OK)
        {
            std::cout << "Curl successfull. Response below" << std::endl;

            // Print the response: std::cout << "Response:\n" << response << std::endl;

            // Extract the version number from the response -
            std::string stringToFind = "Version: ";
            size_t foundStringPosition = response.find(stringToFind);
            std::cout << "now locating string: " << stringToFind << std::endl;

            if (foundStringPosition != std::string::npos)
            {
                foundStringPosition += stringToFind.length(); // Move past the "Version: " string

                // Find the position of the first non-numeric character in the version number
                size_t non_numeric_pos = response.find_first_not_of("0123456789.", foundStringPosition);

                // Keep only the numeric part of the version number
                foundString = response.substr(foundStringPosition, non_numeric_pos - foundStringPosition);

                compare_curl_response_strings(foundString);

                curl_easy_cleanup(curl);
                curl_global_cleanup();
                return true;
            }
            else
            {
                std::cout << "Couldn't find string 'Version: ' in online repo README.md application update stopping." << std::endl;
            }
        }
        else
        {
            std::cout << "Error: curl failed: " << curl_easy_strerror(res) << std::endl;
        }
    }
    else
    {
        std::cout << "Error: Failed to initialize curl." << std::endl;
    }
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return false;
}

void UpdateApp::compare_curl_response_strings(std::string foundString)
{
    // Convert version strings to double
    double currentVersionDouble = stod(currentVersion);
    double foundStringDouble = stod(foundString);

    if (foundStringDouble <= currentVersionDouble)
    {
        std::cout << "Current version: " << currentVersionDouble << " , is already up to date." << std::endl;
        newVersionAvailable = false;
    }
    else
    {
        // 1 - If the application is out of date, prompt to download the latest version
        std::cout << "Current version is: " << currentVersionDouble << ", New version available is: " << foundStringDouble << std::endl;
        newVersionAvailable = true;
    }
}

size_t UpdateApp::download_write_callback(void *contents, size_t size, size_t nmemb, FILE *file)
{
    return fwrite(contents, size, nmemb, file);
}

bool UpdateApp::download_zip(std::string parentDirectory, std::string downloadLink, std::string directoryName)
{
    std::cout << "Attempting to download updates" << std::endl;

    CURL *curl;
    CURLcode res;
    FILE *file;

    // zipFilePath is the name of the zip file curl will download files into.
    // e.g, zipFilePath = c:\users\test\example.zip
    zipFilePath = parentDirectory + directoryName + ".zip";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (!curl)
    {
        std::cout << "Error: Cannot initialize curl." << std::endl;
        return false;
    }

    /**
     * Leave cert path blank during constructor to not bundle a CA cert in case of expiry
     * You can modify this code to point to your hosts CA store instead, or if it's a trusted hose
     * just ignore SSL verification all together.
     */
    if (certPath.empty())
    {
        // Disable SSL peer verification
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        // Disable SSL host verification
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }
    else
    {
        curl_easy_setopt(curl, CURLOPT_CAINFO, certPath.c_str());
    }

    // Set download link
    curl_easy_setopt(curl, CURLOPT_URL, downloadLink.c_str());

    // Open file to save the downloaded data
    file = fopen(zipFilePath.c_str(), "wb");
    if (!file)
    {
        std::cout << "Error: Cannot create file to save downloaded data." << std::endl;
        curl_easy_cleanup(curl);
        return false;
    }

    // Set the file to write to using WriteCallback
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &UpdateApp::download_write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    // Set progress callback
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, &UpdateApp::XferInfoCallback);

    // Follow redirects
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Fail if HTTP response code >= 400
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    // Set user-agent
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3");

    // Set debug verbosity
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    // Perform the request
    res = curl_easy_perform(curl);

    fclose(file); // Close the file after download

    if (res == CURLE_OK)
    {
        std::cout << "Download successful." << std::endl;
        curl_easy_cleanup(curl);
        return true;
    }
    else
    {
        std::cout << "Download failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return false;
    }
}

bool UpdateApp::extract_zip(std::string zipFilePath, std::string parentDirectory)
{
    struct zip *zip_archive;
    struct zip_file *zip_file;
    struct zip_stat zip_stat;
    char buf[100];

    std::cout << "Starting Extract Zip function..." << std::endl;

    // e.x, zipFilePath = "c:\users\test.zip"
    std::filesystem::path parent_directory = std::filesystem::path(parentDirectory);
    std::string newDirectory = std::filesystem::path(zipFilePath).stem().string();
    newDirectory += "-extracted";
    std::filesystem::path newDirectoryPath = parent_directory / newDirectory;
    std::filesystem::create_directory(newDirectoryPath);
    if (!std::filesystem::exists(newDirectoryPath))
    {
        std::cout << "Created directory for extraction: " << newDirectoryPath << std::endl;
    }

    // Open the zip archive
    zip_archive = zip_open(zipFilePath.c_str(), ZIP_RDONLY, nullptr);
    if (zip_archive == nullptr)
    {
        std::cout << "Error opening zip archive." << std::endl;
        return false;
    }
    else
    {
        std::cout << "Zip archive opened successfully." << std::endl;
    }

    // Get the number of entries in the zip archive
    int num_entries = zip_get_num_entries(zip_archive, 0);
    std::cout << "Number of entries in the zip archive: " << num_entries << std::endl;

    // Extract each entry in the zip archive
    for (int i = 0; i < num_entries; i++)
    {
        // Get information about the current entry
        if (zip_stat_index(zip_archive, i, 0, &zip_stat) == 0)
        {
            // Get the name of the entry
            std::string entry_name = zip_get_name(zip_archive, i, 0);

            // Create full output file path
            std::filesystem::path output_file_path = newDirectoryPath / entry_name;

            // Check if the entry is a directory
            bool is_directory = entry_name.back() == '/';

            // If it's a directory, create the directory
            if (is_directory)
            {
                std::filesystem::create_directories(output_file_path);
                std::cout << "Created directory: " << output_file_path.string() << std::endl;
                continue; // Skip further processing for directories
            }

            // If it's a file, open the entry
            zip_file = zip_fopen_index(zip_archive, i, ZIP_FL_UNCHANGED);
            if (zip_file == nullptr)
            {
                std::cout << "Error opening file in zip archive." << std::endl;
                zip_close(zip_archive);
                return false;
            }
            else
            {
                std::cout << "Opened entry " << i << " in the zip archive." << std::endl;
            }

            // Create directories if needed using filesystem
            std::filesystem::create_directories(output_file_path.parent_path());

            // Open the output file
            FILE *output_file;
#ifdef _WIN32
            errno_t err = fopen_s(&output_file, output_file_path.string().c_str(), "wb");
            if (err != 0 || output_file == nullptr)
#else
            output_file = fopen(output_file_path.string().c_str(), "wb");
            if (output_file == nullptr)
#endif
            {
                std::cout << "Error creating output file." << std::endl;
                zip_fclose(zip_file);
                zip_close(zip_archive);
                return false;
            }
            else
            {
                std::cout << "Created output file: " << output_file_path.string() << std::endl;
            }

            // Extract the current entry and write it to the output file
            zip_int64_t n;
            while ((n = zip_fread(zip_file, buf, sizeof(buf))) > 0)
            {
                fwrite(buf, n, 1, output_file);
            }

            // Close the output file and the current entry
            fclose(output_file);
            zip_fclose(zip_file);

            std::cout << "Zip entry extracted successfully." << std::endl;
        }
        else
        {
            std::cout << "Error getting information about zip entry." << std::endl;
            zip_close(zip_archive);
            return false;
        }
    }

    std::cout << "application updates unzipped successfully." << std::endl;

    // Close the zip archive
    zip_close(zip_archive);
    return true;
}

bool UpdateApp::copy_data_from_source_to_destination(std::string currentDirectory, std::string newDirectory, std::string dataFileName)
{
    std::cout << "STARTING - Copying important data from source to destination directory" << std::endl;

    std::filesystem::path dataSourcePath = std::filesystem::path(currentDirectory) / dataFileName;  // e.g, c:\users\test\savedata.txt
    std::filesystem::path dataDestinationPath = std::filesystem::path(newDirectory) / dataFileName; // e.g, c:\users\test-extracted\savedata.txt
    // Check if the source file exists
    if (std::filesystem::exists(dataSourcePath))
    {
        // Copy the file
        std::filesystem::copy_file(dataSourcePath, dataDestinationPath, std::filesystem::copy_options::overwrite_existing);
        std::cout << "File copied successfully." << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Existing save file from non-updated application directory not found." << std::endl;
        return false;
    }
}

bool UpdateApp::exit_application() const
{
    std::cout << "STARTING - Close application" << std::endl;

    try
    {
        if (osName == "Windows")
        {
            std::string windows_terminate_process_command = "taskkill /F /IM main.exe";
            system(windows_terminate_process_command.c_str());
        }
        else
        {
            std::string unix_terminate_process_command = "pkill main";
            system(unix_terminate_process_command.c_str());
        }
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error occurred in exit_application: " << e.what() << std::endl;
        return false;
    }
}

bool UpdateApp::delete_directory(const std::string &currentDirectory)
{
    for (const auto &entry : std::filesystem::recursive_directory_iterator(currentDirectory))
    {
        if (entry.is_regular_file())
        {
            std::filesystem::remove(entry.path());
        }
    }
    try
    {
        std::filesystem::remove_all(currentDirectory);
        std::cout << "Directory deleted: " << currentDirectory << std::endl;
        return true;
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Error deleting directory: " << e.what() << std::endl;
        return false;
    }
}

bool UpdateApp::rename_extracted_folder(std::string newDirectory, std::string currentDirectory)
{
    std::cout << "STARTING - Rename unzipped folder to xxxxx" << std::endl;
    try
    {
        // Check if newDirectory exists
        if (!std::filesystem::exists(newDirectory))
        {
            std::cerr << "Error: New directory does not exist." << std::endl;
            return false;
        }

        // Rename newDirectory to currentDirectory
        std::filesystem::rename(newDirectory, currentDirectory);
        std::cout << "Unzipped folder successfully renamed from 'xxxxx-master' to 'xxxxx'." << std::endl;
        return true;
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Error renaming unzipped folder from 'xxxxx-master' to 'xxxxx': " << e.what() << std::endl;
        return false;
    }
}

bool UpdateApp::application_start(std::string currentDirectory, std::string executableName) const
{
    std::cout << "STARTING - Opening application executable or binary" << std::endl;
    try
    {
        if (osName == "Windows")
        {
            std::string start_command = "start \"\" \"" + currentDirectory + executableName;
            system(start_command.c_str());
        }
        else
        {
            size_t dotPosition = executableName.find_last_of('.');
            std::string binaryName = executableName.substr(0, dotPosition);
            std::string start_command = "chmod +x \"" + currentDirectory + binaryName;
            system(start_command.c_str());
        }
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error occurred in application_start: " << e.what() << std::endl;
        return false;
    }
}

bool UpdateApp::start_update()
{
    startUpdate = true;
    // Perform update steps
    bool downloadSuccess = download_zip(parentDirectory, downloadLink, directoryName);
    bool extractionSuccess = extract_zip(zipFilePath, parentDirectory);
    bool copySuccess = copy_data_from_source_to_destination(currentDirectory, newDirectory, dataFileName);
    bool exitSuccess = exit_application();
    bool deleteSuccess = delete_directory(currentDirectory);
    bool renameSuccess = rename_extracted_folder(newDirectory, currentDirectory);
    bool applicationStartSuccess = application_start(currentDirectory, executableName);

    // Check if all steps were successful
    if (downloadSuccess && extractionSuccess && copySuccess && exitSuccess && deleteSuccess && renameSuccess && applicationStartSuccess)
    {
        applicationUpdated = true; // Update the flag
        startUpdate = false;
        return true;
    }
    else
    {
        applicationUpdated = false; // Update the flag
        return false;
    }
}

int UpdateApp::XferInfoCallback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{

    if (dltotal <= 0)
    {
        std::cout << "Download progress: " << dlnow / (1024 * 1024) << " MB downloaded (Unknown total size)" << std::endl;
    }
    else
    {
        double total = static_cast<double>(dltotal) / (1024 * 1024);
        double downloaded = static_cast<double>(dlnow) / (1024 * 1024);
        std::cout << "Download progress: " << static_cast<long long>(downloaded) << " MB / " << static_cast<long long>(total) << " MB ("
                  << (downloaded / total) * 100.0 << "%/100% complete)" << std::endl;
    }
    return 0;
}
