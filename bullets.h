#include "common.h"

extern void blitRotated(SDL_Texture *texture, int x, int y, float angle);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern float getAngle(int x1, int y1, int x2, int y2);
extern int getDistance(int x1, int y1, int x2, int y2);
extern SDL_Texture *loadTexture(char *filename);

//player weapons
extern void fireDefaultGun(void);
extern void fireFastGun(void);
extern void fireTripleGun(void);
extern void fireSlowGun(void);
//enemy weapons
extern void shooterShot(void);
extern void crossShooterShot(void);
extern void lineShooterShot(void);
extern void sniperShot(void);
extern void multiShooterShot(void);
extern void starShooterShot(void);
extern void playSound(int id, int channel);

extern App app;
extern Entity *player;
extern Entity *self;
extern Stage stage;