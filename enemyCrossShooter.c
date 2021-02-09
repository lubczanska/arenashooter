#include "common.h"

extern void addPowerup(int x, int y);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void angledSlope(int x1, int y1, int x2, int y2, float angle, float *dx, float *dy);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern int getDistance(int x1, int y1, int x2, int y2);
void blitRotated(SDL_Texture *texture, int x, int y, float angle);
extern Entity *createBullet(Entity *shooter);
extern SDL_Texture *loadTexture(char *filename);

extern Entity *player;
extern Entity *self;
extern Stage stage;

extern SDL_Texture *enemyTexture[10];

extern void initEnemies(void);
static void tickCrossShooter(void);
static void tickCrossShooterSpin(void);
void crossShooterShot(void);
extern void enemyDie(void);

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
    if (stage.wave > 5) e->tick = tickCrossShooter;
    else e->tick = tickCrossShooterSpin;
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
        if (self->reload <= 0) {
            crossShooterShot();
            self->reload = 30;
        }
    }
}

static void tickCrossShooterSpin(void) {
    if (player != NULL) {
        self->angle = (self->angle + 1) % 360;
        if (self->reload <= 0) {
            crossShooterShot();
            self->reload = 20;
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