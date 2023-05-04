#include "MenuItem.h"

MenuItem::MenuItem(string filename, float x, float y, Game* game, string selFilename)
	: Actor(filename, x, y, 100, 21, game)
{
	defaultFilename = filename;
	selectedFilename = selFilename;
}
