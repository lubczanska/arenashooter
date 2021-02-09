#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void spawnShooter(int x, int y);
extern void spawnRunner(int x, int y);
extern SDL_Texture *loadTexture(char *filename);
extern SDL_Texture *bossTexture[6];
extern void angledSlope(int x1, int y1, int x2, int y2, float angle, float *dx, float *dy);
extern void bossDie(void);
extern Entity *createBullet(Entity *shooter);

extern App app;
extern Entity *player;
extern Stage stage;
Entity *boss;
int attackTimer;

static void bossSpinTick(void);
static void circleFire(void);
static void starFire(void);
static void multiFire(void);
static int spinDirection;

void spawnBossSpin(void) {
    boss = malloc(sizeof(Entity));
    memset(boss, 0, sizeof(Entity));
    stage.entityTail->next = boss;
    stage.entityTail = boss;

    boss->health = 40;
    boss->tick = bossSpinTick;
    boss->die = bossDie;
    boss->side = SIDE_BOSS;
    boss->weapon = circleFire;
    boss->x = SCREEN_WIDTH / 2;
    boss->y = SCREEN_HEIGHT / 2;
    boss->texture = bossTexture[B_SPIN];
    boss->reload = 30;
    SDL_QueryTexture(boss->texture, NULL, NULL, &boss->w, &boss->h);
    boss->color.r = 255;
    boss->color.g = 85;
    boss->color.b = 33;
    boss->color.a = 255;
    attackTimer = SDL_GetTicks();
    spinDirection = 1;
}

static void bossSpinTick(void) {
    if (player != NULL) {

        if (SDL_GetTicks() - attackTimer <= FPS * 40) boss->weapon();
        else if (SDL_GetTicks() - attackTimer >= FPS * 50) {
            attackTimer = SDL_GetTicks();
            switch(rand() % 4) {
                case 0:
                    boss->weapon = circleFire;
                    spinDirection = 1;
                    break;
                case 1:
                    boss->weapon = circleFire;
                    spinDirection = -1;
                    break;
                case 2:
                   boss->weapon = starFire;
                    break;
                default:
                    boss->weapon = multiFire;
                    break;
            }
        }
    }
}

static void circleFire(void) {
    boss->angle = (boss->angle + spinDirection) % 360;
    if (boss->reload <= 0) {
        Entity *b;
        int c = 5;
        if (stage.wave > 20) c = 6;
        for (int i = 0; i <= c; i++) {
            int ang = boss->angle + i * (360 / c);
            b = createBullet(boss);
            b->angle = ang;
            b->health = FPS*2;
            angledSlope(SCREEN_WIDTH, SCREEN_HEIGHT/2, b->x, b->y, ang, &b->dx, &b->dy);
            b->dx *= 10;
            b->dy *= 10;
            b->damage = 1;
        }
        boss->reload = 6;
    }
}

static void starFire(void) {
    if (boss->reload <= 0) {
        Entity *b;
        int c = 10;
        if (stage.wave > 20) c = 12;
        for (int i = 0; i <= c; i++) {
            int ang = 0 + i * (360 / c);
            b = createBullet(boss);
            b->angle += ang;
            b->health = FPS * 2;
            angledSlope(0, 0, b->x, b->y, ang, &b->dx, &b->dy);
            b->dx *= 10;
            b->dy *= 10;
            b->damage = 2;
        }
        boss->reload = 20;
    }
}

static void multiFire(void) {
    boss->angle = getAngle(boss->x, boss->y, player->x, player->y);
    if (boss->reload <= 0) {
        Entity *b;
        int c = 1;
        if (stage.wave >= 15) c = 2;
        for (int i = -c; i <= c; i++) {
            b = createBullet(boss);
            b->angle += i * 10;
            b->health = FPS*2;
            angledSlope(player->x, player->y, b->x, b->y, i * 10, &b->dx, &b->dy);
            b->dx *= 10;
            b->dy *= 10;
            b->damage = 3;
        }
        boss->reload = 20;
    }
}