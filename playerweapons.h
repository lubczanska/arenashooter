#include "common.h"

extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void angledSlope(int x1, int y1, int x2, int y2, float angle, float *dx, float *dy);
extern int getDistance(int x1, int y1, int x2, int y2);
extern float getAngle(int x1, int y1, int x2, int y2);
extern Entity *createBullet(Entity *shooter);
extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Entity *player;
extern Stage stage;

