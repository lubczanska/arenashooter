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
extern App app;

extern SDL_Texture *enemyTexture[10];

extern void initEnemies(void);
static void tickSniper(void);
void sniperShot(void);
extern void enemyDie(void);
static int targeterAlpha;

void spawnSniper(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;
    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;
    e->speed = 2;
    e->reload = FPS * 3;
    e->weapon = sniperShot;
    e->texture = enemyTexture[SNIPER];
    e->tick = tickSniper;
    e->health = 7;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 255;
    e->color.g = 255;
    e->color.b = 0;
    e->color.a = 255;
    e->die = enemyDie;
}

static void tickSniper(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        if(self->reload > FPS * 2) {
            getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
        }
        else {
            self->dx = self->dy = 0;
            SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, targeterAlpha);
            SDL_RenderDrawLine(app.renderer, self->x, self->y, player->x, player->y);
            targeterAlpha += 10;
        }
        if (self->reload <=0 ) {
            sniperShot();
            self->reload = FPS * 4;
            targeterAlpha = 10;
        }
    }
}

void sniperShot(void) {
    Entity *b;
    b = createBullet(self);
    getSlope(player->x, player->y, b->x, b->y, &b->dx, &b->dy);
    b->dx *= 30;
    b->dy *= 30;
    b->damage = 4;
    //reload controlled by tick function
}