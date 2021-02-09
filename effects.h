#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Entity *self;
extern Entity *player;
extern Stage stage;