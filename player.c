#include "player.h"

static SDL_Texture *playerTexture;

void initPlayer(void) {
	playerTexture = loadTexture("resources/playerSquare.png");
}

static void die(void) {
    addPlayerDeathEffect();
    player = NULL;
}

static void enemyTouch(Entity *other) { //touching enemies inflicts damage
    if (other->side >= SIDE_ENEMY) {
        player->hit = 4;
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
    player->touch = enemyTouch;
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	player->side = SIDE_PLAYER;
	player->weapon = fireDefaultGun;
	player->atkSpeed = 0;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
	player->color.r = 255;
	player->color.g = 255;
	player->color.b = 255;
	player->color.a = 255;
	player->die = die;
}

void doPlayer(void) {
	if (player != NULL) {
		player->dx *= 0.85; //for smooth movement
		player->dy *= 0.85;

		if (app.keyboard[SDL_SCANCODE_W]) player->dy = -1;
		if (app.keyboard[SDL_SCANCODE_S]) player->dy = 1;
		if (app.keyboard[SDL_SCANCODE_A]) player->dx = -1;
		if (app.keyboard[SDL_SCANCODE_D]) player->dx = 1;
        if (app.keyboard[SDL_SCANCODE_0]) player->weapon = fireDefaultGun; //just for testing
        if (app.keyboard[SDL_SCANCODE_1]) player->weapon = fireFastGun;
        if (app.keyboard[SDL_SCANCODE_3]) player->weapon = fireTripleGun;
        if (app.keyboard[SDL_SCANCODE_4]) player->weapon = fireSlowGun;
        if (app.keyboard[SDL_SCANCODE_SPACE]) {
            SDL_Delay(100);
            stage.pause = 1;
        }

        player->angle = getAngle(player->x, player->y, app.mouse.x, app.mouse.y);

        if (player->reload == 0 && app.mouse.button[SDL_BUTTON_LEFT]) player->weapon();
	}
}

