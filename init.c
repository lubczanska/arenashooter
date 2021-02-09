#include "init.h"

void loadMusic(char *filename);
void playMusic(int loop);

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

void initSDL(void) {
	int rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		exit(1);
	}
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        SDL_Log("Couldn't initialize SDL Mixer: %s", SDL_GetError());
        exit(1);
    }
    Mix_AllocateChannels(MAX_CHANNELS);
    app.volumeMusic = 30;
    app.volumeSounds = 50;
    Mix_Volume(CH_ANY, app.volumeSounds);
    Mix_VolumeMusic(app.volumeMusic);
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) < 0) {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        exit(1);
    }
    SCREEN_WIDTH = dm.w;
    SCREEN_HEIGHT = dm.h;

    app.window = SDL_CreateWindow("arenashooter v1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	SDL_ShowCursor(0);
}

void initGame(void) {
	initFonts();
	initPlayer();
	initEnemies();
	initBosses();
	initBullets();
	initItems();
    initEffects();
    initSounds();
    loadMusic("sounds/muzyczka.mp3");
    playMusic(1);
}

void cleanup(void) {
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_Quit();
}
