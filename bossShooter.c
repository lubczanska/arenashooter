#include "bossClasses.h"

static void bossShooterTick(void);

Entity *spawnBossShooter(void) {
    Entity *e;
    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->health = 30 + (stage.wave % 5) * 5;
    e->tick = bossShooterTick;
    e->die = bossDie;
    e->speed = 5;
    e->side = SIDE_BOSS;
    e->x = SCREEN_WIDTH / 2;
    e->y = SCREEN_HEIGHT / 2;
    e->texture = bossTexture[B_SHOOTER];
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 255;
    e->color.g = 20;
    e->color.b = 60;
    e->color.a = 255;
    return e;
}

static void bossShooterTick(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
        if (self->reload <= 0) {
            shooterShot();
            self->reload = 6;
        }
    }
}
