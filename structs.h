typedef struct Texture Texture;
typedef struct Entity Entity;
typedef struct Effect Effect;

typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

struct Texture {
	char name[MAX_NAME_LENGTH];
	SDL_Texture *texture;
	Texture *next;
};

typedef struct {
    int x;
    int y;
    int button[MAX_MOUSE_BUTTONS];
    int wheel;
} Mouse;

struct Entity {
	int side;
	float x;
	float y;
	float dx;
	float dy;
    int w;
    int h;
	int health;
	float speed;
	float reload;
	float atkSpeed;
	int damage;
	int angle;
	int hit;
	SDL_Texture *texture;
	SDL_Color color;
    void (*weapon)(void);
	void (*tick)(void);
	void (*touch)(Entity *other);
	void (*die)(void);
	Entity *next;
};

struct Effect {
    float x;
    float y;
    float dx;
    float dy;
    int lifetime;
    SDL_Color color;
    SDL_Texture *texture;
    Effect *next;
};

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
    Mouse mouse;
	Texture textureHead, *textureTail;
} App;

typedef struct {
    int pause;
	int score;
	int wave;
	int waveLeftToSpawn;
	int waveEnemies;
	int waveState;
	Entity entityHead, *entityTail;
	Entity bulletHead, *bulletTail;
    Effect effectHead, *effectTail;
} Stage;
