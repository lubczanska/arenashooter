#include "enemyClasses.h"

static void tickCrossShooter(void);
void crossShooterShot(void);

void spawnCrossShooter(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_BOSS;
    e->angle = getAngle(player->x, player->y, e->x, e->y);
    e->x = 250 + (rand() % 1500);
    e->y = 250 + (rand() % 800);
    e->weapon = crossShooterShot;
    e->texture = enemyTexture[CROSS_SHOOTER];
    e->tick = tickCrossShooter;
    e->health = 10;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 119;
    e->color.g = 22;
    e->color.b = 245;
    e->color.a = 255;
    e->die = enemyDie;
}


static void tickCrossShooter(void) {
    if (player != NULL) {
        self->angle = (self->angle + 1) % 360;
        if (self->reload <= 0) {
            crossShooterShot();
            self->reload = MAX(20 - (stage.wave * 0.1), 16);
        }
    }
}

void crossShooterShot(void) {
    Entity *b;
    for (int i = 0; i < 4; i++) {
        int ang = self->angle + i*90;
        b = createBullet(self);
        b->angle = ang;
        b->health = FPS*2;
        angledSlope(SCREEN_WIDTH, SCREEN_HEIGHT/2, b->x, b->y, ang, &b->dx, &b->dy);
        b->dx *= MIN(5 + (stage.wave * 0.3), 16);
        b->dy *= MIN(5 + (stage.wave * 0.3), 16);

    }
    //reload controlled by tick function
}