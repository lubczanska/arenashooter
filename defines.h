#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b)) //why do I have to do that arghhhh
#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'
#define PI 3.141592653589793

#define PLAYER_HEALTH 50
#define PLAYER_SPEED 6
#define PLAYER_ATKSPEED 12 //the bigger the slower
#define PLAYER_ATKSPEED 12


#define SCREEN_WIDTH   1600
#define SCREEN_HEIGHT  900

#define FPS 60

#define MAX_KEYBOARD_KEYS 350
#define MAX_MOUSE_BUTTONS 6

#define MAX_NAME_LENGTH 32
#define GLYPH_W  7
#define GLYPH_H 9
#define MAX_LINE_LENGTH 1024

enum {
	SIDE_NEUTRAL,
	SIDE_PLAYER,
	SIDE_ENEMY
};
