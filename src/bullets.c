#include "bullets.h"

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
			    if(player != NULL && e->side == SIDE_ENEMY && (player->weapon == fireDefaultGun || player->weapon == fireSlowGun)) {
                   e->x += b->dx; //knockback
                   e->y += b->dy;
                }
			    if(e->side == SIDE_PLAYER) playSound(PLAYER_HIT, CH_PLAYER);
			    else playSound(ENEMY_HIT, CH_ENEMY);
                e->hit = 4; //for flashing white sprite
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
    b->color = shooter->color;
    return b;
}