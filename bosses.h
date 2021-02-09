#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void spawnShooter(int x, int y);
extern void spawnRunner(int x, int y);
extern void addEnemyDeathEffect(Entity *e);
extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Entity *player;
extern Stage stage;
extern Entity *boss;

extern void spawnBossShooter(void);
extern void spawnBossSpawner(void);
extern void spawnBossSpin(void);
extern void spawnBossSplit(void);