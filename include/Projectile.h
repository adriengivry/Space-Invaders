#ifndef _PROJECTILE_
#define _PROJECTILE_

#define PROJECTILE_WIDTH 5
#define PROJECTLE_HEIGHT 25
#define PROJECTILE_SPEED 10
#define PROJECTILE_SPRITE_PATH "res/projectile.png"

#include <stdbool.h>
#include <SDL.h>
#include "EntityBody.h"
#include "Window.h"

typedef struct Projectile Projectile;
struct Projectile
{
	EntityBody* entityBody;
	int direction;
};

Projectile* projectile_create(int p_x, int p_y, Window* p_window, int p_direction);
void projectile_move(Projectile* p_projectile);
bool projectile_check(Projectile* p_projectile);
void projectile_destroy(Projectile* p_projectile);

#endif // _PROJECTILE_