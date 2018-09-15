#include "ImageManager.h"

void image_init()
{
	int imgAfterInitResult = IMG_Init(IMG_INIT_PNG);
	if ((IMG_INIT_PNG & imgAfterInitResult) != IMG_INIT_PNG)
	{
		SDL_Log("IMG_Init: Failed to init required jpg and png support!\n");
		SDL_Log("IMG_Init: %s\n", IMG_GetError());
	}
}

bool loadImage(SDL_Surface **p_surface, char *p_path)
{
	bool isSucceed = true;

	*p_surface = IMG_Load(p_path);
	if (*p_surface == NULL)
	{
		SDL_Log("Unable to load image %s! SDL Error: %s\n", p_path, SDL_GetError());
		isSucceed = false;
	}

	return isSucceed;
}

SDL_Texture *loadTexture(Window* p_window, SDL_Surface *p_surface)
{
	SDL_Texture *texture = NULL;

	if (p_window == NULL || p_surface == NULL)
		return NULL;

	texture = SDL_CreateTextureFromSurface(p_window->rendererComponent, p_surface);

	if (texture == NULL)
	{
		SDL_Log("Unable to load texture froam surface : %s\n", SDL_GetError());
		return NULL;
	}

	return texture;
}