#include "common.h"

#include "SDL2/SDL_mixer.h"

static void loadSounds(void);

static Mix_Chunk *sounds[MAX_CHANNELS];
static Mix_Music *music;

void initSounds(void) {
    memset(sounds, 0, sizeof(Mix_Chunk*) * MAX_CHANNELS);
    music = NULL;
    loadSounds();
}

void loadMusic(char *filename) {
    if (music != NULL) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = NULL;
    }
    music = Mix_LoadMUS(filename);
}

static void loadSounds(void) {
    sounds[ENEMY_HIT] = Mix_LoadWAV("sounds/laser_shot.wav");
    sounds[PLAYER_HIT] = Mix_LoadWAV("sounds/player_hit.wav");
    sounds[POWERUP] = Mix_LoadWAV("sounds/item_pick.wav");
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "loaded sounds");
}

void playMusic(int loop) {
    Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel) {
    Mix_PlayChannel(channel, sounds[id], 0);
}