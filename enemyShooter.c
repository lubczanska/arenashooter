#include "common.h"

extern void addPowerup(int x, int y);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
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
static void tickShooter(void);
void shooterShot(void);
extern void enemyDie(void);

void spawnShooter(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;


    e->weapon = shooterShot;
    e->texture = enemyTexture[SHOOTER];
    e->speed = MIN(3 + (stage.wave * 0.1), 7); //wave difficulty modificator
    e->tick = tickShooter;
    e->health = 5;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 250;
    e->color.g = 20;
    e->color.b = 60;
    e->color.a = 255;
    e->die = enemyDie;
}

static void tickShooter(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
        if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_HEIGHT / 2) {
            shooterShot();
            self->reload = 12;
        }
    }
}

void shooterShot(void) {
    Entity *b;
    b = createBullet(self);
    getSlope(player->x, player->y, b->x, b->y, &b->dx, &b->dy);
    b->dx *= MIN(12 + (stage.wave * 0.3), 16);
    b->dy *= MIN(12 + (stage.wave * 0.3), 16);
    //reload controlled by tick function
}
