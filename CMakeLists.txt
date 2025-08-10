cmake_minimum_required(VERSION 3.0)
project(GalacticaInferno)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where to find SFML installed via Homebrew
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml@2")

# Find SFML components
find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics audio network)

# Add your source files here
add_executable(GalacticaInferno
  main.cpp
    Bomb.cpp
    Explosion.cpp
    Game.cpp
    GameObject.cpp
    Helicopter.cpp
    Meteor.cpp
    Missile.cpp
    Pipe.cpp
    Projectile.cpp
    ScrollingBackground.cpp
)

# Link SFML libraries
target_link_libraries(GalacticaInferno
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
)
