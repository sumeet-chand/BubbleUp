# TO DO

* New game facing memory leak
* Use Intel profiler to find which process taking must function memory
* Fix cppcheck errors
* Compile in both g++ and clang++ on windows to compare any errors that appear, use clang error checker
* On minimise does music stop?
* Fix Camera to follow player
* Implement a Mod store website for users and me to upload mods/expansions and that they can be added to the game, the browser will open in game.
* Error ID: 1
Description: Memory leak error when starting new game.
Replicate error steps: Start program e.g, main.exe or main (on linux for error)
Date escalated: 5th August 2024
Error message: Error in terminal output only appears while running program on linux
* Error ID: 2
Description: Github Actions CI/CD error with Windows vm failing to compile code. Issue could be related to import for boost within WebserverClient.hpp
possibly look at this answer https://stackoverflow.com/questions/1372480/c-redefinition-header-files-winsock2-h 
Date escalated: 5th August 2024
Error message: 

Run g++ -fdiagnostics-color=always -ID:\a\BubbleUp\BubbleUp/headers -ID:/a/_temp/msys64/mingw64/include  `
In file included from D:/a/_temp/msys64/mingw64/include/winerror.h:4739,
                 from D:/a/_temp/msys64/mingw64/include/winbase.h:2817,
                 from D:/a/_temp/msys64/mingw64/include/windows.h:70,
                 from D:/a/_temp/msys64/mingw64/include/winsock2.h:23,
                 from D:\a\BubbleUp\BubbleUp/headers/WebserverClient.hpp:17,
                 from D:/a/BubbleUp/BubbleUp/headers/entities/Bot.hpp:14,
                 from D:/a/BubbleUp/BubbleUp/headers/globals.hpp:41,
                 from D:\a\BubbleUp\BubbleUp/tests/testcases.cpp:18:
D:/a/_temp/msys64/mingw64/include/fltwinerror.h:12: warning: "FACILITY_USERMODE_FILTER_MANAGER" redefined
   12 | #define FACILITY_USERMODE_FILTER_MANAGER 0x1f
      | 
D:/a/_temp/msys64/mingw64/include/winerror.h:38: note: this is the location of the previous definition
   38 | #define FACILITY_USERMODE_FILTER_MANAGER 31
      | 
In file included from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/ext/string_conversions.h:41,
                 from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/bits/basic_string.h:3960,
                 from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/string:53,
                 from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/bits/locale_classes.h:40,
                 from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/bits/ios_base.h:41,
                 from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/ios:42,
                 from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/ostream:38,
                 from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/iostream:39,
                 from D:\a\BubbleUp\BubbleUp/tests/testcases.cpp:10:
C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/cstdlib:137:11: error: 'at_quick_exit' has not been declared in '::'
  137 |   using ::at_quick_exit;
      |           ^~~~~~~~~~~~~
C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/cstdlib:160:11: error: 'quick_exit' has not been declared in '::'
  160 |   using ::quick_exit;
      |           ^~~~~~~~~~
In file included from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/bits/chrono.h:40,
                 from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/chrono:39,
                 from D:\a\BubbleUp\BubbleUp/tests/testcases.cpp:13:
C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/ctime:80:11: error: 'timespec_get' has not been declared in '::'
   80 |   using ::timespec_get;
      |           ^~~~~~~~~~~~
In file included from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/bits/chrono.h:40,
                 from C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/chrono:39,
                 from D:\a\BubbleUp\BubbleUp/src/DebugLogging.cpp:9:
C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include/c++/ctime:80:11: error: 'timespec_get' has not been declared in '::'
   80 |   using ::timespec_get;
      |           ^~~~~~~~~~~~
* Add reputation/personality for all player/enemy .hpp/cpp constructors then add in EntityManager for creating randomly
* Add lists of items for sale in draw shops
* #1 importance new parameter to add to render_text(const std::string textAllignment) (copy from button to find code to use)
{
    if (textAllignment = "left")
    {
        // allign text left
    }
    else if (textAllignment = "center")
    {
        // allign text center
    }
    else {
        // allign text right
    }
}
* If bot collides and they die, what happens? should delete from game in sandbox 100 and test
* Convert game to use tiles - https://www.youtube.com/watch?v=KvSjJ-kdGio
* Create a viewport and minimap - https://lazyfoo.net/tutorials/SDL/09_the_viewport/index.php
* Settings menu - add result e.g. Music ON || Music OFF
* Swapping to full screen doesn't update position of all buttons.. create vector loop
* Implement gettext for translations get rid of map global variable and approach
* Convert all cout messages to log non crit
* EntityManager - add functions for creating individual enemies
* DropdownButton, on_selected() draw_all_dropdown_options()
* Implement a level editor
* introduce a co-op multiplayer mechanic, splitscreen and toggle
* Make a cutscene
* Test Vscync button
* Test saving/loading
* Test game update
* Localisation using map to change button font
* include option to use item
* include option to shoot melee and ranged
* Note skill to view all journals picked up
* Add in game store to buy/sell items + another vendor for skills, etc.,
* Gamepad handle doesn't recognise continous arrow key press.
* Make game isometric to add a jump mechanic (jump is an illussion with no height z axis, just texture move up
* and no collission when pressing jump button e.g. jumping over hedge)
* Add story, with player select of dog, cat, fish, bird each with specials e.g. dog passive easy, cat hard
* Unit testing
* WASM on itch.io so game is playable in a web browser
* Use Visual Studio to add .ico
* Final game test with family member
* To demonstrate engine create a raycaster - // https://www.youtube.com/watch?v=gYRrGTC7GtA&t=3s
* choco install cloc, maybe include that in a github action? or after every build somewhere to get the statistics posted to know the progress for personal goals
* SDL uses 1 core for everything by default, even using thraeding will not split cores (to confirm)
since SDL is like this SDL_run(), update, render, movements, it's possible to run all 3 of those functions in its own core which makes the program completely multithreaded. To implement later stage,
may require <atomic>
* Regenerate Doxyfiles on project completion