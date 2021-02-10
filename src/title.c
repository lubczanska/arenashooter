#include "title.h"

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
    drawText(200, SCREEN_HEIGHT - 100, 255, 255, 255, 1, "ESC - quit");
    drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100, 255, 255, 255, 1, "S - settings");
    drawText(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 100, 255, 255, 255, 1, "H - help");
    drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 200, 255, 255, 255, 1, "arenashooter v1.0");
    drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 100, 255, 255, 255, 1,"HIGHSCORE %05d", highscore);
    if (textBlink < 30) drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, 255, 255, 255, 1, "press W to start");
}
