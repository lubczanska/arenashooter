#include "common.h"

extern void firePlayerBullet(void);
extern float getAngle(int x1, int y1, int x2, int y2);
extern SDL_Texture *loadTexture(char *filename);

extern App app;
extern Entity *player;
extern Stage stage;

static SDL_Texture *playerTexture;

void initPlayer(void) {
	playerTexture = loadTexture("resources/playerSquare.png");
}

static void die(void) {
    player = NULL;
}

static void enemyTouch(Entity *other) {
    if (other->side == SIDE_ENEMY) {
        player->health--;
    }
}

void addPlayer(void) {
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.entityTail->next = player;
	stage.entityTail = player;
	
	player->texture = playerTexture;
	player->health = PLAYER_HEALTH;
	player->speed = PLAYER_SPEED;
	player->atkSpeed = PLAYER_ATKSPEED;
	player->range = 1;
    player->touch = enemyTouch;
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	player->side = SIDE_PLAYER;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
	player->color.r = 33;
	player->color.g = 120;
	player->color.b = 255;
	player->color.a = 255;
	player->die = die;
}

void doPlayer(void) {
	if (player != NULL) {
		player->dx *= 0.85;
		player->dy *= 0.85;

		if (app.keyboard[SDL_SCANCODE_W]) player->dy = -1;
		if (app.keyboard[SDL_SCANCODE_S]) player->dy = 1;
		if (app.keyboard[SDL_SCANCODE_A]) player->dx = -1;
		if (app.keyboard[SDL_SCANCODE_D]) player->dx = 1;

        player->angle = getAngle(player->x, player->y, app.mouse.x, app.mouse.y);

        if (player->reload == 0 && app.mouse.button[SDL_BUTTON_LEFT]) firePlayerBullet();
	}
}

