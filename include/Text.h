#ifndef _TEXT_
#define _TEXT_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "string_copy.h"

typedef struct Text Text;
struct Text
{
	char* value;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect* rect;
};

Text* text_create(char* p_value, int p_x, int p_y);
void text_update(Text* p_text, TTF_Font* p_font, SDL_Color p_fontColor, char* p_value);
void text_destroy(Text* p_text);

#endif // _TEXT_