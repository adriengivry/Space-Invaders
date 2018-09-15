#ifndef _USERINTERFACE_
#define _USERINTERFACE_

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include "Window.h"
#include "Text.h"
#include "int_to_alpha.h"

typedef struct UserInterface UserInterface;
struct UserInterface
{
	TTF_Font* font;
	SDL_Color fontColor;

	Text* stage;
	Text* score;
	Text* life;

	Text* pause;
	Text* gameOver;
	Text* menu;
};

UserInterface* userinterface_create();
void userinterface_destroy(UserInterface* p_userInterface);

#endif // _USERINTERFACE_