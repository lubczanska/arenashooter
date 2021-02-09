#include "bossClasses.h"

Entity *boss;

static void bossShooterTick(void);

void spawnBossShooter(void) {
    boss = malloc(sizeof(Entity));
    memset(boss, 0, sizeof(Entity));
    stage.entityTail->next = boss;
    stage.entityTail = boss;

    boss->health = 30 + (stage.wave % 5) * 5;
    boss->tick = bossShooterTick;
    boss->die = bossDie;
    boss->speed = 5;
    boss->side = SIDE_BOSS;
    boss->x = SCREEN_WIDTH / 2;
    boss->y = SCREEN_HEIGHT / 2;
    boss->texture = bossTexture[B_SHOOTER];
    SDL_QueryTexture(boss->texture, NULL, NULL, &boss->w, &boss->h);
    boss->color.r = 255;
    boss->color.g = 20;
    boss->color.b = 60;
    boss->color.a = 255;
}

static void bossShooterTick(void) {
    if (player != NULL) {
        boss->angle = getAngle(boss->x, boss->y, player->x, player->y);
        getSlope(player->x, player->y, boss->x, boss->y, &boss->dx, &boss->dy);
        if (boss->reload <= 0) {
            shooterShot();
            boss->reload = 6;
        }
    }
}
