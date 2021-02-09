#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void spawnShooter(int x, int y);
extern void spawnRunner(int x, int y);
extern void addEnemyDeathEffect(Entity *e);
extern SDL_Texture *loadTexture(char *filename);
static SDL_Texture *bossHBFullTexture;
static SDL_Texture *bossHBEmptyTexture;

extern App app;
extern Entity *player;
extern Stage stage;
extern Entity *boss;
int bossMaxHealth;
int bossBarX;

static void initBossBar(void);

void bossDie(void);

extern void spawnBossShooter(void);
extern void spawnBossSpawner(void);
extern void spawnBossSpin(void);
extern void spawnBossSplit(void);

SDL_Texture *bossTexture[6];

void initBosses(void) {
    bossTexture[B_SHOOTER] = loadTexture("resources/playerSquare.png");
    bossTexture[B_SPAWNER] = loadTexture("resources/playerSquare.png");
    bossTexture[B_SPIN] = loadTexture("resources/playerSquare.png");
    bossTexture[B_SPLIT_0] = loadTexture("resources/bossSplit.png");
    bossTexture[B_SPLIT_1] = loadTexture("resources/bossSplit2.png");
    bossTexture[B_SPLIT_2] = loadTexture("resources/bossSplit3.png");
}

void spawnBoss(void) {
    switch(rand() % 4) {
        case 0:
            spawnBossShooter();
            bossMaxHealth = boss->health;
            bossBarX = (SCREEN_WIDTH - (bossMaxHealth * BOSS_BAR_GLYPH)) / 2;
            break;
        case 1:
            spawnBossSplit();
            break;
        case 2:
            spawnBossSpin();
            bossMaxHealth = boss->health;
            bossBarX = (SCREEN_WIDTH - (bossMaxHealth * BOSS_BAR_GLYPH)) / 2;
            break;
        default:
            spawnBossSpawner();
            bossMaxHealth = boss->health;
            bossBarX = (SCREEN_WIDTH - (bossMaxHealth * BOSS_BAR_GLYPH)) / 2;
            break;
    }
    initBossBar();
}

void bossDie(void) {
    addEnemyDeathEffect(boss);
    boss = NULL;
    stage.score += 200;
    stage.waveState = BOSS_END;
    stage.waveEnemies = 0;
    Entity *e;
    for (e = stage.entityHead.next; e != NULL; e = e->next) { //killing boss kills all spawned enemies too
        if (e->side >= SIDE_ENEMY) e-> health = 0;
    }
}

static void initBossBar(void) {
    bossHBFullTexture = loadTexture("resources/bhbf.png");
    bossHBEmptyTexture = loadTexture("resources/bhbe.png");
    SDL_SetTextureColorMod(bossHBFullTexture, 255, 0, 0);
    SDL_SetTextureColorMod(bossHBEmptyTexture, 0, 0, 0);
}

void drawBossBar(void) {
    int x = bossBarX;
    int hlth = 0;
    if (boss == NULL) {
        Entity *e;
        for (e = stage.entityHead.next; e != NULL; e = e->next) {
            if (e->side >= SIDE_ENEMY) hlth += e->health;
        }
    }
    else hlth = boss->health;
    for (int i = 0; i < hlth; i++) {
        blit(bossHBFullTexture, x, 80, 1);
        x += BOSS_BAR_GLYPH;
    }
    for (int i = hlth; i < bossMaxHealth; i++) {
        blit(bossHBEmptyTexture, x, 80, 1);
        x += BOSS_BAR_GLYPH;
    }
}
