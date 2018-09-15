#include "Window.h"

void window_init(Window* p_window)
{
	p_window->windowComponent = SDL_CreateWindow(WIN_TITLE,
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										WIN_WIDTH, WIN_HEIGHT, 0);

	p_window->rendererComponent = SDL_CreateRenderer(p_window->windowComponent, -1, SDL_RENDERER_PRESENTVSYNC);
}

void window_update(Window* p_window)
{
	SDL_RenderPresent(p_window->rendererComponent);
}

void window_clear(Window* p_window)
{
	SDL_SetRenderDrawColor(p_window->rendererComponent, 0, 0, 0, 255);
	if (SDL_RenderClear(p_window->rendererComponent))
	{
		SDL_Log("Unable to clear screen renderer : %s\n", SDL_GetError());
	}
}

void window_close(Window* p_window)
{
	if (p_window == NULL)
		return;

	if (p_window->rendererComponent != NULL)
	{
		SDL_DestroyRenderer(p_window->rendererComponent);
		p_window->rendererComponent = NULL;
	}

	if (p_window->windowComponent != NULL)
	{
		SDL_DestroyWindow(p_window->windowComponent);
		p_window->windowComponent = NULL;
	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
