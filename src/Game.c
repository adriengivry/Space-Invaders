#include "Game.h"

void game_tick(Game* p_game)
{
	if (p_game->gameInfo->gameState == STATE_PLAY)
	{
		if (p_game->gameEntities->player->life <= 0)
			p_game->gameInfo->gameState = STATE_GAMEOVER;

		player_move(p_game->gameInfo->keyboardState, p_game->gameEntities->player);

		if (!p_game->gameEntities->enemyProjectile)
		{
			int* x = malloc(sizeof(int));
			int* y = malloc(sizeof(int));
			if (enemy_find_pos(p_game->gameEntities->enemies, x, y))
			{
				p_game->gameEntities->enemyProjectile = projectile_create(*x, *y, p_game->window, 1);
			}
		}
		else
		{
			projectile_move(p_game->gameEntities->enemyProjectile);
			if (is_colliding(p_game->gameEntities->enemyProjectile->entityBody, p_game->gameEntities->player->entityBody))
			{
				--p_game->gameEntities->player->life;
				projectile_destroy(p_game->gameEntities->enemyProjectile);
				p_game->gameEntities->enemyProjectile = NULL;
				text_update(p_game->userInterface->life, p_game->userInterface->font, p_game->userInterface->fontColor, int_to_alpha(p_game->gameEntities->player->life));
			}

			if (p_game->gameEntities->enemyProjectile)
			{
				if (projectile_check(p_game->gameEntities->enemyProjectile))
				{
					projectile_destroy(p_game->gameEntities->enemyProjectile);
					p_game->gameEntities->enemyProjectile = NULL;
				}
			}

			if (p_game->gameEntities->projectile && p_game->gameEntities->enemyProjectile)
			{
				if (is_colliding(p_game->gameEntities->projectile->entityBody, p_game->gameEntities->enemyProjectile->entityBody))
				{
					projectile_destroy(p_game->gameEntities->enemyProjectile);
					projectile_destroy(p_game->gameEntities->projectile);
					p_game->gameEntities->enemyProjectile = NULL;
					p_game->gameEntities->projectile = NULL;
				}
			}
		}


		enemy_update(p_game->gameEntities->enemies);
	


		if (p_game->gameEntities->projectile)
		{
			projectile_move(p_game->gameEntities->projectile);

			for (int row = 0; row < 5; ++row)
			{
				for (int col = 0; col < 11; ++col)
				{
					if (p_game->gameEntities->projectile &&
						p_game->gameEntities->enemies[row][col]->isAlive &&
						is_colliding(p_game->gameEntities->enemies[row][col]->entityBody[0], p_game->gameEntities->projectile->entityBody))
					{
						p_game->gameEntities->enemies[row][col]->isAlive = false;
						projectile_destroy(p_game->gameEntities->projectile);
						p_game->gameEntities->projectile = NULL;
						p_game->gameInfo->score += p_game->gameEntities->enemies[row][col]->scoreValue;
						text_update(p_game->userInterface->score, p_game->userInterface->font, p_game->userInterface->fontColor, int_to_alpha(p_game->gameInfo->score));
					}
				}
			}

			if (p_game->gameEntities->projectile)
			{
				if (projectile_check(p_game->gameEntities->projectile))
				{
					projectile_destroy(p_game->gameEntities->projectile);
					p_game->gameEntities->projectile = NULL;
				}
			}
		}
		
		if (enemy_hit_a_wall(p_game->gameEntities->enemies))
		{
			p_game->gameInfo->enemiesDirection *= -1;
			enemy_move(p_game->gameEntities->enemies, 0, 1);
		}
		enemy_move(p_game->gameEntities->enemies, p_game->gameInfo->enemiesDirection, 0);

		if (enemy_won(p_game->gameEntities->enemies))
			p_game->gameInfo->gameState = STATE_GAMEOVER;

		if (enemy_all_dead(p_game->gameEntities->enemies))
			p_game->gameInfo->gameState = STATE_WON;
	}
}

