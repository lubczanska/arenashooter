#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
static void bossShooterTick(void);
extern SDL_Texture *loadTexture(char *filename);
static SDL_Texture *bossTexture;

extern void bossDie(void);
extern void shooterShot(void);
extern App app;
extern Entity *player;
extern Stage stage;
Entity *boss;

void spawnBossShooter(void) {
    boss = malloc(sizeof(Entity));
    memset(boss, 0, sizeof(Entity));
    stage.entityTail->next = boss;
    stage.entityTail = boss;

    bossTexture = loadTexture("resources/shooter.png");
    boss->health = 30;
    boss->tick = bossShooterTick;
    boss->die = bossDie;
    boss->speed = 5;
    boss->side = SIDE_BOSS;
    boss->x = SCREEN_WIDTH / 2;
    boss->y = SCREEN_HEIGHT / 2;
    boss->texture = bossTexture;
    SDL_QueryTexture(boss->texture, NULL, NULL, &boss->w, &boss->h);
    boss->color.r = 255;
    boss->color.g = 255;
    boss->color.b = 255;
    boss->color.a = 255;
}

static void bossShooterTick(void) {
    if (player != NULL) {
        boss->angle = getAngle(boss->x, boss->y, player->x, player->y);
        getSlope(player->x, player->y, boss->x, boss->y, &boss->dx, &boss->dy);
        if (boss->reload <= 0) {
            shooterShot();
            boss->reload = 8;
        }
    }
}
