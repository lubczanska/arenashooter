#include "common.h"

extern SDL_Texture *loadTexture(char *filename);

extern Entity *player;
extern Entity *self;
extern Stage stage;

static void tick(void);
static void addHealthPowerup(int x, int y);
static void addSpeedPowerup(int x, int y);
static void addAtkSpeedPowerup(int x, int y);
static void healthTouch(Entity *other);
static void speedTouch(Entity *other);
static void atkSpeedTouch(Entity *other);


static SDL_Texture *powerupTexture;

void initItems(void) {
    powerupTexture = loadTexture("resources/powerup.png");
}

void addPowerup(int x, int y) {
    switch (rand() % 3) {
        case 0:
            addSpeedPowerup(x, y);
            break;
        case 1:
            addAtkSpeedPowerup(x, y);
            break;
        default:
            addHealthPowerup(x, y);
            break;
    }
}

static Entity *createPowerup(int x, int y) {
	Entity *e;
	
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	
	e->x = x;
	e->y = y;
	e->health = FPS * 5;
	e->tick = tick;
	return e;
}

static void tick(void) {
	self->health--; // they disappear if you don't pick them up
}

static void addHealthPowerup(int x, int y) {
	Entity *e;
	
	e = createPowerup(x, y);
	e->texture = powerupTexture;
    e->color.r = 250;
    e->color.g = 10;
    e->color.b = 45;
    e->color.a = 255;
	e->touch = healthTouch;
}

static void addSpeedPowerup(int x, int y) {
    Entity *e;

    e = createPowerup(x, y);
    e->texture = powerupTexture;
    e->color.r = 128;
    e->color.g = 227;
    e->color.b = 42;
    e->color.a = 255;
    e->touch = speedTouch;
}

static void addAtkSpeedPowerup(int x, int y) {
    Entity *e;

    e = createPowerup(x, y);
    e->texture = powerupTexture;
    e->color.r = 245;
    e->color.g = 187;
    e->color.b = 30;
    e->color.a = 255;
    e->touch = atkSpeedTouch;
}

static void healthTouch(Entity *other) {
	if (other == player) {
		self->health = 0;
		player->health += 5;
	}
}

static void speedTouch(Entity *other) {
    if (other == player) {
        self->health = 0;
        player->speed = MIN(player->speed + 0.5, 8);
    }
}

static void atkSpeedTouch(Entity *other) {
    if (other == player) {
        self->health = 0;
        //player->atkSpeed = MAX(player->atkSpeed - 0.2, 4);
    }
}
