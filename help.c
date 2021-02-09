#include "common.h"

extern void drawText(int x, int y, int r, int g, int b, int center, char *format, ...);
extern void initTitle(void);
extern void blit(SDL_Texture *texture, int x, int y, int center);
extern App app;
extern SDL_Texture *powerupTexture;
extern SDL_Texture *powerupWeaponTexture[4];
extern SDL_Texture *enemyTexture[10];
extern SDL_Texture *bossTexture[6];

static void logic(void);
static void draw(void);
static int page;

void initHelp(void) {
    app.delegate.logic = logic;
    app.delegate.draw = draw;
}

static void logic(void) {
    if (app.keyboard[SDL_SCANCODE_BACKSPACE]) initTitle();
    if (app.keyboard[SDL_SCANCODE_ESCAPE]) exit(0);
    if (app.keyboard[SDL_SCANCODE_D]) {
        page = (page + 1) % HELP_PAGES;
        SDL_Delay(300);
    }
    if (app.keyboard[SDL_SCANCODE_A]) {
        page = ((page - 1) % HELP_PAGES + HELP_PAGES) % HELP_PAGES; //XD!
        SDL_Delay(300);
    }
}

static void draw(void) {
    switch (page) {
        case 0:
            drawText(SCREEN_WIDTH/2, 100, 255, 255, 255, 1, "MOVEMENT");
            drawText(SCREEN_WIDTH/2, 400, 255, 255, 255, 1, "WASD - move");
            drawText(SCREEN_WIDTH/2, 450, 255, 255, 255, 1, "LMB - shoot");
            drawText(SCREEN_WIDTH/2, 500, 255, 255, 255, 1, "SPACE - pause");
            break;
        case 1:
            drawText(SCREEN_WIDTH/2, 100, 255, 255, 255, 1, "ITEMS");

            SDL_SetTextureColorMod(powerupTexture, 250, 10, 45);
            blit(powerupTexture, 200, 300, 1);
            drawText(300, 300, 255, 255, 255, 0, "HP++");

            SDL_SetTextureColorMod(powerupTexture, 128, 227, 42);
            blit(powerupTexture, 200, 400, 1);
            drawText(300, 400, 255, 255, 255, 0, "SPEED++");

            SDL_SetTextureColorMod(powerupTexture, 245, 187, 30);
            blit(powerupTexture, 200, 500, 1);
            drawText(300, 500, 255, 255, 255, 0, "ATTACK SPEED++");

            SDL_SetTextureColorMod(powerupTexture, 250, 10, 100);
            blit(powerupTexture, 200, 600, 1);
            drawText(300, 600, 255, 255, 255, 0, "MAX HP");

            drawText(200, 750, 255, 255, 255, 0, "picking up an equipped weapon");
            drawText(200, 800, 255, 255, 255, 0, "increases your damage");

            SDL_SetTextureColorMod(powerupWeaponTexture[0], 255, 255, 255);
            blit(powerupWeaponTexture[0], 800, 300, 1);
            drawText(900, 300, 255, 255, 255, 0, "DEFAULT GUN");
            drawText(900, 350, 255, 255, 255, 0, "a gun");

            SDL_SetTextureColorMod(powerupWeaponTexture[1], 255, 255, 255);
            blit(powerupWeaponTexture[1], 800, 450, 1);
            drawText(900, 450, 255, 255, 255, 0, "FAST SHOOTING GUN");
            drawText(900, 500, 255, 255, 255, 0, "doesn't do much. but fast");

            SDL_SetTextureColorMod(powerupWeaponTexture[2], 255, 255, 255);
            blit(powerupWeaponTexture[2], 800, 600, 1);
            drawText(900, 600, 255, 255, 255, 0, "SLOW SHOOTING GUN");
            drawText(900, 650, 255, 255, 255, 0, "high reload, high damage");

            SDL_SetTextureColorMod(powerupWeaponTexture[3], 255, 255, 255);
            blit(powerupWeaponTexture[3], 800, 750, 1);
            drawText(900, 750, 255, 255, 255, 0, "TRIPLE SHOOTING GUN");
            drawText(900, 800, 255, 255, 255, 0, "three shots at once");
            break;

        case 2:
            drawText(SCREEN_WIDTH/2, 100, 255, 255, 255, 1, "BOSSES");

            drawText(SCREEN_WIDTH/2, 150, 255, 255, 255, 1, "will spawn every 5th wave");

            SDL_SetTextureColorMod(bossTexture[B_SHOOTER], 255, 20, 60);
            blit(bossTexture[B_SHOOTER], 200, 350, 1);
            drawText(300, 350, 255, 255, 255, 0, "SHOOTER");
            drawText(300, 400, 255, 255, 255, 0, "like a regular shooter");
            drawText(300, 435, 255, 255, 255, 0, "but better");

            SDL_SetTextureColorMod(bossTexture[B_SPAWNER], 119, 22, 245);
            blit(bossTexture[B_SPAWNER], 200, 600, 1);
            drawText(300, 600, 255, 255, 255, 0, "SPAWNER");
            drawText(300, 650, 255, 255, 255, 0, "spawns little runners or shooters");

            SDL_SetTextureColorMod(bossTexture[B_SPIN], 255, 85, 33);
            blit(bossTexture[B_SPIN], 1000, 350, 1);
            drawText(1100, 350, 255, 255, 255, 0, "SPINNER");
            drawText(1100, 400, 255, 255, 255, 0, "spins and shoots in a star pattern");

            SDL_SetTextureColorMod(bossTexture[B_SPLIT_0], 33, 120, 255);
            blit(bossTexture[B_SPLIT_0], 1000, 600, 1);
            drawText(1100, 600, 255, 255, 255, 0, "SPLIT");
            drawText(1100, 650, 255, 255, 255, 0, "will split into smaller enemies");
            drawText(1100, 685, 255, 255, 255, 0, "when killed");
            break;
        case 3:
            drawText(SCREEN_WIDTH/2, 100, 255, 255, 255, 1, "ENEMIES 1");

            SDL_SetTextureColorMod(enemyTexture[SHOOTER], 255, 20, 60);
            blit(enemyTexture[SHOOTER], 200, 350, 1);
            drawText(300, 350, 255, 255, 255, 0, "SHOOTER");
            drawText(300, 400, 255, 255, 255, 0, "will shoot at you. wow");

            SDL_SetTextureColorMod(enemyTexture[LINE_SHOOTER], 184, 48, 200);
            blit(enemyTexture[LINE_SHOOTER], 200, 600, 1);
            drawText(300, 600, 255, 255, 255, 0, "LINE SHOOTER");
            drawText(300, 650, 255, 255, 255, 0, "moves back and forth and shoots ahead");

            SDL_SetTextureColorMod(enemyTexture[RUNNER], 125, 62, 173);
            blit(enemyTexture[RUNNER], 1000, 350, 1);
            drawText(1100, 350, 255, 255, 255, 0, "RUNNER");
            drawText(1100, 400, 255, 255, 255, 0, "chases you");

            SDL_SetTextureColorMod(enemyTexture[RAMMER], 255, 102, 156);
            blit(enemyTexture[RAMMER], 1000, 600, 1);
            drawText(1100, 600, 255, 255, 255, 0, "MAGNET");
            drawText(1100, 650, 255, 255, 255, 0, "will accelerate towards you");
            drawText(1100, 685, 255, 255, 255, 0, "be careful, he's fast");
            break;
        case 4:
            drawText(SCREEN_WIDTH/2, 100, 255, 255, 255, 1, "ENEMIES 2");

            SDL_SetTextureColorMod(enemyTexture[CROSS_SHOOTER], 119, 22, 245);
            blit(enemyTexture[CROSS_SHOOTER], 200, 350, 1);
            drawText(300, 350, 255, 255, 255, 0, "CROSS SHOOTER");
            drawText(300, 400, 255, 255, 255, 0, "will spin and shoot, but not move");

            SDL_SetTextureColorMod(enemyTexture[MULTI_SHOOTER], 33, 120, 255);
            blit(enemyTexture[MULTI_SHOOTER], 200, 600, 1);
            drawText(300, 600, 255, 255, 255, 0, "MULTI SHOOTER");
            drawText(300, 650, 255, 255, 255, 0, "shoots three bullets. or more");

            SDL_SetTextureColorMod(enemyTexture[SLOW_MULTI_SHOOTER], 255, 85, 33);
            blit(enemyTexture[SLOW_MULTI_SHOOTER], 1000, 350, 1);
            drawText(1100, 350, 255, 255, 255, 0, "MULTI SHOOTER 2");
            drawText(1100, 400, 255, 255, 255, 0, "shoots more bullets");

            SDL_SetTextureColorMod(enemyTexture[STAR_SHOOTER], 78, 23, 232);
            blit(enemyTexture[STAR_SHOOTER], 1000, 600, 1);
            drawText(1100, 600, 255, 255, 255, 0, "STAR SHOOTER");
            drawText(1100, 650, 255, 255, 255, 0, "shoots a small circle of bullets");
            drawText(1100, 685, 255, 255, 255, 0, "around himself");
            break;

        case 5:
            drawText(SCREEN_WIDTH/2, 100, 255, 255, 255, 1, "ENEMIES 3");

            SDL_SetTextureColorMod(enemyTexture[SNIPER], 255, 255, 0);
            blit(enemyTexture[SNIPER], 200, 350, 1);
            drawText(300, 350, 255, 255, 255, 0, "SNIPER");
            drawText(300, 400, 255, 255, 255, 0, "moves a little. then aims and shoots");

            SDL_SetTextureColorMod(enemyTexture[SLUG], 255, 102, 156);
            blit(enemyTexture[SLUG], 1000, 350, 1);
            drawText(1100, 350, 255, 255, 255, 0, "SLUG");
            drawText(1100, 400, 255, 255, 255, 0, "floor is lava!");
            break;
    }
    drawText(100, SCREEN_HEIGHT - 100, 255, 255, 255, 1, "<< A");
    drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100, 255, 255, 255, 1, "BACKSPACE - return to menu");
    drawText(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, 255, 255, 255, 1, "D >>");
}