#include "common.h"

extern void blitRotated(SDL_Texture *texture, int x, int y, float angle);
extern int getDistance(int x1, int y1, int x2, int y2);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);

extern Entity *player;
extern Entity *self;
extern Stage stage;

static void touchOthers(void) {
    Entity *e;
    int distance;

    for (e = stage.entityHead.next; e != NULL; e = e->next) {
        if (e != self) {
            distance = getDistance(self->x, self->y, e->x, e->y);

            if (distance * 2 < e->h + self->h)  {
                if (e->side != SIDE_NEUTRAL && self->side != SIDE_NEUTRAL) {
                    e->x -= self->x - e->x;
                    e->y -= self->y - e->y;
                }
                self->touch(e);
            }
        }
    }
}

void doEntities(void) {
	Entity *e, *prev;
	
	prev = &stage.entityHead;
	for (e = stage.entityHead.next; e != NULL; e = e->next) {
		self = e;
		
		if (e->tick) e->tick();
		e->x += e->dx * e->speed;
		e->y += e->dy * e->speed;
		
		if (e->touch) touchOthers();
		e->reload = MAX(e->reload - 1, 0);
		//collisions with borders
		e->x = MIN(MAX(e->x, e->w / 2), SCREEN_WIDTH - e->w / 2);
		e->y = MIN(MAX(e->y, e->h / 2), SCREEN_HEIGHT - e->h / 2);

		if (e->health <= 0) {
			if (e->die) e->die();
			if (e == stage.entityTail) stage.entityTail = prev;
			prev->next = e->next;
			free(e);
			e = prev;
		}
		prev = e;
	}
}

void drawEntities(void) {
    Entity *e;
    for (e = stage.entityHead.next; e != NULL; e = e->next) {
        SDL_SetTextureColorMod(e->texture, e->color.r, e->color.g, e->color.b);
        blitRotated(e->texture, e->x, e->y, e->angle);
    }
}