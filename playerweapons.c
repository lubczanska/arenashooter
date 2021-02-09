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
    b->damage = 2 + player->damage;
    b->health = FPS;
    player->reload = PLAYER_RELOAD - player->atkSpeed;
}

void fireFastGun(void) {
    Entity *b;
    b = createBullet(player);
    getSlope(app.mouse.x, app.mouse.y, b->x, b->y, &b->dx, &b->dy);
    b->dx *= 18;
    b->dy *= 18;
    b->damage += player->damage;
    player->reload = 6 - player->atkSpeed;
    b->health = FPS;
}


void fireTripleGun(void) {
    Entity *b;
    for (int i = -1; i <= 1; i++) {
        b = createBullet(player);
        b->angle += i * 10;
        angledSlope(app.mouse.x, app.mouse.y, b->x, b->y, i * 10, &b->dx, &b->dy);
        b->dx *= 16;
        b->dy *= 16;
        b->damage = 2 + player->damage;
        b->health = FPS;
    }
    player->reload = PLAYER_RELOAD - player->atkSpeed;;
}

void fireSlowGun(void) {
    Entity *b;
    b = createBullet(player);
    getSlope(app.mouse.x, app.mouse.y, b->x, b->y, &b->dx, &b->dy);
    b->dx *= 25;
    b->dy *= 25;
    b->damage = 5 + player->damage;
    player->reload = 20 - player->atkSpeed;
}
