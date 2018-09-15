#include "Player.h"

Player* player_create(Window* p_window)
{
	Player* player = (Player*)malloc(sizeof(Player));
	player->entityBody = entitybody_create(PLAYER_X_START_POS, PLAYER_Y_START_POS, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_SPRITE_PATH, p_window);
	player->life = PLAYER_LIFE;
	player->maxLife = player->life;
	return player;
}

void player_move(const Uint8* p_keyboardState, Player* p_player)
{
	if (p_keyboardState[SDL_SCANCODE_LEFT] || p_keyboardState[SDL_SCANCODE_A])
		if (p_player->entityBody->hitbox.x > 0)
			p_player->entityBody->hitbox.x -= PLAYER_X_SPEED;

	if (p_keyboardState[SDL_SCANCODE_RIGHT] || p_keyboardState[SDL_SCANCODE_D])
		if (p_player->entityBody->hitbox.x + p_player->entityBody->hitbox.w < 1200)
			p_player->entityBody->hitbox.x += PLAYER_X_SPEED;
}

void player_destroy(Player* p_player)
{
	entitybody_destroy(p_player->entityBody);
	free(p_player);
}