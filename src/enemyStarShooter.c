#include "enemyClasses.h"

static void tickStarShooter(void);
void starShooterShot(void);

void spawnStarShooter(int x, int y) {
    Entity *e;
    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;

    e->weapon = starShooterShot;
    e->texture = enemyTexture[STAR_SHOOTER];
    e->speed = MIN(3 + (stage.wave % 5), 7); //wave difficulty modificator
    e->tick = tickStarShooter;
    e->health = 5;
    e->reload = FPS / 2;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 78;
    e->color.g = 23;
    e->color.b = 232;
    e->color.a = 255;
    e->die = enemyDie;
}

static void tickStarShooter(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);

        if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_WIDTH / 2) {
            starShooterShot();
            self->reload = FPS / 2;
        }
    }
}

void starShooterShot(void) {
    Entity *b;
    int c = MIN(8 + stage.wave, 20);
    for (int i = 0; i <= c; i++) {
        int ang = 0 + i * (360/c);
        b = createBullet(self);
        b->angle += ang;
        b->health = 20;
        angledSlope(player->x, player->y, b->x, b->y, ang, &b->dx, &b->dy);
        b->dx *= 10;
        b->dy *= 10;
        b->damage = 2;
    }
}