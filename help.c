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


void initHelp(void) {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

}

static void logic(void) {
    if (app.keyboard[SDL_SCANCODE_BACKSPACE]) initTitle();
    if (app.keyboard[SDL_SCANCODE_ESCAPE]) exit(0);
    if (app.keyboard[SDL_SCANCODE_D]) { page = (page + 1) % HELP_PAGES; SDL_Delay(300); }
    if (app.keyboard[SDL_SCANCODE_A]) { page = (page - 1) % HELP_PAGES; SDL_Delay(300); }
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
            blit(powerupTexture, 200, 700, 1);
            drawText(300, 700, 255, 255, 255, 0, "MAX HP");

            SDL_SetTextureColorMod(powerupTexture, 255, 255, 255);
            blit(powerupTexture, 200, 300, 1);
            drawText(300, 300, 255, 255, 255, 0, "HP++");

            SDL_SetTextureColorMod(powerupTexture, 255, 255, 255);
            blit(powerupTexture, 200, 300, 1);
            drawText(300, 300, 255, 255, 255, 0, "HP++");

            SDL_SetTextureColorMod(powerupTexture, 255, 255, 255);
            blit(powerupTexture, 200, 300, 1);
            drawText(300, 300, 255, 255, 255, 0, "HP++");

            SDL_SetTextureColorMod(powerupTexture, 255, 255, 255);
            blit(powerupTexture, 200, 300, 1);
            drawText(300, 300, 255, 255, 255, 0, "HP++");
            break;
        case 1:
            drawText(SCREEN_WIDTH/2, 200, 255, 255, 255, 1, "BOSSES");
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