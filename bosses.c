#include "bosses.h"

static SDL_Texture *bossHBFullTexture;
static SDL_Texture *bossHBEmptyTexture;
SDL_Texture *bossTexture[6];

static void initBossBar(void);
void bossDie(void);

int bossMaxHealth;
int bossBarX;

void initBosses(void) {
    bossTexture[B_SHOOTER] = loadTexture("resources/shooter.png");
    bossTexture[B_SPAWNER] = loadTexture("resources/playerSquare.png");
    bossTexture[B_SPIN] = loadTexture("resources/hexagon.png");
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
