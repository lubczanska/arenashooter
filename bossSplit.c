#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void addEnemyDeathEffect(Entity *e);
static void bossSplitTick(void);
static void bossSplitDie0(void);
static void bossSplitDie1(void);
static void bossSplitDie2(void);
extern SDL_Texture *loadTexture(char *filename);
static SDL_Texture *bossTexture;

extern void bossDie(void);
extern App app;
extern Entity *player;
extern Stage stage;
extern Entity *self;
extern int bossMaxHealth;
extern int bossBarX;

void spawnBossSplit(void) {
    Entity* e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    bossTexture = loadTexture("resources/bossSplit.png");
    e->health = 30;
    e->tick = bossSplitTick;
    e->die = bossSplitDie0;
    e->side = SIDE_BOSS;
    e->speed = 10;
    e->x = SCREEN_WIDTH / 2;
    e->y = SCREEN_HEIGHT / 2;
    e->dx = (1 + (rand() % 99)) * 0.01;
    e->dy = (1 + (rand() % 99)) * 0.01;
    e->texture = bossTexture;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->color.r = 255;
    e->color.g = 255;
    e->color.b = 255;
    e->color.a = 255;
    bossMaxHealth = e->health;
    bossBarX = (SCREEN_WIDTH - (bossMaxHealth * BOSS_BAR_GLYPH)) / 2;
}

static void bossSplitTick(void) {
    if (player != NULL) {
        if ((self->x - self->w) <=0 || (self->x + self->w) >= SCREEN_WIDTH) self->dx *= -1;
        if ((self->y - self->h)<=0 || (self->y + self->h) >= SCREEN_HEIGHT) self->dy *= -1;
    }
}

static void bossSplitDie0(void) {
    addEnemyDeathEffect(self);
    int cap = MIN(2 + (stage.wave / 5), 7);
    bossMaxHealth -= 30;
    for (int i = 0; i < cap; i++) {
        Entity *e;

        e = malloc(sizeof(Entity));
        memset(e, 0, sizeof(Entity));
        stage.entityTail->next = e;
        stage.entityTail = e;

        bossTexture = loadTexture("resources/bossSplit2.png");
        e->health = 15;
        e->tick = bossSplitTick;
        e->die = bossSplitDie1;
        e->side = SIDE_BOSS;
        e->speed = 12;
        e->x = self->x;
        e->y = self->y;
        e->dx = (1 + ((rand() + i*i) % 99)) * 0.01;
        e->dy = (1 + ((rand() + i*i) % 99)) * 0.01;
        e->texture = bossTexture;
        SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
        e->color.r = 0;
        e->color.g = 255;
        e->color.b = 255;
        e->color.a = 255;
        bossMaxHealth += e->health;
    }
    bossBarX = (SCREEN_WIDTH - (bossMaxHealth * BOSS_BAR_GLYPH)) / 2;
}
static void bossSplitDie1(void) {
    addEnemyDeathEffect(self);
    int cap = MIN(2 + (stage.wave / 5), 7);
    bossMaxHealth -= 15;
    for (int i = 0; i < cap; i++) {
        Entity *e;

        e = malloc(sizeof(Entity));
        memset(e, 0, sizeof(Entity));
        stage.entityTail->next = e;
        stage.entityTail = e;

        bossTexture = loadTexture("resources/bossSplit3.png");
        e->health = 5;
        e->tick = bossSplitTick;
        e->die = bossSplitDie2;
        e->side = SIDE_BOSS;
        e->speed = 15;
        e->x = self->x;
        e->y = self->y;
        e->dx = (1 + ((rand() + i*i) % 99)) * 0.01;
        e->dy = (1 + ((rand() + i*i) % 99)) * 0.01;
        e->texture = bossTexture;
        SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
        e->color.r = 255;
        e->color.g = 0;
        e->color.b = 255;
        e->color.a = 255;
        bossMaxHealth += e->health;
    }
    bossBarX = (SCREEN_WIDTH - (bossMaxHealth * BOSS_BAR_GLYPH)) / 2;
}
static void bossSplitDie2(void) {
    addEnemyDeathEffect(self);
    Entity *e;
    for (e = stage.entityHead.next; e != NULL; e = e->next) {
        if (e->side >= SIDE_ENEMY && e != self) return;
    }
    stage.score += 200;
    stage.waveState = BOSS_END;
    stage.waveEnemies = 0;
}