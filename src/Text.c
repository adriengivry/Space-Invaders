#include "Text.h"

Text* text_create(char* p_value, int p_x, int p_y)
{
	Text* text = (Text*)malloc(sizeof(Text));
	
	text->value = (char*)malloc(sizeof(char));
	string_copy(p_value, &text->value);

	text->surface = NULL;
	text->texture = NULL;

	text->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	text->rect->x = p_x;
	text->rect->y = p_y;

	return text;
}

void text_update(Text* p_text, TTF_Font* p_font, SDL_Color p_fontColor, char* p_value)
{
	if (p_value)
	{
		char* newString = string_concatenate(p_text->value, p_value);
		p_text->surface = TTF_RenderText_Blended(p_font, newString, p_fontColor);
	}
	else
	{
		p_text->surface = TTF_RenderText_Blended(p_font, p_text->value, p_fontColor);
	}

	p_text->rect->w = p_text->surface->w;
	p_text->rect->h = p_text->surface->h;
}


void text_destroy(Text* p_text)
{
	free(p_text->value);
	SDL_FreeSurface(p_text->surface);
	SDL_DestroyTexture(p_text->texture);
	free(p_text->rect);
	free(p_text);
}