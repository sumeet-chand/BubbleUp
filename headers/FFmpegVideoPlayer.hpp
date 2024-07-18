/*
    Author: Sumeet Singh
    Dated: 18/04/2024
    Minimum C++ Standard: C++17
    Purpose: Class Declaration file
    License: MIT License
*/

#pragma once

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/channel_layout.h>
}

/**
 * @brief Declaration file for using FFmpeg in your SDL program to play a video from any format.
 * 
 * 
 * ******************************************************************************************************************************
 * 
 * COMPLETE GUIDE HERE: https://stackoverflow.com/questions/77742801/how-do-i-include-ffmpeg-for-development-in-a-windows-program
 * 
 * ******************************************************************************************************************************
 *
 * Declarations/Definitions ./headers/FFmpegVideoPlayer.hpp
 *
 *
 * REQUIREMENTS
 *
 * FFMPEG is the largest open source multimedia framework for video playback and codec methods.
 * FFMPEG requires building if you require include, libs and .dll's to utilise in a C/C++ program.
 *
 * Currently this code is requiring manual user intervention to split audio track from video using any tool
 * e.g. a free online converter: https://biteable.com/tools/extract-audio-from-video/
 * then add it in the constructor to play during the video. Ideally it should be read from audio channel.
 *
 * To test
 *
 * Step 1. Download this video - https://archive.org/download/NyanCatoriginal_201509
 * the download link is here: https://archive.org/download/NyanCatoriginal_201509/Nyan%20Cat%20%5Boriginal%5D.mp4
 * Step 2. Use an image splitter free program to split the audio and video e.g. I used this website
 * https://restream.io/tools/audio-extractor
 * to upload the video "Nyan cat [original]" and clicked split audio - then downloaded the audio file.
 * Step 3. Name the video file "nyan_cat_video.mp4" and the audio file "nyan_cat_audio.mp3
 * Step 4. Initialise SDL in your program
 * Step 5. Build FFMPEG following steps below
 * linked here: https://stackoverflow.com/questions/77742801/how-do-i-include-ffmpeg-for-development-in-a-windows-program/
 *
 *_______________________________________________________
 *
 * WINDOWS - you can build with MSYS2 and running below commands in Mingw-64 shell
 * mkdir -p C:/ffmpeg
 * cd c:\ffmpeg
 * git clone https://git.ffmpeg.org/ffmpeg.git .
 * ./configure --prefix=C:/ffmpeg --enable-shared --enable-gpl --disable-programs
 * make -j$(nproc)
 * make install
 *
 * Copy lib and include files to your c++ compilers locations
 * Remove-Item -Recurse C:/ffmpeg/lib/pkgconfig -Force
 * Copy-Item -Path C:/ffmpeg/bin/* -Destination "D:/a/_temp/msys64/mingw64/bin" -Recurse -Force
 * Copy-Item -Path C:/ffmpeg/include/* -Destination "D:/a/_temp/msys64/mingw64/include" -Recurse -Force
 * Copy-Item -Path C:/ffmpeg/lib/* -Destination "D:/a/_temp/msys64/mingw64/lib" -Recurse -Force
 *
 * Copy the dll's to your projects directory next to your main.cpp for example
 * Copy-Item -Path D:/a/_temp/msys64/mingw64/bin/avcodec-61.dll ${{ github.workspace }}/ -Force
 * Copy-Item -Path D:/a/_temp/msys64/mingw64/bin/avformat-61.dll ${{ github.workspace }}/ -Force
 * Copy-Item -Path D:/a/_temp/msys64/mingw64/bin/avutil-59.dll ${{ github.workspace }}/ -Force
 * Copy-Item -Path D:/a/_temp/msys64/mingw64/bin/swresample-5.dll ${{ github.workspace }}/ -Force
 *
 * Link to your main program (i included all sdl libs for ease of use)
 * -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
 * -lavformat -lavcodec -lavutil -lswscale -lavfilter -mwindows
 *_______________________________________________________
 *
 * MACOS - no need to build, brew has it already run in CLI: brew install ffmpeg
 *  No DLL required
 *  Link to your main program (i included all sdl libs for ease of use)
 *      -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lavformat -lavcodec -lavutil -lswscale
 *
 * _______________________________________________________
 *
 * LINUX - run below code
 * git clone https://git.ffmpeg.org/ffmpeg.git .
 * ./configure --prefix=${HOME}/ffmpeg/install  --enable-shared --enable-gpl --disable-programs
 * make -j$(nproc)
 * sudo make install
 *
 * Then copy the ffmpeg include and lib files into your usr lib and include
 * sudo cp -rf ${HOME}/ffmpeg/install/include/* /usr/include
 * sudo cp -rf ${HOME}/ffmpeg/install/lib/* /usr/lib
 *
 * and copy the DLL's from the /usr/lib folder do your projects directory so these sit next to your main.cpp for example
 *      Requires DLL's below
 *      libavutil.so.59.21.100
 *      libswscale.so.8
 *      libavformat.so.61.3.104
 *      libavcodec.so.61.6.100
 *      libswresample.so.5.2.100
 *
 *       link the following
 *      "-lavformat",
 *      "-lavcodec",
 *      "-lavutil",
 *      "-lswscale",
 *      "-lswresample",
 *
 *_______________________________________________________
 *
 *  EXAMPLE
 *
 *  Step 6. Include this class in desired program
 *  include <FFmpegVideoPlayer.hpp>
 *
 *  Step 7. You will need SDL so that you can pass a window/renderer. If you don't know how to use SDL
 *  I suggest you first learn from YouTube + ChatGPT. That's how I learnt.
 *  Then in your code enter the below
 *
 *  FFmpegVideoPlayer videoPlayer("nyan_cat_video.mp4", "nyan_cat_audio.mp4", window, renderer);
 *
 *  Step 8. Play the video. It will block the stack until it ends like any standard function.
 *  So within your main loop you can call it like this
 *
 *  int main() {
 *    std::cout << "Meow!" << std::endl;
 *
 *    sdl_start();
 *
 *    // Play Intro video for game/movie etc.
 *    FFmpegVideoPlayer videoPlayer("nyan_cat_video.mp4", "nyan_cat_audio.mp4", window, renderer);
 *    videoPlayer.playVideo();
 *
 *    // Then start the rest of the program
 *    sdl_run();
 *    sdl_exit();
 *
 *    return 0;
 *  }
 * 
 * Step 9. Ensure that your list of files looks like the below. Note I included the DLL's for both Linux and Windows. If your just building on
 * windows then only copy those dll's over. The reason I have both is to make the software multiplatform (portable)
 * avcodec-61.dll
 * avformat-61.dll
 * avutil-59.dll
 * FFmpegPlayer.h
 * libavcodec.so
 * libavformat.so
 * libavutil.so
 * libcurl-4.dll
 * libswresample.so
 * libswscale.so
 * main.cpp
 * nyan_cat_audio.mp3
 * nyan_cat_video.mp4
 * SDL2.dll
 * SDL2_image.dll
 * SDL2_mixer.dll
 * SDL2_TTF.dll
 * swresample-5.dll
 *
 * Step 10. Build by running the below in the command line: 
 * PS C:\Users\Sumeet\Documents\nyancat> g++ main.cpp -o main -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lavcodec -lavformat -lavutil -lswscale -lswresample
 * PS C:\Users\Sumeet\Documents\nyancat> ./main.exe
 * Meow!
 * Success: initialised: SDL2
 * Success: initialised: SDL2 window
 * Success: initialised: SDL2 renderer
 * Found Video Stream: Index 0
 * Found Audio Stream: Index 1
 * PS C:\Users\Sumeet\Documents\nyancat>
 *
 * Step 11. Done. Be proud of yourself Warrior!
 * 
 */
