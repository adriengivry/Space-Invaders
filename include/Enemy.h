#ifndef _ENEMY_
#define _ENEMY_

#define ENEMY_WIDTH 50
#define ENEMY_HEIGHT 35
#define ENEMY_SPRITE_PATH1 "res/enemy1.png"
#define ENEMY_SPRITE_PATH2 "res/enemy2.png"
#define ENEMY_X_SPEED 10
#define ENEMY_Y_SPEED 20

#include <stdbool.h>
#include "EntityBody.h"
#include "Window.h"
#include <time.h>

typedef struct Enemy Enemy;
struct Enemy
{
	EntityBody* entityBody[2];
	bool isAlive;
	int toRender;
	int counter;
	int stageIndicator;
	int scoreValue;
};

Enemy* enemy_create(Window* p_window, int p_x, int p_y, int p_stage, int p_scoreValue);
void enemy_move(Enemy* p_enemies[5][11], int p_x, int p_y);
bool enemy_hit_a_wall(Enemy* p_enemies[5][11]);
bool enemy_won(Enemy* p_enemies[5][11]);
void enemy_update(Enemy* p_enemies[5][11]);
bool enemy_all_dead(Enemy* p_enemies[5][11]);
void enemy_destroy_all(Enemy* p_enemies[5][11]);
bool enemy_find_pos(Enemy* p_enemies[5][11], int* x, int* y);
int enemy_generate_rand(int a, int b);

#endif // _ENEMY_