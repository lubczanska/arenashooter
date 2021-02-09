#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void angledSlope(int x1, int y1, int x2, int y2, float angle, float *dx, float *dy);
extern void bossDie(void);
extern Entity *createBullet(Entity *shooter);
extern void fireEnemyBullet(void);
extern void shooterShot(void);
extern void addEnemyDeathEffect(Entity *e);
extern void spawnShooter(int x, int y);
extern void spawnRunner(int x, int y);

extern SDL_Texture *loadTexture(char *filename);
extern SDL_Texture *bossTexture[6];

extern App app;
extern Entity *player;
extern Stage stage;
extern Entity *self;

extern int bossMaxHealth;
extern int bossBarX;