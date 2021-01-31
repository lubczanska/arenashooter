#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern void fireEnemyBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern SDL_Texture *loadTexture(char *filename);
static SDL_Texture *bbfTexture;
static SDL_Texture *bbeTexture;
static SDL_Texture *bossTexture;

extern App app;
extern Entity *player;
extern Stage stage;
Entity *boss;
static int bossMaxHealth;
static int bossBarX;

extern void drawText(int x, int y, int r, int g, int b, char *format, ...);

static void initBossBar(void);
static void bossTick(void);
static void bossDie(void);

void spawnBoss(void) {
    boss = malloc(sizeof(Entity));
    memset(boss, 0, sizeof(Entity));
    stage.entityTail->next = boss;
    stage.entityTail = boss;

    bossTexture = loadTexture("resources/playerSquare.png");
    //roll boss type
    boss->health = bossMaxHealth = 30;
    boss->tick = bossTick;
    boss->die = bossDie;
    boss->side = SIDE_ENEMY;
    boss->weapon = SHOOTER;
    boss->x = SCREEN_WIDTH / 2;
    boss->y = SCREEN_HEIGHT / 2;
    boss->texture = bossTexture;
    SDL_QueryTexture(boss->texture, NULL, NULL, &boss->w, &boss->h);
    boss->color.r = 255;
    boss->color.g = 255;
    boss->color.b = 255;
    boss->color.a = 255;
    bossBarX = (SCREEN_WIDTH - (bossMaxHealth * BOSS_BAR_GLYPH)) / 2;
    initBossBar();
}
//TODO: boss specific spawns and ticks
static void bossTick(void) {
    if (player != NULL) {
        boss->angle = getAngle(boss->x, boss->y, player->x, player->y);
        getSlope(player->x, player->y, boss->x, boss->y, &boss->dx, &boss->dy);
        if (boss->reload <= 0) {
            fireEnemyBullet();
            boss->reload = 12;
        }
    }
}

static void bossDie(void) {
    boss = NULL;
    stage.score += 200;
    stage.waveState = BOSS_END;
    stage.waveEnemies = 0;
    Entity *e;
    for (e = stage.entityHead.next; e != NULL; e = e->next) {
        if (e->side == SIDE_ENEMY) e-> health = 0;
    }
    //add powerups;
}

static void initBossBar(void) {
    bbfTexture = loadTexture("resources/bbf.png");
    bbeTexture = loadTexture("resources/bbe.png");
    SDL_SetTextureColorMod(bbfTexture, 255, 0, 0);
    SDL_SetTextureColorMod(bbeTexture, 0, 0, 0);
}
void drawBossBar(void) {
    //TODO: add textures and edges
    int x = bossBarX;
    for (int i = 0; i < boss->health; i++) {
        blit(bbfTexture, x, 50, 1);
        x += BOSS_BAR_GLYPH;
    }
    for (int i = boss->health; i < bossMaxHealth; i++) {
        blit(bbeTexture, x, 50, 1);
        x += BOSS_BAR_GLYPH;
    }
    drawText(bossBarX, 70, 255, 255, 255,  "BOSS:%02d / %02d", boss->health, bossMaxHealth);
}
