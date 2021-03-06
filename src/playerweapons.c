#include "playerweapons.h"
static int overheat;
static int overheatTimer;

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
    if (SDL_GetTicks() - overheatTimer >= 200) overheat -= MIN((SDL_GetTicks() - overheatTimer) / 100, overheat);
    overheatTimer = SDL_GetTicks();
    if (++overheat >= (20 + (stage.wave/3))) {
        player->reload = FPS;
        overheat = 0;
    }
    else {
        Entity *b;
        b = createBullet(player);
        getSlope(app.mouse.x, app.mouse.y, b->x, b->y, &b->dx, &b->dy);
        b->dx *= 18;
        b->dy *= 18;
        b->damage += player->damage;
        player->reload = 6 - player->atkSpeed;
        b->health = FPS;
    }
}


void fireTripleGun(void) {
    if (SDL_GetTicks() - overheatTimer >= 200) overheat -= MIN((SDL_GetTicks() - overheatTimer) / 100, overheat);
    overheatTimer = SDL_GetTicks();
    if (++overheat >= (20 + (stage.wave/3))) {
        player->reload = FPS;
        overheat = 0;
    }
    else {
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
        player->reload = PLAYER_RELOAD - player->atkSpeed;
    }
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
