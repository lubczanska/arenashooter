cmake_minimum_required(VERSION 3.17)
project(arenashooter C)

find_package(SDL2 REQUIRED)
include_directories(arenashooter ${SDL2_INCLUDE_DIRS})

add_executable(arenashooter main.c draw.c init.c keyboard.c stage.c common.h defines.h structs.h entities.c player.c util.c text.c bullets.c enemies.c items.c title.c playerweapons.c sound.c enemyweapons.c)
target_link_libraries(arenashooter ${SDL2_LIBRARIES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)

INCLUDE_DIRECTORIES(arenashooter ${SDL2IMAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(project ${SDL2MIXER_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(arenashooter ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} m ${SDL2MIXER_LIBRARIES})