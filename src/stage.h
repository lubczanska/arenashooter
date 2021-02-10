#include "common.h"

extern int getDistance(int x1, int y1, int x2, int y2);
extern SDL_Texture *loadTexture(char *filename);
extern void blit(SDL_Texture *texture, int x, int y, int center);
extern void doBullets(void);
extern void doEntities(void);
extern void doEffects(void);
extern void doPlayer(void);
extern void drawBullets(void);
extern void drawEntities(void);
extern void drawEffects(void);
extern void drawText(int x, int y, int r, int g, int b, int center, char *format, ...);
extern void drawBossBar(void);
extern void addPowerup(int x, int y);
extern void addPowerupBoss(void);
extern void addPlayer(void);
extern void spawnShooter(int x, int y);
extern void spawnCrossShooter(int x, int y);
extern void spawnLineShooter(int x, int y);
extern void spawnMultiShooter(int x, int y);
extern void spawnSlowMultiShooter(int x, int y);
extern void spawnStarShooter(int x, int y);
extern void spawnRunner(int x, int y);
extern void spawnRammer(int x, int y);
extern void spawnSniper(int x, int y);
extern void spawnSlug(int x, int y);
extern void spawnBoss(void);

extern App app;
extern Entity *player;
extern Stage stage;
extern int highscore;
