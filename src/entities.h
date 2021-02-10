#include "common.h"

extern void blitRotated(SDL_Texture *texture, int x, int y, float angle);
extern int getDistance(int x1, int y1, int x2, int y2);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);

extern Entity *player;
extern Entity *self;
extern Stage stage;
