#include "enemyClasses.h"

static void tickMultiShooter(void);
void multiShooterShot(void);

void spawnMultiShooter(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;
    e->weapon = multiShooterShot;
    e->texture = enemyTexture[MULTI_SHOOTER];
    e->speed = MIN(4 + (stage.wave * 0.1), 7); //wave difficulty modificator
    e->tick = tickMultiShooter;
    e->health = 5;
    e->reload = FPS / 2;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 33;
    e->color.g = 120;
    e->color.b = 255;
    e->color.a = 255;
    e->die = enemyDie;
}

static void tickMultiShooter(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);

        if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_WIDTH / 2) {
            multiShooterShot();
            self->reload = FPS / 2;
        }
    }
}

void multiShooterShot(void) {
    Entity *b;
    int c = 1;
    if (stage.wave >= 10) c = 2;
    for (int i = -c; i <= c; i++) {
        b = createBullet(self);
        b->angle += i * 10;
        b->health = FPS - 10;
        angledSlope(player->x, player->y, b->x, b->y, i * 10, &b->dx, &b->dy);
        b->dx *= 10;
        b->dy *= 10;
        b->damage = 2;
    }
}
