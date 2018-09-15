#ifndef _ENTITYBODY_
#define _ENTITYBODY_

#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"

typedef struct EntityBody EntityBody;
struct EntityBody
{
	SDL_Rect hitbox;
	SDL_Surface* sprite;
	SDL_Texture* texture;
};

EntityBody* entitybody_create(int p_x, int p_y, int p_w, int p_h, const char* p_texturePath, Window* p_window);
bool is_colliding(EntityBody* p_e1, EntityBody* p_e2);
void entitybody_duplicate_hitbox(EntityBody* p_dest, EntityBody* p_src);
void entitybody_destroy(EntityBody* p_entityBody);

#endif // _ENTITYBODY_