#include "bossClasses.h"

static void bossSpinTick(void);
static void circleFire(void);
static void starFire(void);
static void multiFire(void);
static int spinDirection;
int attackTimer;

void spawnBossSpin(void) {
    Entity *e;
    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->health = 40 + (stage.wave % 5) * 10;
    e->tick = bossSpinTick;
    e->die = bossDie;
    e->side = SIDE_BOSS;
    e->weapon = circleFire;
    e->x = SCREEN_WIDTH / 2;
    e->y = SCREEN_HEIGHT / 2;
    e->texture = bossTexture[B_SPIN];
    e->reload = 30;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 255;
    e->color.g = 85;
    e->color.b = 33;
    e->color.a = 255;
    attackTimer = SDL_GetTicks();
    spinDirection = 1;
}

static void bossSpinTick(void) {
    if (player != NULL) {

        if (SDL_GetTicks() - attackTimer <= FPS * 40) self->weapon();
        else if (SDL_GetTicks() - attackTimer >= FPS * 50) {
            attackTimer = SDL_GetTicks();
            switch(rand() % 4) {
                case 0:
                    self->weapon = circleFire;
                    spinDirection = 1;
                    break;
                case 1:
                    self->weapon = circleFire;
                    spinDirection = -1;
                    break;
                case 2:
                    self->weapon = starFire;
                    break;
                default:
                    self->weapon = multiFire;
                    break;
            }
        }
    }
}

static void circleFire(void) {
    self->angle = (self->angle + spinDirection) % 360;
    if (self->reload <= 0) {
        Entity *b;
        int c = 5;
        if (stage.wave > 20) c = 6;
        for (int i = 0; i <= c; i++) {
            int ang = self->angle + i * (360 / c);
            b = createBullet(self);
            b->angle = ang;
            b->health = FPS*2;
            angledSlope(SCREEN_WIDTH, SCREEN_HEIGHT/2, b->x, b->y, ang, &b->dx, &b->dy);
            b->dx *= 10;
            b->dy *= 10;
            b->damage = 1;
        }
        self->reload = 6;
    }
}

static void starFire(void) {
    if (self->reload <= 0) {
        Entity *b;
        int c = 10;
        if (stage.wave > 20) c = 12;
        for (int i = 0; i <= c; i++) {
            int ang = 0 + i * (360 / c);
            b = createBullet(self);
            b->angle += ang;
            b->health = FPS * 2;
            angledSlope(0, 0, b->x, b->y, ang, &b->dx, &b->dy);
            b->dx *= 10;
            b->dy *= 10;
            b->damage = 2;
        }
        self->reload = 20;
    }
}

static void multiFire(void) {
    self->angle = getAngle(self->x, self->y, player->x, player->y);
    if (self->reload <= 0) {
        Entity *b;
        int c = 1;
        if (stage.wave >= 15) c = 2;
        for (int i = -c; i <= c; i++) {
            b = createBullet(self);
            b->angle += i * 10;
            b->health = FPS*2;
            angledSlope(player->x, player->y, b->x, b->y, i * 10, &b->dx, &b->dy);
            b->dx *= 10;
            b->dy *= 10;
            b->damage = 3;
        }
        self->reload = 20;
    }
}