class FFmpegVideoPlayer
{
private:
    const char *videoFile{};         /**< the video filepath to play */
    const char *musicFile{};         /**< the audio filepath to play, split from video, currently this code is not working to isolate audio stream requires manual splitting */
    SDL_Window *window{};            /**< the SDL Window to play the video on passed as a reference in an existing SDL app */
    SDL_Renderer *renderer{};        /**< the SDL renderer to play the video on passed as a reference in an existing SDL app */
    AVFormatContext *formatCtx{};    /**< the video file */
    int videoStreamIndex{};          /**< the found and split video stream */
    int audioStreamIndex{};          /**< the found and split audio stream */
    const AVCodec *videoCodec{};     /**< the found video codec */
    const AVCodec *audioCodec{};     /**< the found audio codec */
    AVCodecContext *videoCodecCtx{}; /**< the found video codec */
    AVCodecContext *audioCodecCtx{}; /**< the found audio codec */
    Mix_Music *music{};              /**< the SDL mixer to play the audio on passed as a reference in an existing SDL app */

public:
    /**
     * @brief default FFmpegVideoPlayer constructor
     */
    FFmpegVideoPlayer(const char *videoFile, const char *musicFile, SDL_Window *window, SDL_Renderer *renderer)
        : videoFile(videoFile), musicFile(musicFile), window(window), renderer(renderer), formatCtx(nullptr),
          videoStreamIndex(-1), audioStreamIndex(-1), videoCodec(nullptr), audioCodec(nullptr),
          videoCodecCtx(nullptr), audioCodecCtx(nullptr), music(nullptr)
    {
        avformat_network_init();

        // Open the input file
        if (avformat_open_input(&formatCtx, videoFile, nullptr, nullptr) < 0)
        {
            char errbuf[AV_ERROR_MAX_STRING_SIZE];
            av_strerror(errno, errbuf, AV_ERROR_MAX_STRING_SIZE);
            std::cerr << "Error: Could not open Video file: " << videoFile << " - " << errbuf << std::endl;
            return;
        }

        // // Debug: Printing stream information for debugging
        // std::cout << "Debug: Printing stream information for debugging:" << std::endl;
        // av_dump_format(formatCtx, 0, videoFile, 0);

        // Find the stream information
        if (avformat_find_stream_info(formatCtx, nullptr) < 0)
        {
            char errbuf[AV_ERROR_MAX_STRING_SIZE];
            av_strerror(errno, errbuf, AV_ERROR_MAX_STRING_SIZE);
            std::cerr << "Error: Could not find stream information: " << errbuf << std::endl;
            avformat_close_input(&formatCtx); // Close input on failure
            return;
        }

        // Find the first video stream and audio stream
        for (unsigned int i = 0; i < formatCtx->nb_streams; i++)
        {
            if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && videoStreamIndex < 0)
            {
                videoStreamIndex = i;
                std::cout << "Found Video Stream: Index " << videoStreamIndex << std::endl;
                // // Debug: Print video codec information
                // std::cout << "Debug: Video Codec Information:" << std::endl;
                // av_dump_format(formatCtx, videoStreamIndex, videoFile, 0);
            }
            else if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && audioStreamIndex < 0)
            {
                audioStreamIndex = i;
                std::cout << "Found Audio Stream: Index " << audioStreamIndex << std::endl;
                // // Debug: Print audio codec information
                // std::cout << "Debug: Audio Codec Information:" << std::endl;
                // av_dump_format(formatCtx, audioStreamIndex, videoFile, 0); // Changed this line
            }
        }

        if (videoStreamIndex == -1 && audioStreamIndex == -1)
        {
            std::cerr << "Error: Could not find video or audio stream." << std::endl;
            avformat_close_input(&formatCtx); // Close input on failure
            return;
        }

        // Open video codec
        if (videoStreamIndex >= 0)
        {
            videoCodecCtx = avcodec_alloc_context3(nullptr);
            if (!videoCodecCtx)
            {
                std::cerr << "Error: Could not allocate video codec context." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }
            avcodec_parameters_to_context(videoCodecCtx, formatCtx->streams[videoStreamIndex]->codecpar);
            videoCodec = avcodec_find_decoder(videoCodecCtx->codec_id);
            if (!videoCodec)
            {
                std::cerr << "Error: Could not find video codec." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }
            if (avcodec_open2(videoCodecCtx, videoCodec, nullptr) < 0)
            {
                std::cerr << "Error: Could not open video codec." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }
        }

        // Open audio codec
        if (audioStreamIndex >= 0)
        {
            audioCodecCtx = avcodec_alloc_context3(nullptr);
            if (!audioCodecCtx)
            {
                std::cerr << "Error: Could not allocate audio codec context." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }
            avcodec_parameters_to_context(audioCodecCtx, formatCtx->streams[audioStreamIndex]->codecpar);
            audioCodec = avcodec_find_decoder(audioCodecCtx->codec_id);
            if (!audioCodec)
            {
                std::cerr << "Error: Could not find audio codec." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }
            if (avcodec_open2(audioCodecCtx, audioCodec, nullptr) < 0)
            {
                std::cerr << "Error: Could not open audio codec." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }

            // Initialize SDL Mixer
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
            {
                std::cerr << "Error: Failed to open audio channel: " << Mix_GetError() << std::endl;
                return;
            }

            // Initialize music with SDL Mixer
            music = Mix_LoadMUS(musicFile);
            if (!music)
            {
                std::cerr << "Error: Failed to load music file: " << Mix_GetError() << std::endl;
                return;
            }
        }
    }

    /**
     * @brief default FFmpegVideoPlayer deconstructor
     */
    ~FFmpegVideoPlayer()
    {
        if (videoCodecCtx)
        {
            avcodec_free_context(&videoCodecCtx);
        }
        if (audioCodecCtx)
        {
            avcodec_free_context(&audioCodecCtx);
        }
        if (formatCtx)
        {
            avformat_close_input(&formatCtx);
        }
        if (music)
        {
            Mix_FreeMusic(music);
        }
        Mix_CloseAudio();
    }

    /**
     * @brief play audioFile
     *
     * The audio playback pipeline is below
     *
     * Original file -> split into videoFile/musicFile -> musicFile -> initialise SDL_Mixer -> Mix_PlayMusic -> playAudio() -> playVideo() {playAudio()}
     */
    void playAudio() const
    {
        // Play music
        if (Mix_PlayMusic(music, 0) == -1)
        {
            std::cerr << "Error: Failed to play music: " << Mix_GetError() << std::endl;
            return;
        }
    }

    /**
     * @brief play the video and call the audio at the same time
     *
     * The video playback pipeline is below
     *
     * Original file -> split into videoFile/musicFile -> videoFile -> videoStream -> while (packet -> frame -> texture -> renderer)
     *
     * Their is an input event loop because it's important to allow moving/resizing/closing the window while the video is playing
     * if you havn't initialised the event loop outside of this function yet.
     *
     */
    void playVideo() const
    {
        // Check if constructor initialised successfully
        if (!formatCtx || !videoCodecCtx || !audioCodecCtx)
        {
            std::cerr << "Error: FFmpeg initialization failed." << std::endl;
            return;
        }

        // Create SDL texture
        SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING,
                                                 videoCodecCtx->width, videoCodecCtx->height);
        if (texture == nullptr)
        {
            std::cerr << "Error: Could not create SDL texture: " << SDL_GetError() << std::endl;
            return;
        }

        // Allocate frame
        AVFrame *frame = av_frame_alloc();
        AVPacket packet;

        // Calculate delay to achieve desired frame rate
        double frame_delay = 1.0 / av_q2d(formatCtx->streams[videoStreamIndex]->avg_frame_rate);

        // Start audio playback
        playAudio();

        // Start video playback loop
        bool end_of_stream = false; // Flag to track end of video stream
        while (!end_of_stream)      // Loop until end of stream
        {
            // Read video frames
            while (!end_of_stream && av_read_frame(formatCtx, &packet) >= 0)
            {
                if (packet.stream_index == videoStreamIndex)
                {
                    avcodec_send_packet(videoCodecCtx, &packet);
                    avcodec_receive_frame(videoCodecCtx, frame);

                    SDL_RenderClear(renderer);

                    // Update the video texture
                    SDL_UpdateYUVTexture(texture, nullptr,
                                         frame->data[0], frame->linesize[0],
                                         frame->data[1], frame->linesize[1],
                                         frame->data[2], frame->linesize[2]);

                    // Render the video frame
                    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
                    SDL_RenderPresent(renderer);

                    // Delay the video so that it plays at the same speed as video stream
                    SDL_Delay((Uint32)(frame_delay * 1000)); // Convert to milliseconds

                    /*
                        It's necessary to have an event loop here.
                        The reason is while the video is playing, if you move the window
                        SDL expects their to be a key input handle loop logic to take care of this event
                        but because their are no case for events it will crash.

                        Thus we initialise a fake event loop and also pressing any button skips the cutscene which
                        can be customised
                    */
                    SDL_Event event;
                    while (SDL_PollEvent(&event))
                    {
                        switch (event.type)
                        {
                        case SDL_QUIT:
                        case SDL_KEYDOWN:
                        case SDL_CONTROLLERBUTTONDOWN:
                        case SDL_MOUSEBUTTONDOWN:
                        case SDL_FINGERDOWN:
                            end_of_stream = true;
                            break;
                        }
                    }
                }
                av_packet_unref(&packet);
            }

            // When video stream ends, quit and return
            if (av_read_frame(formatCtx, &packet) == AVERROR_EOF)
                end_of_stream = true;
        }

        // Cleanup
        av_frame_free(&frame);
        SDL_DestroyTexture(texture);
    }
};
