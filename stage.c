#include "common.h"

extern void addPowerup(int x, int y);
extern void addEnemy(int x, int y);
extern void addPlayer(void);
extern void blit(SDL_Texture *texture, int x, int y, int center);
extern void doBullets(void);
extern void doEntities(void);
extern void doPlayer(void);
extern void drawBullets(void);
extern void drawEntities(void);
extern void drawText(int x, int y, int r, int g, int b, char *format, ...);
extern int getDistance(int x1, int y1, int x2, int y2);
extern SDL_Texture *loadTexture(char *filename);

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
static void resetStage(void);
extern void initTitle(void);

extern void drawBossBar(void);

extern void spawnShooter(int x, int y);
extern void spawnCrossShooter(int x, int y);
extern void spawnLineShooter(int x, int y);
extern void spawnRunner(int x, int y);
extern void spawnRammer(int x, int y);
extern void spawnSniper(int x, int y);

extern void spawnBoss(void);

static SDL_Texture *cursorTexture;
static int enemySpawnTimer;

void initStage(void) {
	app.delegate.logic = logic;
	app.delegate.draw = draw;

    cursorTexture = loadTexture("resources/cursor.png");
    resetStage();
    addPlayer();
    stage.waveState = NEW;
    stage.wave = 0;
	enemySpawnTimer = 0;
}

static void resetStage(void) {
    Entity *e;

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
    memset(&stage, 0, sizeof(Stage));
    stage.entityTail = &stage.entityHead;
    stage.bulletTail = &stage.bulletHead;
}

static void logic(void) {
   // if (stage.pause) doPause();
    //else {
        doPlayer();
        doEntities();
        doBullets();
        doWave();
    //}
    if (player == NULL) {
        highscore = MAX(stage.score, highscore);
        initTitle();
    }
}

static void doPause(void) {
    if (app.keyboard[SDL_SCANCODE_ESCAPE]) stage.pause = (stage.pause++) % 2;
}

static void doWave(void) {
    if (stage.waveEnemies == 0 && (stage.waveState == NORMAL || stage.waveState == BOSS_END)) { //new wave
        addPowerup(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        stage.waveState = END;
    }
    else if (stage.waveState == NEW) {
        if (++stage.wave % 10 == 0) {
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
        switch (rand() % 4) {
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
        switch (rand() % 5) {
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
                printf("spawning rammer\n");
                break;

            default:
                spawnRunner(x, y);
                break;
        }
        enemySpawnTimer = MAX(FPS * 1.5 - stage.wave, 20);
	}
}

static void draw(void) {
	drawEntities();
	drawBullets();
    drawStats();
    if (stage.waveState == BOSS) drawBossBar();
    blit(cursorTexture, app.mouse.x, app.mouse.y, 1);
}

static void drawStats(void) {
	drawText(10, 10, 255, 255, 255, "HEALTH:%d", player != NULL ? player->health : 0);
	drawText(250, 10, 255, 255, 255, "SCORE:%04d", stage.score);
    drawText(510, 10, 255, 255, 255,  "WAVE:%02d", stage.wave);
    drawText(760, 10, 255, 255, 255,  "WEAPON:%02d", player->weapon);
}
