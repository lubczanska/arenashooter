#include "common.h"

extern void blitRotated(SDL_Texture *texture, int x, int y, float angle);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern float getAngle(int x1, int y1, int x2, int y2);
extern int getDistance(int x1, int y1, int x2, int y2);
extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Entity *player;
extern Entity *self;
extern Stage stage;

static void bulletHitEntity(Entity *b);
static SDL_Texture *bulletTexture;

void initBullets(void) {
	bulletTexture = loadTexture("resources/bulletSquare.png");
}

void doBullets(void) {
	Entity *b, *prev;
	
	prev = &stage.bulletHead;
	for (b = stage.bulletHead.next ; b != NULL ; b = b->next) {
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
                    e->x += b->dx * 3; //knockback
                    e->y += b->dy * 3;
                }
				b->health = 0;
				e->health--;
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
    Entity *b;

    b = malloc(sizeof(Entity));
    memset(b, 0, sizeof(Entity));
    stage.bulletTail->next = b;
    stage.bulletTail = b;

    b->x = player->x;
    b->y = player->y;
    b->texture = bulletTexture;
    b->health = FPS * player->range;
    b->angle = player->angle;
    b->side = SIDE_PLAYER;
    SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);
    b->color.r = player->color.r;
    b->color.g = player->color.g;
    b->color.b = player->color.b;
    b->color.a = 255;

    getSlope(app.mouse.x, app.mouse.y, b->x, b->y, &b->dx, &b->dy);

    b->dx *= 16;
    b->dy *= 16;
    player->reload = player->atkSpeed;
}

void fireEnemyBullet(void) {
	Entity *b;
	
	b = malloc(sizeof(Entity));
	memset(b, 0, sizeof(Entity));
	stage.bulletTail->next = b;
	stage.bulletTail = b;
	
	b->x = self->x;
	b->y = self->y;
	b->texture = bulletTexture;
	b->health = FPS * self->range;
	b->angle = getAngle(self->x, self->y, player->x, player->y);
	b->side = SIDE_ENEMY;
	SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);
    b->color.r = self->color.r;
    b->color.g = self->color.g;
    b->color.b = self->color.b;
    b->color.a = 255;

    getSlope(player->x, player->y, b->x, b->y, &b->dx, &b->dy);
	
	b->dx *= MIN(12 + (stage.wave * 0.3), 16);
	b->dy *= MIN(12 + (stage.wave * 0.3), 16);
}
