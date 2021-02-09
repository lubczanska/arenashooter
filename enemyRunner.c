#include "enemyClasses.h"

static void tickRunner(void);

void spawnRunner(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;

    e->texture = enemyTexture[RUNNER];
    e->speed = MIN(6 + (stage.wave * 0.2), 9);
    e->tick = tickRunner;
    e->health = 3;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 125;
    e->color.g = 62;
    e->color.b = 173;
    e->color.a = 255;
    e->die = enemyDie;
}

static void tickRunner(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
    }
}
