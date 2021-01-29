#include "common.h"

extern void getSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void angledSlope(int x1, int y1, int x2, int y2, float angle, float *dx, float *dy);
extern int getDistance(int x1, int y1, int x2, int y2);
extern float getAngle(int x1, int y1, int x2, int y2);
extern Entity *createBullet(Entity *shooter);
extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Entity *player;
extern Entity *self;
extern Stage stage;

void shooterShot(void) {
    Entity *b;
    b = createBullet(self);
    getSlope(player->x, player->y, b->x, b->y, &b->dx, &b->dy);
    b->dx *= MIN(12 + (stage.wave * 0.3), 16);
    b->dy *= MIN(12 + (stage.wave * 0.3), 16);
    //reload controlled by tick function
}

void crossShooterShot(void) {
    Entity *b;
    for (int i = -1; i < 2; i += 2) {
        b = createBullet(self);
        b->dx = i * MIN(5 + (stage.wave * 0.3), 16);
        b->dy = 0 * MIN(5 + (stage.wave * 0.3), 16);
        b = createBullet(self);
        b->dx = 0 * MIN(5 + (stage.wave * 0.3), 16);
        b->dy = i * MIN(5 + (stage.wave * 0.3), 16);
    }
    //reload controlled by tick function
}

void lineShooterShot(void) {
    Entity *b;
    b = createBullet(self);
    b->dx = self->dx * MIN(7 + (stage.wave * 0.3), 16);
    b->dy = self->dy * MIN(7 + (stage.wave * 0.3), 16);
}
