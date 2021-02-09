#include "common.h"

extern void addPowerup(int x, int y);
extern void addPowerupBoss(void);
extern void addPlayer(void);
extern void blit(SDL_Texture *texture, int x, int y, int center);
extern void doBullets(void);
extern void doEntities(void);
extern void doEffects(void);
extern void doPlayer(void);
extern void drawBullets(void);
extern void drawEntities(void);
extern void drawEffects(void);
extern void drawText(int x, int y, int r, int g, int b, int center, char *format, ...);
extern int getDistance(int x1, int y1, int x2, int y2);
extern SDL_Texture *loadTexture(char *filename);
static SDL_Texture *playerHBFullTexture;
static SDL_Texture *playerHBEmptyTexture;
static void initPlayerHealthBar(void);

extern App app;
extern Entity *player;
extern Stage stage;
extern int highscore;

static void logic(void);
static void draw(void);
static void drawStats(void);
static void doWave(void);
static void spawnEnemy(void);
static void doPause(void);
static void drawPause(void);
static void resetStage(void);
static void drawGameOver(void);
extern void initTitle(void);

extern void drawBossBar(void);

extern void spawnShooter(int x, int y);
extern void spawnCrossShooter(int x, int y);
extern void spawnLineShooter(int x, int y);
extern void spawnMultiShooter(int x, int y);
extern void spawnSlowMultiShooter(int x, int y);
extern void spawnStarShooter(int x, int y);
extern void spawnRunner(int x, int y);
extern void spawnRammer(int x, int y);
extern void spawnSniper(int x, int y);
extern void spawnSlug(int x, int y);

extern void spawnBoss(void);

static SDL_Texture *cursorTexture;
static int enemySpawnTimer;
static int playerDeathTimer;

void initStage(void) {
	app.delegate.logic = logic;
	app.delegate.draw = draw;

    cursorTexture = loadTexture("resources/cursor2.png");
    resetStage();
    addPlayer();
    initPlayerHealthBar();
    stage.waveState = NEW;
    stage.wave = 0;
	enemySpawnTimer = 0;
    playerDeathTimer = FPS * 4;
}

static void resetStage(void) {
    Entity *e;
    Effect *f;
    while (stage.entityHead.next) {
        e = stage.entityHead.next;
        stage.entityHead.next = e->next;
        free(e);
    }
    while (stage.bulletHead.next) {
        e = stage.bulletHead.next;
        stage.bulletHead.next = e->next;
        free(e);
    }
    while (stage.effectHead.next) {
        f = stage.effectHead.next;
        stage.effectHead.next = f->next;
        free(f);
    }
    memset(&stage, 0, sizeof(Stage));
    stage.entityTail = &stage.entityHead;
    stage.bulletTail = &stage.bulletHead;
    stage.effectTail = &stage.effectHead;
}

static void logic(void) {
    if (stage.pause) doPause();
    else {
        doPlayer();
        doEntities();
        doBullets();
        doEffects();
        doWave();
    }
    if (player == NULL) {
        highscore = MAX(stage.score, highscore);
        if (app.keyboard[SDL_SCANCODE_ESCAPE]) exit(0);
        if (--playerDeathTimer <= 0) initTitle();
    }
}

static void doPause(void) {
    if (app.keyboard[SDL_SCANCODE_SPACE]) {
        SDL_Delay(200);
        stage.pause = 0;
    }
    if (app.keyboard[SDL_SCANCODE_ESCAPE]) exit(0);
}

static void doWave(void) {
    if (stage.waveEnemies == 0 && stage.waveState == NORMAL) { //new wave
        addPowerup(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4);
        stage.waveState = END;
    }
    else if (stage.waveEnemies == 0 && stage.waveState == BOSS_END) {
        addPowerupBoss();
        stage.waveState = END;
    }
    else if (stage.waveState == NEW) {
        Entity *e;
        for (e = stage.entityHead.next; e != NULL; e = e->next) {
            if (e->side == SIDE_NEUTRAL) e->health = 0;
        }
        stage.waveState = NEW_BEGIN;
    }
    else if (stage.waveState == NEW_BEGIN) {

        if (++stage.wave % 3 == 0) {
            stage.waveEnemies = 0;
            spawnBoss();
            stage.waveState = BOSS;
        }
        else {
            stage.waveState = NORMAL;
            stage.waveEnemies = 10;
            stage.waveLeftToSpawn = stage.waveEnemies;
        }
    }
    if (stage.waveLeftToSpawn > 0) {
        spawnEnemy();
    }
}


