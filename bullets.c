#include "common.h"

extern void blitRotated(SDL_Texture *texture, int x, int y, float angle);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern float getAngle(int x1, int y1, int x2, int y2);
extern int getDistance(int x1, int y1, int x2, int y2);
extern SDL_Texture *loadTexture(char *filename);

//player weapons
extern void fireDefaultGun(void);
extern void fireFastGun(void);
extern void fireSlowGun(void);
extern void fireTripleShot(void);
extern void fireQuadShot(void);
//enemy weapons
extern void shooterShot(void);
extern void crossShooterShot(void);
extern void lineShooterShot(void);
extern void sniperShot(void);

extern void playSound(int id, int channel);

extern App app;
extern Entity *player;
extern Entity *self;
extern Stage stage;

Entity *createBullet(Entity *shooter);
static void bulletHitEntity(Entity *b);
static SDL_Texture *bulletTexture;

void initBullets(void) {
	bulletTexture = loadTexture("resources/bulletSquare.png");
}

void doBullets(void) {
	Entity *b, *prev;
	
	prev = &stage.bulletHead;
	for (b = stage.bulletHead.next; b != NULL; b = b->next) {
		b->x += b->dx;
		b->y += b->dy;
		
		bulletHitEntity(b);
		
		if (--b->health <= 0) {
			if (b == stage.bulletTail) stage.bulletTail = prev;
			prev->next = b->next;
			free(b);
			b = prev;
		}
		prev = b;
	}
}

static void bulletHitEntity(Entity *b) {
	Entity *e;
	int distance;

	for (e = stage.entityHead.next; e != NULL; e = e->next) {
		if (e->side != SIDE_NEUTRAL && e->side != b->side) {
			distance = getDistance(e->x, e->y, b->x, b->y);
			if (distance * 2 < e->h + b->h) {
			    if(e->side == SIDE_ENEMY) {
                    e->x += b->dx * 2; //knockback
                    e->y += b->dy * 2;
                }
			    if(e->side == SIDE_PLAYER) playSound(PLAYER_HIT, CH_PLAYER);
				b->health = 0;
				e->health -= b->damage;
				return;
			}
		}
	}
}

void drawBullets(void) {
	Entity *b;
	for (b = stage.bulletHead.next; b != NULL; b = b->next) {
		SDL_SetTextureColorMod(b->texture, b->color.r, b->color.g, b->color.b);
        blitRotated(b->texture, b->x, b->y, b->angle);
	}
}

void firePlayerBullet(void) {

    switch(player->weapon) {
        case(FAST_GUN):
            fireFastGun();
            break;
        case(SLOW_GUN):
            fireSlowGun();
            break;
        case(TRIPLE_SHOT):
            fireTripleShot();
            break;
        case(QUAD_SHOT):
            fireQuadShot();
            break;
        default:
            fireDefaultGun();
            break;
    }
    playSound(PLAYER_FIRE, CH_PLAYER);

}

void fireEnemyBullet(void) {
    switch(self->weapon) {
        case(SHOOTER):
            shooterShot();
            break;
        case(CROSS_SHOOTER):
            crossShooterShot();
            break;
        case(LINE_SHOOTER):
            lineShooterShot();
            break;
        case(SNIPER):
            sniperShot();
            break;
        default:
            break;
    }
}

Entity *createBullet(Entity *shooter) {
    Entity *b;

    b = malloc(sizeof(Entity));
    memset(b, 0, sizeof(Entity));
    stage.bulletTail->next = b;
    stage.bulletTail = b;

    b->x = shooter->x;
    b->y = shooter->y;
    b->texture = bulletTexture; //default
    b->health = FPS * 2; //default
    b->damage = 1; //default
    b->angle = shooter->angle;
    b->side = shooter->side;
    SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);
    b->color.r = shooter->color.r; //TODO: remove when there are proper sprites
    b->color.g = shooter->color.g;
    b->color.b = shooter->color.b;
    b->color.a = 255;

    return b;
}