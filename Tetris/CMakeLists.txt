# CMakeList.txt : CMake project for Tetris, include source and define
# project specific logic here.
#

find_package(SDL2 REQUIRED)

# Add source to this project's executable.
add_executable (Tetris "Tetris.cpp" "Tetris.h" "Game.cpp" "Game.h" "GameSDLRenderer.cpp" "GameSDLRenderer.h")

target_link_libraries(Tetris SDL2::SDL2 SDL2::SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tetris PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
