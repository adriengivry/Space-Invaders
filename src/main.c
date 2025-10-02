#include <stdlib.h>
#include <stdio.h>
#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	
	game_init_all(&game);
	game_update(&game);
	game_close(&game);

	return EXIT_SUCCESS;
}