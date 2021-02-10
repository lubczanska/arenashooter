#include "items.h"

static void addHealthPowerup(int x, int y);
static void addMaxHealthPowerup(int x, int y);
static void addSpeedPowerup(int x, int y);
static void addAtkSpeedPowerup(int x, int y);
static void healthTouch(Entity *other);
static void maxHealthTouch(Entity *other);
static void speedTouch(Entity *other);
static void atkSpeedTouch(Entity *other);
static void addDefaultGunPowerup(int x, int y);
static void addFastGunPowerup(int x, int y);
static void addTripleGunPowerup(int x, int y);
static void addSlowGunPowerup(int x, int y);
static void weaponTouch(Entity *other);
extern void fireDefaultGun(void);
extern void fireFastGun(void);
extern void fireTripleGun(void);
extern void fireSlowGun(void);

SDL_Texture *powerupTexture;
SDL_Texture *powerupWeaponTexture[4];

void initItems(void) {
    powerupTexture = loadTexture("resources/powerup.png");
    powerupWeaponTexture[0] = loadTexture("resources/powerupw1.png");
    powerupWeaponTexture[1] = loadTexture("resources/powerupw2.png");
    powerupWeaponTexture[2] = loadTexture("resources/powerupw3.png");
    powerupWeaponTexture[3] = loadTexture("resources/powerupw4.png");
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

void addPowerupBoss(void) {
    switch (rand() % 4) {
        case 0:
            addDefaultGunPowerup(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
            break;
        case 1:
            addFastGunPowerup(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
            break;
        case 2:
            addTripleGunPowerup(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
            break;
        default:
            addSlowGunPowerup(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
            break;
    }
    switch (rand() % 3) {
        case 0:
            addMaxHealthPowerup(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2);
            break;
        case 1:
            addAtkSpeedPowerup(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2);
            break;
        default:
            addSpeedPowerup(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2);
            break;
    }
}

static Entity *createPowerup(int x, int y) {
	Entity *e;
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
    e->side = SIDE_NEUTRAL;
	e->x = x;
	e->y = y;
	e->health = FPS * 5;
	return e;
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

static void addMaxHealthPowerup(int x, int y) {
    Entity *e;
    e = createPowerup(x, y);
    e->texture = powerupTexture;
    e->color.r = 250;
    e->color.g = 10;
    e->color.b = 100;
    e->color.a = 255;
    e->touch = maxHealthTouch;
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

static void addDefaultGunPowerup(int x, int y) {
    Entity *e;
    e = createPowerup(x, y);
    e->texture = powerupWeaponTexture[0];
    e->color.r = 255;
    e->color.g = 255;
    e->color.b = 255;
    e->color.a = 255;
    e->weapon = fireDefaultGun;
    e->touch = weaponTouch;
}

static void addFastGunPowerup(int x, int y) {
    Entity *e;
    e = createPowerup(x, y);
    e->texture = powerupWeaponTexture[1];
    e->color.r = 255;
    e->color.g = 255;
    e->color.b = 255;
    e->color.a = 255;
    e->weapon = fireFastGun;
    e->touch = weaponTouch;
}

static void addTripleGunPowerup(int x, int y) {
    Entity *e;
    e = createPowerup(x, y);
    e->texture = powerupWeaponTexture[2];
    e->color.r = 255;
    e->color.g = 255;
    e->color.b = 255;
    e->color.a = 255;
    e->weapon = fireTripleGun;
    e->touch = weaponTouch;
}

static void addSlowGunPowerup(int x, int y) {
    Entity *e;
    e = createPowerup(x, y);
    e->texture = powerupWeaponTexture[3];
    e->color.r = 255;
    e->color.g = 255;
    e->color.b = 255;
    e->color.a = 255;
    e->weapon = fireSlowGun;
    e->touch = weaponTouch;
}

static void healthTouch(Entity *other) {
	if (other == player) {
		player->health = MIN(player->health + 2, PLAYER_HEALTH); // you can't heal above base hp
        playSound(POWERUP, CH_ITEM);
        stage.waveState = NEW;
	}
}

static void speedTouch(Entity *other) {
    if (other == player) {
        player->speed = MIN(player->speed + 0.5, 8);
        playSound(POWERUP, CH_ITEM);
        stage.waveState = NEW;
    }
}

static void atkSpeedTouch(Entity *other) {
    if (other == player) {
        player->atkSpeed = MAX(player->atkSpeed + 0.3, 4);
        playSound(POWERUP, CH_ITEM);
        stage.waveState = NEW;
    }
}

//special boss powerups
static void maxHealthTouch(Entity *other) {
    if (other == player) {
        player->health = PLAYER_HEALTH;
        playSound(POWERUP, CH_ITEM);
        stage.waveState = NEW;
    }
}

static void weaponTouch(Entity *other) {
    if (other == player) {
        if (player->weapon == self->weapon) {
            player->damage = MIN(player->damage + 1, 5);
            stage.score += 10;
        }
        else player->weapon = self->weapon;
        playSound(POWERUP, CH_ITEM);
        stage.waveState = NEW;
    }
}