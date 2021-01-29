#include "common.h"

extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void angledSlope(int x1, int y1, int x2, int y2, float angle, float *dx, float *dy);
extern int getDistance(int x1, int y1, int x2, int y2);
extern float getAngle(int x1, int y1, int x2, int y2);
extern Entity *createBullet(Entity *shooter);
extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Entity *player;
extern Stage stage;


void fireDefaultGun(void) {
    Entity *b;

    b = createBullet(player);

    getSlope(app.mouse.x, app.mouse.y, b->x, b->y, &b->dx, &b->dy);

    b->dx *= 16;
    b->dy *= 16;
    b->damage = 2;
    player->reload = PLAYER_RELOAD;
}

void fireFastGun(void) {
    Entity *b;

    b = createBullet(player);

    getSlope(app.mouse.x, app.mouse.y, b->x, b->y, &b->dx, &b->dy);

    b->dx *= 18;
    b->dy *= 18;
    player->reload = 6;
}

void fireSlowGun(void) {
    Entity *b;

    b = createBullet(player);

    getSlope(app.mouse.x, app.mouse.y, b->x, b->y, &b->dx, &b->dy);

    b->dx *= 12;
    b->dy *= 12;
    b->damage = 4;
    player->reload = 15;
}

void fireTripleShot(void) {
    Entity *b;
    for (int i = -1; i < 2; i++) {
        b = createBullet(player);
        b->angle += i * 20;
        angledSlope(app.mouse.x, app.mouse.y, b->x, b->y, i * 20, &b->dx, &b->dy);
        b->dx *= 16;
        b->dy *= 16;
        b->damage = 2;
    }
    player->reload = PLAYER_RELOAD;
}

void fireQuadShot(void) {
    Entity *b;
    for (int i = 0; i < 4; i++) {
        b = createBullet(player);
        b->angle += i * 90;
        angledSlope(app.mouse.x, app.mouse.y, b->x, b->y, i * 90, &b->dx, &b->dy);
        b->dx *= 16;
        b->dy *= 16;
        b->damage = 2;
    }
    player->reload = PLAYER_RELOAD;
}

void fireLaserPistol(void) {
    Entity *b;

    b = createBullet(player);

    getSlope(app.mouse.x, app.mouse.y, b->x, b->y, &b->dx, &b->dy);

    b->dx *= 16;
    b->dy *= 16;
    b->damage = 2;
    player->reload = PLAYER_RELOAD;
}