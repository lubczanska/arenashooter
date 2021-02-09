#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Entity *self;
extern Entity *player;
extern Stage stage;

static SDL_Texture *whiteSquare8;

void initEffects(void) {
    whiteSquare8 = loadTexture("resources/square12.png");
}

void doEffects(void) {
    Effect *f, *prev;
    prev = &stage.effectHead;
    for (f = stage.effectHead.next; f != NULL; f = f->next) {
        f->x += f->dx;
        f->y += f->dy;
        if (--f->lifetime <= 0) {
            if (f == stage.effectTail) stage.effectTail = prev;
            prev->next = f->next;
            free(f);
            f = prev;
        }
        prev = f;
    }
}

void drawEffects(void) {
    Effect *f;
    for (f = stage.effectHead.next; f != NULL; f = f->next) {
        SDL_SetTextureColorMod(f->texture, f->color.r, f->color.g, f->color.b);
        blit(f->texture, f->x, f->y, 1);
    }
}

void addEnemyDeathEffect(Entity *e) {
    Effect *f;
    for (int i = 0 ; i < 32 ; i++) {
        f = malloc(sizeof(Effect));
        memset(f, 0, sizeof(Effect));
        stage.effectTail->next = f;
        stage.effectTail = f;

        f->x = self->x;
        f->y = self->y;
        f->dx = 400 - rand() % 800;
        f->dy = 400 - rand() % 800;

        f->dx /= 50;
        f->dy /= 50;

        f->texture = whiteSquare8;

        f->color = e->color;
//        f->color.a = rand() % 255;

        f->lifetime = rand() % FPS;
    }
}

void addPlayerDeathEffect(void)
{
    Effect *f;
    for (int i = 0 ; i < 32 ; i++) {
        f = malloc(sizeof(Effect));
        memset(f, 0, sizeof(Effect));
        stage.effectTail->next = f;
        stage.effectTail = f;

        f->x = self->x;
        f->y = self->y;
        f->dx = 400 - rand() % 800;
        f->dy = 400 - rand() % 800;

        f->dx /= 50;
        f->dy /= 50;

        f->texture = whiteSquare8;

        f->color = player->color;

        f->lifetime = rand() % FPS;
    }
}