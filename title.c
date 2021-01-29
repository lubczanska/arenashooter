#include "common.h"

extern void drawText(int x, int y, int r, int g, int b, char *format, ...);
extern void initStage(void);

extern App app;
extern int highscore;

static void logic(void);
static void draw(void);

static int textBlink;

void initTitle(void) {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
    memset(&app.mouse, 0, sizeof(Mouse));
    textBlink = FPS;
}

static void logic(void) {
    if (--textBlink < 0) (textBlink = FPS);
    if (app.keyboard[SDL_SCANCODE_W]) initStage();
    if (app.keyboard[SDL_SCANCODE_ESCAPE]) SDL_Quit();
}

static void draw(void) { //TODO: display proper logo and instructions, settings, save highscore to file
    drawText(SCREEN_WIDTH/2 - 8 * GLYPH_W, SCREEN_HEIGHT/2 - 60, 255, 255, 255, "ARENASHOOTER v1.0");
    drawText(SCREEN_WIDTH/2 - 8 * GLYPH_W, SCREEN_HEIGHT/2 - 30, 255, 255, 255, "HIGHSCORE:%05d", highscore);
    if (textBlink < 30) drawText(SCREEN_WIDTH / 2 - 8 * GLYPH_W, SCREEN_HEIGHT / 2, 255, 255, 255, "PRESS W TO START");
}
