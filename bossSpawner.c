#include "bossClasses.h"

Entity *boss;

static void bossSpawnerTick1(void);
static void bossSpawnerTick2(void);

void spawnBossSpawner(void) {
    boss = malloc(sizeof(Entity));
    memset(boss, 0, sizeof(Entity));
    stage.entityTail->next = boss;
    stage.entityTail = boss;

    boss->health = 40 + (stage.wave % 5) * 10;
    if (stage.wave >= 10) boss->tick = bossSpawnerTick2;
    else boss->tick = bossSpawnerTick1;
    boss->die = bossDie;
    boss->side = SIDE_BOSS;
    boss->speed = 1;
    boss->x = SCREEN_WIDTH / 2;
    boss->y = SCREEN_HEIGHT / 2;
    boss->texture = bossTexture[B_SPAWNER];
    SDL_QueryTexture(boss->texture, NULL, NULL, &boss->w, &boss->h);
    boss->color.r = 119;
    boss->color.g = 22;
    boss->color.b = 245;
    boss->color.a = 255;
}

static void bossSpawnerTick1(void) {
    if (player != NULL) {
        boss->angle = getAngle(boss->x, boss->y, player->x, player->y);
        getSlope(player->x, player->y, boss->x, boss->y, &boss->dx, &boss->dy);
        if (boss->reload <= 0) {
            spawnRunner(boss->x, boss->y);
            boss->reload = FPS - 10;
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