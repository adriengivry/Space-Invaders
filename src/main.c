#include <stdlib.h>
#include <stdio.h>
#include "Game.h"

int SDL_main(int* argc, char** argv)
{
	Game game;
	
	game_init_all(&game);
	game_update(&game);
	game_close(&game);

	return EXIT_SUCCESS;
}