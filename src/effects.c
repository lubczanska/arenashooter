#include "effects.h"

static SDL_Texture *effectSquare8;

void initEffects(void) {
    effectSquare8 = loadTexture("resources/square8.png");
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

        f->texture = effectSquare8;

        f->color = e->color;
        f->color.r = 110;
        f->color.g = 110;
        f->color.b = 110;
        f->color.a = 255;
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

        f->texture = effectSquare8;

        //f->color = player->color;
        f->color.r = 110;
        f->color.g = 110;
        f->color.b = 110;
        f->color.a = 255;

        f->lifetime = rand() % FPS;
    }
}