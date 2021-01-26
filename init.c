#include "common.h"

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

extern void initBullets(void);
extern void initEnemies(void);
extern void initFonts(void);
extern void initItems(void);
extern void initPlayer(void);

extern App app;


void initSDL(void) {
	int rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	app.window = SDL_CreateWindow("arenashooter v1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	SDL_ShowCursor(0);
}

void initGame(void) {
	initFonts();
	initPlayer();
	initEnemies();
	initBullets();
	initItems();
}

void cleanup(void) {
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	SDL_Quit();
}
