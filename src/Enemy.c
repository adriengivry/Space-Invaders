#include "Enemy.h"

Enemy* enemy_create(Window* p_window, int p_x, int p_y, int p_stage, int p_scoreValue)
{
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	if (!enemy)
		return NULL;

	enemy->entityBody[0] = entitybody_create(p_x, p_y, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_SPRITE_PATH1, p_window);
	enemy->entityBody[1] = entitybody_create(p_x, p_y, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_SPRITE_PATH2, p_window);
	enemy->isAlive = true;
	enemy->toRender = 0;
	enemy->counter = 0;
	enemy->stageIndicator = p_stage;
	enemy->scoreValue = p_scoreValue;
	return enemy;
}

void enemy_move(Enemy* p_enemies[5][11], int p_x, int p_y)
{
	Enemy* current = NULL;
	for (int row = 0; row < 5; ++row)
	{
		for (int col = 0; col < 11; ++col)
		{
			current = p_enemies[row][col];
			current->entityBody[0]->hitbox.x += (ENEMY_X_SPEED + current->stageIndicator * 3) / 10 * p_x;
			current->entityBody[0]->hitbox.y += ENEMY_Y_SPEED * p_y;
		}
	}
}

bool enemy_hit_a_wall(Enemy* p_enemies[5][11])
{
	for (int row = 0; row < 5; ++row)
	{
		for (int col = 0; col < 11; ++col)
		{
			if (p_enemies[row][col]->isAlive &&
				(p_enemies[row][col]->entityBody[0]->hitbox.x + p_enemies[row][col]->entityBody[0]->hitbox.w >= 1200 ||
					p_enemies[row][col]->entityBody[0]->hitbox.x <= 0))
				return true;
		}
	}

	return false;
}

bool enemy_won(Enemy* p_enemies[5][11])
{
	for (int row = 0; row < 5; ++row)
	{
		for (int col = 0; col < 11; ++col)
		{
			if (p_enemies[row][col]->isAlive && p_enemies[row][col]->entityBody[0]->hitbox.y >= 700)
				return true;
		}
	}

	return false;
}

void enemy_update(Enemy* p_enemies[5][11])
{
	for (int row = 0; row < 5; ++row)
	{
		for (int col = 0; col < 11; ++col)
		{
			entitybody_duplicate_hitbox(p_enemies[row][col]->entityBody[1], p_enemies[row][col]->entityBody[0]);
			p_enemies[row][col]->counter++;
			if (p_enemies[row][col]->counter == 50)
			{
				p_enemies[row][col]->counter = 0;
				p_enemies[row][col]->toRender++;
				if (p_enemies[row][col]->toRender > 1)
					p_enemies[row][col]->toRender = 0;
			}
		}
	}
	
}

bool enemy_all_dead(Enemy* p_enemies[5][11])
{
	for (int row = 0; row < 5; ++row)
	{
		for (int col = 0; col < 11; ++col)
		{
			if (p_enemies[row][col]->isAlive)
				return false;
		}
	}

	return true;
}

void enemy_destroy_all(Enemy* p_enemies[5][11])
{
	for (int row = 0; row < 5; ++row)
	{
		for (int col = 0; col < 11; ++col)
		{
			entitybody_destroy(p_enemies[row][col]->entityBody[0]);
			entitybody_destroy(p_enemies[row][col]->entityBody[1]);
			free(p_enemies[row][col]);
		}
	}
}

bool enemy_find_pos(Enemy* p_enemies[5][11], int* x, int* y)
{
	bool canShoot;
	for (int row = 0; row < 5; ++row)
	{
		for (int col = 0; col < 11; ++col)
		{
			if (p_enemies[row][col]->isAlive && enemy_generate_rand(1, 500) == 3)
			{
				canShoot = true;
				for (int rowLoop = row + 1; rowLoop < 5; ++rowLoop)
				{
					if (p_enemies[rowLoop][col]->isAlive)
					{
						canShoot = false;
					}
				}
				if (canShoot)
				{
					*x = p_enemies[row][col]->entityBody[0]->hitbox.x + p_enemies[row][col]->entityBody[0]->hitbox.w / 2;
					*y = p_enemies[row][col]->entityBody[0]->hitbox.y + p_enemies[row][col]->entityBody[0]->hitbox.h;
					return true;
				}
			}
		}
	}
	return false;
}

int enemy_generate_rand(int a, int b) {
	return rand() % (b - a) + a;
}