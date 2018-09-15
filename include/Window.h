#ifndef _WINDOW_
#define _WINDOW_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>

#define WIN_WIDTH 1200
#define WIN_HEIGHT 800
#define WIN_TITLE "Space Invaders Like"

typedef struct Window Window;
struct Window
{
	SDL_Window* windowComponent;
	SDL_Renderer* rendererComponent;
};

void window_init(Window* p_window);
void window_update(Window* p_window);
void window_clear(Window* p_window);
void window_close(Window* p_window);

#endif // _WINDOW_