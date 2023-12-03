#include "Grid.h"

void Grid::start()
{
	backdrop = loadTexture("gfx/BackgroundGrass.png");

	x = 0;
	y = 0;
}

void Grid::update()
{
}

void Grid::draw()
{
	blit(backdrop, x, y);
}