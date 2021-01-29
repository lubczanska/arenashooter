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

//spawning enemies
static void spawnRunner(void);
static void spawnShooter(void);
static void spawnCrossShooter(void);
static void spawnLineShooter(void);

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

	switch (rand() % 5) {
		case SHOOTER: //shooting slow guy
		    e->weapon = SHOOTER;
            e->texture = enemyTexture;
            e->speed = MIN(3 + (stage.wave * 0.1), 7); //wave difficulty modificator
            e->tick = spawnShooter;
            e->health = 5;
            SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
            e->color.r = 250;
            e->color.g = 20;
            e->color.b = 60;
            e->color.a = 255;
			break;

        case CROSS_SHOOTER: //cross shooting guy
            e->weapon = CROSS_SHOOTER;
            e->texture = enemyTexture;
            e->speed = MIN(3 + (stage.wave * 0.1), 7); //wave difficulty modificator
            e->tick = spawnCrossShooter;
            e->health = 5;
            SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
            e->color.r = 174;
            e->color.g = 237;
            e->color.b = 64;
            e->color.a = 255;
            break;

        case LINE_SHOOTER: //line shooting guy
            e->weapon = LINE_SHOOTER;
            if (MIN(e->y, SCREEN_HEIGHT - e->y) < 50) e->dy = 1;
            else e->dx = 1;
            e->texture = enemyTexture;
            e->speed = MIN(3 + (stage.wave * 0.1), 7); //wave difficulty modificator
            e->tick = spawnLineShooter;
            e->health = 5;
            SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
            e->color.r = 184;
            e->color.g = 48;
            e->color.b = 200;
            e->color.a = 255;
            break;

		default: //melee guy
            e->texture = enemyTexture;
            e->speed = MIN(6 + (stage.wave * 0.5), 9);
            e->tick = spawnRunner;
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

static void spawnRunner(void) {
    if (player != NULL) {
        self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);
    }
}

static void spawnShooter(void) {
	if (player != NULL) {
		self->angle = getAngle(self->x, self->y, player->x, player->y);
        getSlope(player->x, player->y, self->x, self->y, &self->dx, &self->dy);

		if (self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) < SCREEN_HEIGHT / 2) {
			fireEnemyBullet();
			self->reload = 12;
		}
	}
}

static void spawnCrossShooter(void) { //kinda shit
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

static void spawnLineShooter(void) {
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
