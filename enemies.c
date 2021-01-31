#include "common.h"

extern void addPowerup(int x, int y);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern int getDistance(int x1, int y1, int x2, int y2);
void blitRotated(SDL_Texture *texture, int x, int y, float angle);
extern SDL_Texture *loadTexture(char *filename);

extern Entity *player;
extern Entity *self;
extern Stage stage;

//enemy tick functions
static void tickRunner(void);
static void tickRammer(void);
static void tickShooter(void);
static void tickCrossShooter(void);
static void tickLineShooter(void);
static void tickSniper(void);
static void die(void);

static SDL_Texture *enemyTexture;
static SDL_Texture *laserPointer;

void initEnemies(void) {
	enemyTexture = loadTexture("resources/playerSquare.png");
	laserPointer = loadTexture("resources/laserPointerLong.png");
    SDL_SetTextureColorMod(laserPointer, 255, 0, 0);
    SDL_SetTextureAlphaMod(laserPointer, 30);
}


void spawnSniper(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;
    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;

    e->reload = FPS*3;
    e->weapon = SNIPER;
    e->texture = enemyTexture;
    e->tick = tickSniper;
    e->health = 7;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 255;
    e->color.g = 255;
    e->color.b = 0;
    e->color.a = 255;
    e->die = die;
}


void spawnShooter(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;


    e->weapon = SHOOTER;
    e->texture = enemyTexture;
    e->speed = MIN(3 + (stage.wave * 0.1), 7); //wave difficulty modificator
    e->tick = tickShooter;
    e->health = 5;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 250;
    e->color.g = 20;
    e->color.b = 60;
    e->color.a = 255;
    e->die = die;
}

void spawnCrossShooter(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;

    e->weapon = CROSS_SHOOTER;
    e->texture = enemyTexture;
    e->speed = MIN(3 + (stage.wave * 0.1), 7); //wave difficulty modificator
    e->tick = tickCrossShooter;
    e->health = 5;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 174;
    e->color.g = 237;
    e->color.b = 64;
    e->color.a = 255;
    e->die = die;
}
void spawnLineShooter(int x, int y) {
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->x = x;
    e->y = y;

    e->reload = FPS;
    e->weapon = LINE_SHOOTER;
    if (MIN(e->y, SCREEN_HEIGHT - e->y) < 50) e->dy = 1;
    else e->dx = 1;
    e->texture = enemyTexture;
    e->speed = MIN(3 + (stage.wave * 0.1), 7); //wave difficulty modificator
    e->tick = tickLineShooter;
    e->health = 5;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 184;
    e->color.g = 48;
    e->color.b = 200;
    e->color.a = 255;
    e->die = die;
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

    e->texture = enemyTexture;
    e->speed = MIN(6 + (stage.wave * 0.5), 9);
    e->tick = tickRunner;
    e->health = 3;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 125;
    e->color.g = 62;
    e->color.b = 173;
    e->color.a = 255;
    e->die = die;
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
    e->texture = enemyTexture;
    e->speed = 4;
    e->reload = FPS * 2;
    e->health = 4;
    e->tick = tickRammer;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 100;
    e->color.g = 100;
    e->color.b = 100;
    e->color.a = 255;
    e->die = die;
    printf("spawned rammer\n");
}

//TODO-------TICKS------
static void tickSniper(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        blitRotated(laserPointer, self->x, self->y, self->angle - 90);
        if (self->reload <=0 ) {
            fireEnemyBullet();
            self->reload = FPS * 3;
        }
    }
}

static void tickRammer(void) {
    if (player != NULL) {
        if (self->weapon == 1) {
            if (self->speed >= 6 && (self->x - self->w <= 0 || self->x + self->w >= SCREEN_WIDTH || self->y - self->h <= 0 || self->y + self->h >= SCREEN_HEIGHT)) {
                self->speed = 2;
                self->weapon = 0;
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
                self->weapon = 1;
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

static void tickShooter(void) {
	if (player != NULL) {
		self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);

		if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_HEIGHT / 2) {
			fireEnemyBullet();
			self->reload = 12;
		}
	}
}

static void tickCrossShooter(void) { //kinda shit
    if (player != NULL) {
        if (SDL_GetTicks() % (FPS * 3)== 0 || (self->dx == 1 && SCREEN_WIDTH - self->x < 100)
        || (self->dx == -1 && self->x < 100) || (self->dy == 1 && SCREEN_HEIGHT - self->y < 100)
                                                              || (self->dy == -1 && self->y < 100)) {
            int dir = rand() % 4;
            self->angle = 90 * dir;
            switch(dir) {
                case 0:
                    self->dx = 0;
                    self->dy = -1;
                    break;
                case 1:
                    self->dx = 1;
                    self->dy = 0;
                    break;
                case 2:
                    self->dx = 0;
                    self->dy = 1;
                    break;
                default:
                    self->dx = -1;
                    self->dy = 0;
                    break;
            }
        }

        if (self->reload <= 0) {
            fireEnemyBullet();
            self->reload = FPS;
        }
    }
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
            fireEnemyBullet();
            self->reload = FPS;
        }
    }
}

static void die(void) {
	stage.score += 10; //TODO: score scaling with wave?
	stage.waveEnemies--;
}
