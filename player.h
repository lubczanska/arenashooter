#include "common.h"

extern float getAngle(int x1, int y1, int x2, int y2);
extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Entity *player;
extern Stage stage;

extern void fireDefaultGun(void);
extern void fireFastGun(void);
extern void fireTripleGun(void);
extern void fireSlowGun(void);
extern void addPlayerDeathEffect(void);
