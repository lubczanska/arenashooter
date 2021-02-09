#include "common.h"

extern void drawText(int x, int y, int r, int g, int b, int center, char *format, ...);
extern void initTitle(void);
extern void blit(SDL_Texture *texture, int x, int y, int center);

extern App app;
static void logic(void);
static void draw(void);
static int page;

extern SDL_Texture *powerupTexture;
extern SDL_Texture *powerupWeaponTexture[4];
extern SDL_Texture *enemyTexture[10];
extern SDL_Texture *bossTexture[6];

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
        page = ((page - 1) % HELP_PAGES + 4) % HELP_PAGES; //XD!
        SDL_Delay(300);
    }
}

static void draw(void) {
    switch (page) {
        case 0:
            drawText(SCREEN_WIDTH/2, 100, 255, 255, 255, 1, "ITEMS");

            SDL_SetTextureColorMod(powerupTexture, 255, 0, 0);
            blit(powerupTexture, 200, 300, 1);
            drawText(300, 300, 255, 255, 255, 0, "HP++");

            SDL_SetTextureColorMod(powerupTexture, 0, 255, 255);
            blit(powerupTexture, 200, 400, 1);
            drawText(300, 400, 255, 255, 255, 0, "SPEED++");

            SDL_SetTextureColorMod(powerupTexture, 255, 0, 255);
            blit(powerupTexture, 200, 500, 1);
            drawText(300, 500, 255, 255, 255, 0, "ATTACK SPEED++");

            SDL_SetTextureColorMod(powerupTexture, 255, 0, 255);
            blit(powerupTexture, 200, 600, 1);
            drawText(300, 600, 255, 255, 255, 0, "MAX HP");

            SDL_SetTextureColorMod(powerupWeaponTexture[0], 255, 255, 255);
            blit(powerupWeaponTexture[0], 800, 300, 1);
            drawText(900, 300, 255, 255, 255, 0, "DEFAULT GUN");

            SDL_SetTextureColorMod(powerupWeaponTexture[1], 255, 255, 255);
            blit(powerupWeaponTexture[1], 800, 400, 1);
            drawText(900, 400, 255, 255, 255, 0, "FAST SHOOTING GUN");
            drawText(900, 450, 255, 255, 255, 0, "SMOL DAMAGE");

            SDL_SetTextureColorMod(powerupWeaponTexture[2], 255, 255, 255);
            blit(powerupWeaponTexture[2], 800, 500, 1);
            drawText(900, 500, 255, 255, 255, 0, "SLOW SHOOTING GUN");
            drawText(900, 550, 255, 255, 255, 0, "BIG DAMAGE");

            SDL_SetTextureColorMod(powerupWeaponTexture[3], 255, 255, 255);
            blit(powerupWeaponTexture[3], 800, 600, 1);
            drawText(900, 600, 255, 255, 255, 0, "TRIPLE SHOOTING GUN");
            break;

        case 1:
            drawText(SCREEN_WIDTH/2, 200, 255, 255, 255, 1, "BOSSES");

            SDL_SetTextureColorMod(bossTexture[B_SHOOTER], 255, 255, 255);
            blit(bossTexture[B_SHOOTER], 800, 600, 1);
            drawText(900, 600, 255, 255, 255, 0, "SHOOTER");
            break;
        case 2:
            drawText(SCREEN_WIDTH/2, 200, 255, 255, 255, 1, "ENEMIES 1");
            break;
        case 3:
            drawText(SCREEN_WIDTH/2, 200, 255, 255, 255, 1, "ENEMIES 2");
            break;
    }
    drawText(100, SCREEN_HEIGHT - 100, 255, 255, 255, 1, "<< A");
    drawText(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, 255, 255, 255, 1, "D >>");
}