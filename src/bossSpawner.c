#include "bossClasses.h"

static void bossSpawnerTick1(void);
static void bossSpawnerTick2(void);

Entity *spawnBossSpawner(void) {
    Entity *e;
    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->health = 40 + (stage.wave % 5) * 20;
    if (stage.wave >= 10) e->tick = bossSpawnerTick2;
    else e->tick = bossSpawnerTick1;
    e->die = bossDie;
    e->side = SIDE_BOSS;
    e->speed = 1;
    e->x = SCREEN_WIDTH / 2;
    e->y = SCREEN_HEIGHT / 2;
    e->texture = bossTexture[B_SPAWNER];
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 119;
    e->color.g = 22;
    e->color.b = 245;
    e->color.a = 255;
    return e;
}

static void bossSpawnerTick1(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
        if (self->reload <= 0) {
            spawnRunner(self->x, self->y);
            self->reload = FPS - 10;
        }
    }
}

static void bossSpawnerTick2(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
        if (self->reload <= 0) {
            spawnShooter(self->x, self->y);
            self->reload = FPS;
        }
    }
}