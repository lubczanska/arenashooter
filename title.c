#include "common.h"

extern void drawText(int x, int y, int r, int g, int b, int center, char *format, ...);
extern void initStage(void);
extern void initHelp(void);
extern void initSettings(void);

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
    if (app.keyboard[SDL_SCANCODE_H]) initHelp();
    if (app.keyboard[SDL_SCANCODE_S]) initSettings();
    if (app.keyboard[SDL_SCANCODE_ESCAPE]) exit(0);
}

static void draw(void) {
    drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 100, 255, 255, 255, 1, "ARENASHOOTER v1.0");
    drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 50, 255, 255, 255, 1,"HIGHSCORE:%05d", highscore);
    if (textBlink < 30) drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, 255, 255, 255, 1, "PRESS W TO START");
}
