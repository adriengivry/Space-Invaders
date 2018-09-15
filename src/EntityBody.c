#include "EntityBody.h"

EntityBody* entitybody_create(int p_x, int p_y, int p_w, int p_h, const char* p_texturePath, Window* p_window)
{
	EntityBody* entityBody = (EntityBody*)malloc(sizeof(EntityBody));
	entityBody->hitbox.x = p_x;
	entityBody->hitbox.y = p_y;
	entityBody->hitbox.w = p_w;
	entityBody->hitbox.h = p_h;

	loadImage(&entityBody->sprite, p_texturePath);
	entityBody->texture = loadTexture(p_window, entityBody->sprite);

	return entityBody;
}

bool is_colliding(EntityBody* p_e1, EntityBody* p_e2)
{
	int x1 = p_e1->hitbox.x;
	int x2 = p_e2->hitbox.x;
	int y1 = p_e1->hitbox.y;
	int y2 = p_e2->hitbox.y;

	int w1 = p_e1->hitbox.w;
	int w2 = p_e2->hitbox.w;
	int h1 = p_e1->hitbox.h;
	int h2 = p_e2->hitbox.h;

	return (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2);
}

void entitybody_duplicate_hitbox(EntityBody* p_dest, EntityBody* p_src)
{
	p_dest->hitbox.x = p_src->hitbox.x;
	p_dest->hitbox.y = p_src->hitbox.y;
	p_dest->hitbox.w = p_src->hitbox.w;
	p_dest->hitbox.h = p_src->hitbox.h;
}

void entitybody_destroy(EntityBody* p_entityBody)
{
	if (p_entityBody)
	{
		if (p_entityBody->sprite)
			SDL_FreeSurface(p_entityBody->sprite);

		if (p_entityBody->texture)
 			SDL_DestroyTexture(p_entityBody->texture);
		

		free(p_entityBody);
	}

	
}