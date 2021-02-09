#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b)) //why do I have to do that arghhhh
#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'
#define PI 3.141592653589793

#define PLAYER_HEALTH 20 //base stats
#define PLAYER_SPEED 6
#define PLAYER_RELOAD 12

#define SCREEN_WIDTH   1920
#define SCREEN_HEIGHT  1080

#define FPS 60

#define MAX_KEYBOARD_KEYS 350
#define MAX_MOUSE_BUTTONS 6

#define MAX_NAME_LENGTH 32
#define GLYPH_W  16
#define GLYPH_H 30
#define MAX_LINE_LENGTH 1024
#define MAX_CHANNELS 16

#define HELP_PAGES 4

enum sides{
	SIDE_NEUTRAL,
	SIDE_PLAYER,
	SIDE_ENEMY,
	SIDE_BOSS //for eliminating boss knockback
};

enum enemies {
    SHOOTER,
    LINE_SHOOTER,
    CROSS_SHOOTER,
    MULTI_SHOOTER,
    SLOW_MULTI_SHOOTER,
    STAR_SHOOTER,
    SNIPER,
    RUNNER,
    RAMMER,
    SLUG
};

enum bosses {
    B_SHOOTER,
    B_SPAWNER,
    B_SPIN,
    B_SPLIT_0,
    B_SPLIT_1,
    B_SPLIT_2
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
    NEW_BEGIN,
    NORMAL,
    BOSS,
    END,
    BOSS_END
};

enum prompts {
    ENEMIES_1,
    ITEMS,
    ENEMIES_2,
    BOSS_1,
    ITEMS_BOSS,
    ENEMIES_3,
    ENEMIES_4,
    BOSS_2,
    ENEMIES_5,
    BOSS_3,
    BOSS_4
};


#define BOSS_BAR_GLYPH 12
#define PLAYER_BAR_GLYPH 8