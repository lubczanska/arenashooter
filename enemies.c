#include "common.h"

extern void addPowerup(int x, int y);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern int getDistance(int x1, int y1, int x2, int y2);
void blitRotated(SDL_Texture *texture, int x, int y, float angle);
extern Entity *createBullet(Entity *shooter);
extern SDL_Texture *loadTexture(char *filename);
extern void addEnemyDeathEffect(Entity *e);

extern Entity *player;
extern Entity *self;
extern Stage stage;

//enemy tick functions
static void tickRunner(void);
static void tickRammer(void);
void enemyDie(void);

SDL_Texture *enemyTexture[10];

void initEnemies(void) {
	enemyTexture[SHOOTER] = loadTexture("resources/shooter.png");
    enemyTexture[LINE_SHOOTER] = loadTexture("resources/playerSquare.png");
    enemyTexture[CROSS_SHOOTER] = loadTexture("resources/hexagon.png");
    enemyTexture[MULTI_SHOOTER] = loadTexture("resources/hexagon.png");
    enemyTexture[SLOW_MULTI_SHOOTER] = loadTexture("resources/pentagon.png");
    enemyTexture[STAR_SHOOTER] = loadTexture("resources/8star.png");
    enemyTexture[SNIPER] = loadTexture("resources/triangle.png");
    enemyTexture[RUNNER] = loadTexture("resources/playerSquare.png");
    enemyTexture[RAMMER] = loadTexture("resources/playerSquare.png");
    enemyTexture[SLUG] = loadTexture("resources/playerSquare.png");
}

void spawnRunner(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;

    e->texture = enemyTexture[RUNNER];
    e->speed = MIN(6 + (stage.wave * 0.5), 9);
    e->tick = tickRunner;
    e->health = 3;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 125;
    e->color.g = 62;
    e->color.b = 173;
    e->color.a = 255;
    e->die = enemyDie;
}

void spawnRammer(int x, int y) {
    Entity *e;
    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;

    e->weapon = 0;
    e->texture = enemyTexture[RAMMER];
    e->speed = 4;
    e->reload = FPS * 2;
    e->health = 4;
    e->tick = tickRammer;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 255;
    e->color.g = 102;
    e->color.b = 156;
    e->color.a = 255;
    e->die = enemyDie;
}

static void tickRammer(void) {
    if (player != NULL) {
        if (self->damage == 1) {
            if (self->speed >= 6 && (self->x - self->w <= 0 || self->x + self->w >= SCREEN_WIDTH || self->y - self->h <= 0 || self->y + self->h >= SCREEN_HEIGHT)) {
                self->speed = 2;
                self->damage = 0;
                self->reload = FPS;
            }
            else {
                self->speed *= 1.1;
            }
        }
        else {
            self->angle = getAngle(self->x, self->y, player->x, player->y);
            getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
            if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_HEIGHT / 2) {
                self->speed = 4;
                getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
                self->damage = 1;
            }
        }
    }
}

static void tickRunner(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
    }
}

void enemyDie(void) {
    addEnemyDeathEffect(self);
	stage.score += 10; //TODO: score scaling with wave?
	stage.waveEnemies--;
}
