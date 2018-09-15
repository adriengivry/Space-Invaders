#include "UserInterface.h"

UserInterface* userinterface_create()
{
	UserInterface* userInterface = (UserInterface*)malloc(sizeof(UserInterface));
	if (TTF_Init() == -1)
	{
		SDL_Log("Can't init TTF (%s)", TTF_GetError());
		return NULL;
	}

	userInterface->font = TTF_OpenFont("res/Pixeled.ttf", 25);
	userInterface->fontColor.r = 255;
	userInterface->fontColor.g = 255;
	userInterface->fontColor.b = 255;
	userInterface->fontColor.a = 150;

	userInterface->stage = text_create("Stage: ", 50, 0);
	userInterface->score = text_create("Score: ", 500, 0);
	userInterface->life = text_create("Life: ", 1000, 0);
	userInterface->pause = text_create("Pause", 500, 350);
	userInterface->gameOver = text_create("Game Over", 500, 350);
	userInterface->menu = text_create("Press [SPACE] to start playing", 250, 350);

	text_update(userInterface->pause, userInterface->font, userInterface->fontColor, NULL);
	text_update(userInterface->gameOver, userInterface->font, userInterface->fontColor, NULL);
	text_update(userInterface->menu, userInterface->font, userInterface->fontColor, NULL);

	return userInterface;
}

void userinterface_destroy(UserInterface* p_userInterface)
{
	text_destroy(p_userInterface->stage);
	text_destroy(p_userInterface->score);
	text_destroy(p_userInterface->life);
	text_destroy(p_userInterface->pause);
	text_destroy(p_userInterface->gameOver);
	text_destroy(p_userInterface->menu);

	TTF_CloseFont(p_userInterface->font);
	free(p_userInterface);
	p_userInterface = NULL;
}