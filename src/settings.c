#include "common.h"

#include "SDL2/SDL_mixer.h"

extern void drawText(int x, int y, int r, int g, int b, int center, char *format, ...);
extern void initTitle(void);
extern void playSound(int id, int channel);
extern App app;

static void logic(void);
static void draw(void);
static void changeVolume(void);
static int activeField;
static int *settingFields[2];

void initSettings(void) {
    SDL_Delay(300);
    settingFields[0] = &app.volumeMusic;
    settingFields[1] = &app.volumeSounds;
    app.delegate.logic = logic;
    app.delegate.draw = draw;

}

static void logic(void) {
    if (app.keyboard[SDL_SCANCODE_BACKSPACE]) initTitle();
    if (app.keyboard[SDL_SCANCODE_ESCAPE]) exit(0);
    if (app.keyboard[SDL_SCANCODE_W]) {
        activeField = (activeField + 1) % 2;
        SDL_Delay(300);
    }
    if (app.keyboard[SDL_SCANCODE_S]) {
        activeField = ((activeField - 1) % 2 + 2) % 2;
        SDL_Delay(300);
    }
    if (app.keyboard[SDL_SCANCODE_D]) {
        *settingFields[activeField] = MIN(*settingFields[activeField] + 10, 100);
        changeVolume();
        SDL_Delay(300);
    }
    if (app.keyboard[SDL_SCANCODE_A]) {
        *settingFields[activeField] = MAX(*settingFields[activeField] - 10, 0);
        changeVolume();
        SDL_Delay(300);
    }
}

static void changeVolume(void) {
    Mix_Volume(CH_ANY, app.volumeSounds);
    Mix_Volume(CH_PLAYER, app.volumeSounds + 20);
    Mix_VolumeMusic(app.volumeMusic);
    playSound(POWERUP, CH_ITEM);
}

static void draw(void) {
    drawText(SCREEN_WIDTH/2, 100, 255, 255, 255, 1, "SETTINGS");
    drawText(SCREEN_WIDTH/2, 150, 255, 255, 255, 1, "W,S - select");
    drawText(SCREEN_WIDTH/2, 200, 255, 255, 255, 1, "<< A   D >>");
    drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100, 255, 255, 255, 1, "BACKSPACE - return to menu");
    for (int i = 0; i < 2; i++) {
        drawText(500, SCREEN_HEIGHT / 2, 255, 255, 255, 1, "MUSIC VOLUME");
        drawText(500, SCREEN_HEIGHT / 2 + 100, 255, 255, 255, 1, "SOUNDS VOLUME");
        if (activeField == i) {
            drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + i*100, 255, 0, 0, 1, "%d", *settingFields[i]);
        }
        else drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + i*100, 255, 255, 255, 1, "%d", *settingFields[i]);
    }
}