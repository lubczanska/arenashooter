#include "enemyClasses.h"

static void tickLineShooter(void);
void lineShooterShot(void);

void spawnLineShooter(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_BOSS;
    e->x = x;
    e->y = y;

    e->reload = FPS;
    e->weapon = lineShooterShot;
    if (MIN(e->y, SCREEN_HEIGHT - e->y) < 50) e->dy = 1;
    else e->dx = 1;
    e->texture = enemyTexture[LINE_SHOOTER];
    e->speed = MIN(3 + (stage.wave * 0.1), 7); //wave difficulty modificator
    e->tick = tickLineShooter;
    self->reload = FPS;
    e->health = 5;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 184;
    e->color.g = 48;
    e->color.b = 200;
    e->color.a = 255;
    e->die = enemyDie;
}

static void tickLineShooter(void) {
    if (player != NULL) {
        if ((self->dx == 1 && (self ->x + self->w) >= SCREEN_WIDTH) || (self->dx == -1 && (self ->x - self->w) <= 0)) {
            self->dx *= -1;
            self->angle = (self->angle + 180) % 360;
        }
        if ((self->dy == 1 && (self ->y + self->h) >= SCREEN_HEIGHT) || (self->dy == -1 && (self ->y - self->h) <= 0)) {
            self->dy *= -1;
            self->angle = (self->angle + 180) % 360;
        }

        if (self->reload <= 0) {
            lineShooterShot();
            self->reload = MAX(FPS - (stage.wave * 0.2), 30);
        }
    }
}

void lineShooterShot(void) {
    Entity *b;
    b = createBullet(self);
    b->dx = self->dx * MIN(7 + (stage.wave * 0.3), 16);
    b->dy = self->dy * MIN(7 + (stage.wave * 0.3), 16);
}