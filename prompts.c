#include "common.h"

extern void drawText(int x, int y, int r, int g, int b, int center, char *format, ...);
extern void initTitle(void);
extern void blit(SDL_Texture *texture, int x, int y, int center);

extern App app;

extern int prompts[11][2];
extern int nextPrompt;
void displayPrompt(int index);

void displayPrompt(int index) {
    switch(index) {
        case ENEMIES_1:

            break;
        case ITEMS:
        case ENEMIES_2:
        case BOSS_1:
        case ITEMS_BOSS:
        case ENEMIES_3:
        case ENEMIES_4:
        case BOSS_2:
        case ENEMIES_5:
        case BOSS_3:
        case BOSS_4:
            break;
    }
}