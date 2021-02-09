#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void spawnShooter(int x, int y);
extern void spawnRunner(int x, int y);
extern SDL_Texture *loadTexture(char *filename);
extern SDL_Texture *bossTexture[6];

extern void bossDie(void);

extern App app;
extern Entity *player;
extern Stage stage;
Entity *boss;

static void bossSpawnerTick1(void);
static void bossSpawnerTick2(void);

void spawnBossSpawner(void) {
    boss = malloc(sizeof(Entity));
    memset(boss, 0, sizeof(Entity));
    stage.entityTail->next = boss;
    stage.entityTail = boss;

    boss->health = 40;
    if (stage.wave >= 10) boss->tick = bossSpawnerTick2;
    else boss->tick = bossSpawnerTick1;
    boss->die = bossDie;
    boss->side = SIDE_BOSS;
    boss->speed = 1;
    boss->x = SCREEN_WIDTH / 2;
    boss->y = SCREEN_HEIGHT / 2;
    boss->texture = bossTexture[B_SPAWNER];
    SDL_QueryTexture(boss->texture, NULL, NULL, &boss->w, &boss->h);
    boss->color.r = 255;
    boss->color.g = 255;
    boss->color.b = 255;
    boss->color.a = 255;
}

static void bossSpawnerTick1(void) {
    if (player != NULL) {
        boss->angle = getAngle(boss->x, boss->y, player->x, player->y);
        getSlope(player->x, player->y, boss->x, boss->y, &boss->dx, &boss->dy);
        if (boss->reload <= 0) {
            spawnRunner(boss->x, boss->y);
            boss->reload = FPS;
        }
    }
}

static void bossSpawnerTick2(void) {
    if (player != NULL) {
        boss->angle = getAngle(boss->x, boss->y, player->x, player->y);
        getSlope(player->x, player->y, boss->x, boss->y, &boss->dx, &boss->dy);
        if (boss->reload <= 0) {
            spawnShooter(boss->x, boss->y);
            boss->reload = FPS;
        }
    }
}