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
static void tickSlug(void);
void slugShot(void);
extern void enemyDie(void);

void spawnSlug(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_BOSS;
    e->x = SCREEN_WIDTH/2;
    e->y = SCREEN_HEIGHT/2;
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
            //self->reload /= getDistance(self->x, self->y, self->x + self->dx, self->y + self->dy);
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