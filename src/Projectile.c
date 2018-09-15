#include "Projectile.h"

Projectile* projectile_create(int p_x, int p_y, Window* p_window, int p_direction)
{
	Projectile* projectile = (Projectile*)malloc(sizeof(Projectile));
	projectile->entityBody = entitybody_create(p_x, p_y, PROJECTILE_WIDTH, PROJECTLE_HEIGHT, PROJECTILE_SPRITE_PATH, p_window);
	projectile->direction = p_direction;
	return projectile;
}

void projectile_move(Projectile* p_projectile)
{
	p_projectile->entityBody->hitbox.y += PROJECTILE_SPEED * p_projectile->direction;
}

bool projectile_check(Projectile* p_projectile)
{
	return (p_projectile->entityBody->hitbox.y < 0 || p_projectile->entityBody->hitbox.y > 800);
}

void projectile_destroy(Projectile* p_projectile)
{
	if (p_projectile == NULL)
		return;

	entitybody_destroy(p_projectile->entityBody);

	free(p_projectile);
}