#include "Background.h"

void Background::start()
{
	bgTexture = loadTexture("gfx/background.png");

	x = 0;
	y = 0;
	width = 1136;
	height = 720;

	SDL_QueryTexture(bgTexture, NULL, NULL, &width, &height);
}

void Background::update()
{
}

void Background::draw()
{
	blitScale(bgTexture, x, y, &width, &height, 3);
}
