//delete mouse once unnecessary

#include "common.h"

extern App app;

void doKeyUp(SDL_KeyboardEvent *event) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) app.keyboard[event->keysym.scancode] = 0;
}

void doKeyDown(SDL_KeyboardEvent *event) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) app.keyboard[event->keysym.scancode] = 1;
}

void doMouseButtonUp(SDL_MouseButtonEvent *event) {
    app.mouse.button[event->button] = 0;
}

void doMouseButtonDown(SDL_MouseButtonEvent *event) {
    app.mouse.button[event->button] = 1;
}

void doInput(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;
			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;
            case SDL_MOUSEBUTTONDOWN:
                doMouseButtonDown(&event.button);
                break;

            case SDL_MOUSEBUTTONUP:
                doMouseButtonUp(&event.button);
                break;
			default:
				break;
		}
	}
    SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
}
