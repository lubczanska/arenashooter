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

void playMusic(int loop) {
    Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "playing sound");
    Mix_PlayChannel(channel, sounds[id], 0);
}

static void loadSounds(void) {
    sounds[SHOT] = Mix_LoadWAV("sounds/gun_sound.ogg");
}