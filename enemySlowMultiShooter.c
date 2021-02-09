#include "common.h"

extern void addPowerup(int x, int y);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void angledSlope(int x1, int y1, int x2, int y2, float angle, float *dx, float *dy);
extern int getDistance(int x1, int y1, int x2, int y2);
void blitRotated(SDL_Texture *texture, int x, int y, float angle);
extern Entity *createBullet(Entity *shooter);
extern SDL_Texture *loadTexture(char *filename);

extern Entity *player;
extern Entity *self;
extern Stage stage;

extern SDL_Texture *enemyTexture[10];

extern void initEnemies(void);
static void tickSlowMultiShooter(void);
void slowMultiShooterShot(void);
extern void enemyDie(void);

void spawnSlowMultiShooter(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;
    e->weapon = slowMultiShooterShot;
    e->texture = enemyTexture[SLOW_MULTI_SHOOTER];
    e->speed = MIN(3 + (stage.wave * 0.1), 7); //wave difficulty modificator
    e->tick = tickSlowMultiShooter;
    e->health = 8;
    e->reload = FPS;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 255;
    e->color.g = 85;
    e->color.b = 33;
    e->color.a = 255;
    e->die = enemyDie;
}

static void tickSlowMultiShooter(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);

        if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_WIDTH / 2) {
            slowMultiShooterShot();
            self->reload = FPS;
        }
    }
}

void slowMultiShooterShot(void) {
    Entity *b;
    int c = 3;
    if (stage.wave >= 10) c = 4;
    for (int i = -c; i <= c; i++) {
        b = createBullet(self);
        b->angle += i * 10;
        b->health = 35;
        angledSlope(player->x, player->y, b->x, b->y, i * 10, &b->dx, &b->dy);
        b->dx *= 8;
        b->dy *= 8;
        b->damage = 2;
    }
}