void game_init_all(Game* p_game)
{
	srand(time(NULL));
	p_game->window = (Window*)malloc(sizeof(Window));
	if (!p_game->window)
		return;

	window_init(p_game->window);
	image_init();

	game_init(p_game, 0, 0);
}

void game_init(Game* p_game, int p_stage, int p_score)
{
	p_game->gameInfo = (GameInfo*)malloc(sizeof(GameInfo));
	p_game->gameEntities = (GameEntities*)malloc(sizeof(GameEntities));
	p_game->userInterface = userinterface_create();

	game_init_entities(p_game->gameEntities, p_game->window, p_stage);

	if (p_stage == 0)
		p_game->gameInfo->gameState = STATE_MENU;
	else
		p_game->gameInfo->gameState = STATE_PLAY;

	p_game->gameInfo->exit = false;
	p_game->gameInfo->enemiesDirection = 1;
	p_game->gameInfo->keyboardState = SDL_GetKeyboardState(NULL);
	p_game->gameInfo->stage = p_stage;
	p_game->gameInfo->score = p_score;

	text_update(p_game->userInterface->stage, p_game->userInterface->font, p_game->userInterface->fontColor, int_to_alpha(p_game->gameInfo->stage + 1));
	text_update(p_game->userInterface->score, p_game->userInterface->font, p_game->userInterface->fontColor, int_to_alpha(p_game->gameInfo->score));
	text_update(p_game->userInterface->life, p_game->userInterface->font, p_game->userInterface->fontColor, int_to_alpha(p_game->gameEntities->player->life));
}

void game_update(Game* p_game)
{
	while (!p_game->gameInfo->exit)
	{
		game_check_input(p_game);

		game_tick(p_game);

		game_display_entities(p_game);

		window_update(p_game->window);

		if (p_game->gameInfo->gameState == STATE_GAMEOVER)
		{
			SDL_Delay(3000);
			p_game->gameInfo->exit = true;
		}

		if (p_game->gameInfo->gameState == STATE_WON)
		{
			game_destroy(p_game);
			game_init(p_game, ++p_game->gameInfo->stage, p_game->gameInfo->score);
		}

		window_clear(p_game->window);
		
	}
}

void game_close(Game* p_game)
{
	game_destroy(p_game);
	window_close(p_game->window);
}

void game_destroy(Game* p_game)
{
	projectile_destroy(p_game->gameEntities->projectile);
	player_destroy(p_game->gameEntities->player);
	enemy_destroy_all(p_game->gameEntities->enemies);
	userinterface_destroy(p_game->userInterface);
}

void game_check_input(Game* p_game)
{
	int currentState = p_game->gameInfo->gameState;
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			p_game->gameInfo->exit = true;
			break;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				p_game->gameInfo->exit = true;
				break;
			case SDLK_SPACE:
				if (currentState == STATE_PLAY)
				{
					if (!p_game->gameEntities->projectile && p_game->gameInfo->gameState == STATE_PLAY)
					{
						int spawnX = p_game->gameEntities->player->entityBody->hitbox.x + p_game->gameEntities->player->entityBody->hitbox.w / 2 - 5;
						SDL_Log("Spawn projectile at %d", spawnX);
						p_game->gameEntities->projectile = projectile_create(spawnX, 680, p_game->window, -1);
					}
				}
				else if (currentState == STATE_MENU)
				{
					p_game->gameInfo->gameState = STATE_PLAY;
				}
				break;
			case SDLK_p:
				if (currentState == STATE_PAUSE || currentState == STATE_PLAY)
				{
					if (currentState == STATE_PAUSE)
						p_game->gameInfo->gameState = STATE_PLAY;
					else
						p_game->gameInfo->gameState = STATE_PAUSE;
				}
				break;
			case SDLK_t:
				p_game->gameInfo->gameState = STATE_WON;
				break;
			default:
				break;
			}
		}
	}

	SDL_PumpEvents();
}

