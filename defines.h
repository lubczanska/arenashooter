#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b)) //why do I have to do that arghhhh
#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'
#define PI 3.141592653589793

#define PLAYER_HEALTH 50
#define PLAYER_SPEED 6
#define PLAYER_RELOAD 12 //the bigger the slower


#define SCREEN_WIDTH   1600
#define SCREEN_HEIGHT  900

#define FPS 60

#define MAX_KEYBOARD_KEYS 350
#define MAX_MOUSE_BUTTONS 6

#define MAX_NAME_LENGTH 32
#define GLYPH_W  7
#define GLYPH_H 9
#define MAX_LINE_LENGTH 1024
#define MAX_CHANNELS 16

enum sides{
	SIDE_NEUTRAL,
	SIDE_PLAYER,
	SIDE_ENEMY
};

enum weapons {
    DEFAULT_GUN,
    FAST_GUN,
    SLOW_GUN,
    TRIPLE_SHOT,
    QUAD_SHOT,
    LASER_PISTOL
};

enum enemies {
    SHOOTER, //shooting
    CROSS_SHOOTER,
    LINE_SHOOTER,
    SNIPER,
    SHOTGUN_SHOOTER,
    RUNNER,  //melee
    RAMMER
};

enum sounds {
    PLAYER_FIRE,
    PLAYER_HIT,
    POWERUP
};

enum channels {
    CH_ANY = -1,
    CH_PLAYER,
    CH_ENEMY,
    CH_ITEM
};

enum wave {
    NEW,
    NORMAL,
    BOSS,
    END,
    BOSS_END
};

#define BOSS_BAR_GLYPH 16
#define BOSS_BAR_EDGE 4