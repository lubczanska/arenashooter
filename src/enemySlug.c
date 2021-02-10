#include "enemyClasses.h"

static void tickSlug(void);
void slugShot(void);

void spawnSlug(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_BOSS;
    e->x = 250 + (rand() % 1500);
    e->y = 250 + (rand() % 800);
    e->weapon = slugShot;
    e->texture = enemyTexture[SLUG];
    e->speed = 8;
    e->tick = tickSlug;
    e->health = 10;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 158;
    e->color.g = 102;
    e->color.b = 255;
    e->color.a = 255;
    e->die = enemyDie;
    e->dx = (1 + (rand() % 99)) * 0.01;
    e->dy = (1 + (rand() % 99)) * 0.01;
    self->angle = getAngle(self->x, self->y, self->x + self->dx, self->y + self->dy);
}

static void tickSlug(void) {
    if (player != NULL) {
        if ((self->x - self->w) <=0 || (self->x + self->w) >= SCREEN_WIDTH) {
            self->dx *= -1;
            self->angle = getAngle(self->x, self->y, self->x + self->dx, self->y + self->dy);
        }
        if ((self->y - self->h)<=0 || (self->y + self->h) >= SCREEN_HEIGHT) {
            self->dy *= -1;
            self->angle = getAngle(self->x, self->y, self->x + self->dx, self->y + self->dy);
        }
        if (self->reload <= 0) {
            slugShot();
            self->reload = 8;
        }
    }
}

void slugShot(void) {
    Entity *b;
    b = createBullet(self);
    b->dx = 0;
    b->dy = 0;
    b->health = FPS*3;
    //reload controlled by tick function
}