#include "enemyClasses.h"

extern App app;

static void tickSniper(void);
void sniperShot(void);
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
    b->dx *= 40;
    b->dy *= 40;
    b->damage = 4;
    //reload controlled by tick function
}