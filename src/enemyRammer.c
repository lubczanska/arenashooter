#include "enemyClasses.h"

static void tickRammer(void);

void spawnRammer(int x, int y) {
    Entity *e;
    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;

    e->weapon = 0;
    e->texture = enemyTexture[RAMMER];
    e->speed = MIN(4 + (stage.wave * 0.1), 5);;
    e->reload = FPS * 2;
    e->health = 4;
    e->tick = tickRammer;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 255;
    e->color.g = 102;
    e->color.b = 156;
    e->color.a = 255;
    e->die = enemyDie;
}


static void tickRammer(void) {
    if (player != NULL) {
        if (self->damage == 1) {
            if (self->speed >= 6 && (self->x - self->w <= 0 || self->x + self->w >= SCREEN_WIDTH || self->y - self->h <= 0 || self->y + self->h >= SCREEN_HEIGHT)) {
                self->speed = 2;
                self->damage = 0;
                self->reload = FPS;
            }
            else {
                self->speed *= 1.1;
            }
        }
        else {
            self->angle = getAngle(self->x, self->y, player->x, player->y);
            getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
            if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_HEIGHT / 2) {
                self->speed = 4;
                getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
                self->damage = 1;
            }
        }
    }
}