static void spawnEnemy(void) {
	int x, y;
	if (player != NULL && --enemySpawnTimer <= 0) {
	    stage.waveLeftToSpawn--;
        switch (rand() % 4) { // enemy spawn position
            case 0:
                x = -100;
                y = rand() % SCREEN_HEIGHT;
                break;

            case 1:
                x = SCREEN_WIDTH + 100;
                y = rand() % SCREEN_HEIGHT;
                break;

            case 2:
                x = rand() % SCREEN_WIDTH;
                y = -100;
                break;

            case 3:
                x = rand() % SCREEN_WIDTH;
                y = SCREEN_HEIGHT + 100;
                break;
        }
        switch (rand() % 10) {
            case 0:
                spawnShooter(x, y);
                break;
            case 1:
                spawnSniper(x, y);
                break;
            case 2:
                spawnLineShooter(x, y);
                break;
            case 3:
                spawnRammer(x, y);
                break;
            case 4:
                spawnMultiShooter(x, y);
                break;
            case 5:
                spawnStarShooter(x, y);
                break;
            case 6:
                spawnCrossShooter(x, y);
                break;
            case 7:
                spawnSlowMultiShooter(x, y);
                break;
            case 8:
                spawnSlug(x, y);
                break;
            default:
                spawnRunner(x, y);
                break;
        }
        enemySpawnTimer = MAX(FPS - stage.wave, 20);
	}
}

static void draw(void) {
    drawStats();
    if (stage.waveState == BOSS) drawBossBar();
    blit(cursorTexture, app.mouse.x, app.mouse.y, 1);
	drawEntities();
	drawEffects();
	drawBullets();
    if (stage.pause) drawPause();
    if (playerDeathTimer <= FPS * 3) drawGameOver();
}

static void initPlayerHealthBar(void) {
    playerHBFullTexture = loadTexture("resources/phbf.png");
    playerHBEmptyTexture = loadTexture("resources/phbe.png");
    SDL_SetTextureColorMod(playerHBFullTexture, 255, 0, 0);
    SDL_SetTextureColorMod(playerHBEmptyTexture, 0, 0, 0);
}

static void drawPlayerHealthBar(void) {
    int hlth = 0;
    int x = 30;
    if (player != NULL) hlth = player->health;
    for (int i = 0; i < hlth; i++) {
        blit(playerHBFullTexture, x, 30, 1);
        x += PLAYER_BAR_GLYPH;
    }
    for (int i = hlth; i < PLAYER_HEALTH; i++) {
        blit(playerHBEmptyTexture, x, 30, 1);
        x += PLAYER_BAR_GLYPH;
    }

}

static void dimScreen(void) {
    SDL_Rect s;
    s.x = s.y = 0;
    s.w = SCREEN_WIDTH;
    s.h = SCREEN_HEIGHT;
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 150);
    SDL_RenderFillRect(app.renderer, &s);
}
static void drawPause(void) {
    dimScreen();
    drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 100, 255, 255, 255, 1,  "PAUSE");
    drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 200, 255, 255, 255, 1,  "PRESS SPACE TO RESUME");
    drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 250, 255, 255, 255, 1, "PRESS ESC TO QUIT");
}

static void drawGameOver(void) {
    dimScreen();
    drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 255, 255, 255, 1,  "GAME OVER");
}

static void drawStats(void) {
	drawPlayerHealthBar();
	drawText(SCREEN_WIDTH/2, 20, 255, 255, 255, 1, "%d", stage.score);
    drawText(SCREEN_WIDTH - 200, 10, 255, 255, 255, 0,  "WAVE %02d", stage.wave);
}
