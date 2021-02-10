cmake_minimum_required(VERSION 3.16)
project(arenashooter C)

find_package(SDL2 REQUIRED)
include_directories(arenashooter ${SDL2_INCLUDE_DIRS})

add_executable(arenashooter src/main.c src/draw.c src/init.c src/input.c src/stage.c src/common.h src/defines.h src/structs.h src/entities.c src/player.c src/util.c src/text.c src/bullets.c src/enemies.c src/items.c src/title.c src/playerweapons.c src/sound.c src/enemyweapons.c src/bosses.c src/bossSplit.c src/bossSpawner.c src/bossShooter.c src/effects.c src/bossSpin.c src/enemyShooter.c src/enemySniper.c src/enemyLineShooter.c src/enemyMultiShooter.c src/enemyCrossShooter.c src/enemyStarShooter.c src/enemySlowMultiShooter.c src/enemySlug.c src/help.c src/settings.c src/prompts.c src/bosses.h src/bossClasses.h src/bullets.h src/effects.h src/enemies.h src/enemyClasses.h src/entities.h src/init.h src/items.h src/player.h src/playerweapons.h src/title.h src/stage.h src/enemyRunner.c src/enemyRammer.c)
target_link_libraries(arenashooter ${SDL2_LIBRARIES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)

INCLUDE_DIRECTORIES(arenashooter ${SDL2IMAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(project ${SDL2MIXER_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(arenashooter ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} m ${SDL2MIXER_LIBRARIES})