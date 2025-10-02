#ifndef _IMAGEMANAGER_
#define _IMAGEMANAGER_

#include "Window.h"
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>

void image_init();
bool loadImage(SDL_Surface **p_surface, const char *p_path);
SDL_Texture *loadTexture(Window* p_window, SDL_Surface *p_surface);

#endif // _IMAGEMANAGER_