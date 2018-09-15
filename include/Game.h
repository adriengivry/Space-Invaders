#ifndef _GAME_
#define _GAME_

#define STATE_PAUSE 0
#define STATE_PLAY 1
#define STATE_GAMEOVER 2
#define STATE_WON 3
#define STATE_MENU 4

#include <SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "Window.h"
#include "ImageManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "UserInterface.h"
#include "int_to_alpha.h"
#include "Text.h"

typedef struct GameInfo GameInfo;
struct GameInfo
{
	bool exit;
	bool won;
	const Uint8* keyboardState;
	int enemiesDirection;
	int stage;
	int score;
	int gameState;
};

typedef struct GameEntities GameEntities;
struct GameEntities
{
	Player* player;
	Enemy* enemies[5][11];
	Projectile* projectile;
	Projectile* enemyProjectile;
};

typedef struct Game Game;
struct Game
{
	Window* window;
	GameInfo* gameInfo;
	GameEntities* gameEntities;
	UserInterface* userInterface;
};

void game_tick(Game* p_game);
void game_init(Game* p_game, int p_stage, int p_score);
void game_init_all(Game* p_game);
void game_update(Game* p_game);
void game_close(Game* p_game);
void game_check_input(Game* p_game);
void game_init_entities(GameEntities* p_gameEntities, Window* p_window, int p_stage);
void game_display_entities(Game* p_game);
void game_destroy(Game* p_game);

#endif // _GAME_
