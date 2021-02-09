#include "common.h"

extern void addPowerup(int x, int y);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern int getDistance(int x1, int y1, int x2, int y2);
extern void blitRotated(SDL_Texture *texture, int x, int y, float angle);
extern Entity *createBullet(Entity *shooter);
extern SDL_Texture *loadTexture(char *filename);
extern void addEnemyDeathEffect(Entity *e);

extern Entity *player;
extern Entity *self;
extern Stage stage;