void game_init_entities(GameEntities* p_gameEntities, Window* p_window, int p_stage)
{
	p_gameEntities->player = player_create(p_window);
	p_gameEntities->projectile = NULL;
	p_gameEntities->enemyProjectile = NULL;

	int posX = 20;
	int posY = 80;

	for (int row = 0; row < 5; ++row)
	{
		for (int col = 0; col < 11; ++col)
		{
			p_gameEntities->enemies[row][col] = enemy_create(p_window, posX, posY, p_stage, 30 - (5 * row));
			posX += 60;
		}
		posX = 20;
		posY += 50;
	}
}

void game_display_entities(Game* p_game)
{
	SDL_Renderer* renderer = p_game->window->rendererComponent;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect* rect;
	int gameState = p_game->gameInfo->gameState;

	if (gameState == STATE_GAMEOVER)
	{
		texture = SDL_CreateTextureFromSurface(renderer, p_game->userInterface->gameOver->surface);
		rect = p_game->userInterface->gameOver->rect;
		SDL_RenderCopy(renderer, texture, NULL, rect);
	}


	if (gameState == STATE_PLAY)
	{
		texture = p_game->gameEntities->player->entityBody->texture;
		rect = &p_game->gameEntities->player->entityBody->hitbox;
		SDL_RenderCopy(renderer, texture, NULL, rect);

		for (int row = 0; row < 5; ++row)
		{
			for (int col = 0; col < 11; ++col)
			{
				if (p_game->gameEntities->enemies[row][col]->isAlive)
				{
					int toRender = p_game->gameEntities->enemies[row][col]->toRender;
					texture = p_game->gameEntities->enemies[row][col]->entityBody[toRender]->texture;
					rect = &p_game->gameEntities->enemies[row][col]->entityBody[toRender]->hitbox;
					SDL_RenderCopy(renderer, texture, NULL, rect);
				}
			}
		}

		if (p_game->gameEntities->projectile)
		{
			texture = p_game->gameEntities->projectile->entityBody->texture;
			rect = &p_game->gameEntities->projectile->entityBody->hitbox;
			SDL_RenderCopy(renderer, texture, NULL, rect);
		}

		if (p_game->gameEntities->enemyProjectile)
		{
			texture = p_game->gameEntities->enemyProjectile->entityBody->texture;
			rect = &p_game->gameEntities->enemyProjectile->entityBody->hitbox;
			SDL_RenderCopy(renderer, texture, NULL, rect);
		}

		texture = SDL_CreateTextureFromSurface(renderer, p_game->userInterface->stage->surface);
		rect = p_game->userInterface->stage->rect;
		SDL_RenderCopy(renderer, texture, NULL, rect);
		SDL_DestroyTexture(texture);

		texture = SDL_CreateTextureFromSurface(renderer, p_game->userInterface->score->surface);
		rect = p_game->userInterface->score->rect;
		SDL_RenderCopy(renderer, texture, NULL, rect);
		SDL_DestroyTexture(texture);

		texture = SDL_CreateTextureFromSurface(renderer, p_game->userInterface->life->surface);
		rect = p_game->userInterface->life->rect;
		SDL_RenderCopy(renderer, texture, NULL, rect);
		SDL_DestroyTexture(texture);
	}
		
	if (gameState == STATE_PAUSE)
	{
		texture = SDL_CreateTextureFromSurface(renderer, p_game->userInterface->pause->surface);
		rect = p_game->userInterface->pause->rect;
		SDL_RenderCopy(renderer, texture, NULL, rect);
	}

	if (gameState == STATE_MENU)
	{
		texture = SDL_CreateTextureFromSurface(renderer, p_game->userInterface->menu->surface);
		rect = p_game->userInterface->menu->rect;
		SDL_RenderCopy(renderer, texture, NULL, rect);
	}
}