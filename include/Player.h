#ifndef _PLAYER_
#define _PLAYER_

#define PLAYER_X_START_POS 600
#define PLAYER_Y_START_POS 700
#define PLAYER_WIDTH 72
#define PLAYER_HEIGHT 45
#define PLAYER_LIFE 3
#define PLAYER_SPRITE_PATH "res/player.png"
#define PLAYER_X_SPEED 5

#include "EntityBody.h"
#include "Window.h"

typedef struct Player Player;
struct Player
{
	EntityBody* entityBody;
	unsigned int life;
	unsigned int maxLife;
};

Player* player_create(Window* p_window);
void player_move(const Uint8* p_keyboardState, Player* p_player);
void player_destroy(Player* p_player);

#endif // _PLAYER_
