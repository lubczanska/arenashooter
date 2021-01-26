#include "common.h"

extern void addPowerup(int x, int y);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern int getDistance(int x1, int y1, int x2, int y2);
extern SDL_Texture *loadTexture(char *filename);

extern Entity *player;
extern Entity *self;
extern Stage stage;

static void enemy1(void);
static void enemy2(void);
static void die(void);

static SDL_Texture *enemyTexture;

void initEnemies(void) {
	enemyTexture = loadTexture("resources/playerSquare.png");
}

void addEnemy(int x, int y) {
	Entity *e;
	
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	
	e->side = SIDE_ENEMY;
	e->x = x;
	e->y = y;

	switch (rand() % 2) {
		case 0: //shooting slow guy
            e->texture = enemyTexture;
            e->speed = MIN(3 + (stage.wave * 0.1), 7);
            e->atkSpeed = MAX(30 - (stage.wave * 0.4), 12);
            e->range = 3;
            e->tick = enemy1;
            e->health = 5;
            SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
            e->color.r = 250;
            e->color.g = 20;
            e->color.b = 60;
            e->color.a = 255;
			break;

		default: //melee guy
            e->texture = enemyTexture;
            e->speed = MIN(2 + (stage.wave * 0.1), 4);
            e->tick = enemy2;
            e->health = 3;
            SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
            e->color.r = 125;
            e->color.g = 62;
            e->color.b = 173;
            e->color.a = 255;
			break;
	}
	

	e->die = die;
}

static void enemy1(void) {
	if (player != NULL) {
		self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
		self->reload = MAX(self->reload - 1, 0);
		if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_HEIGHT / 2) {
			fireEnemyBullet();
			self->reload = self->atkSpeed;
		}
	}
}

static void enemy2(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
    }
}

static void die(void) {
	stage.score += 10;
	stage.waveEnemies--;
}
