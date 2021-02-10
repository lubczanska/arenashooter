#include "enemies.h"

void enemyDie(void);

SDL_Texture *enemyTexture[10];

void initEnemies(void) {
	enemyTexture[SHOOTER] = loadTexture("resources/shooter.png");
    enemyTexture[LINE_SHOOTER] = loadTexture("resources/playerSquare.png");
    enemyTexture[CROSS_SHOOTER] = loadTexture("resources/hexagon.png");
    enemyTexture[MULTI_SHOOTER] = loadTexture("resources/hexagon.png");
    enemyTexture[SLOW_MULTI_SHOOTER] = loadTexture("resources/pentagon.png");
    enemyTexture[STAR_SHOOTER] = loadTexture("resources/8star.png");
    enemyTexture[SNIPER] = loadTexture("resources/triangle.png");
    enemyTexture[RUNNER] = loadTexture("resources/playerSquare.png");
    enemyTexture[RAMMER] = loadTexture("resources/playerSquare.png");
    enemyTexture[SLUG] = loadTexture("resources/playerSquare.png");
}

void enemyDie(void) {
    addEnemyDeathEffect(self);
	stage.score += 10;
	stage.waveEnemies--;
}
