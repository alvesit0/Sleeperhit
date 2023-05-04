#pragma once

#include "Actor.h"

class MenuItem : public Actor
{
public:
	MenuItem(string filename, float x, float y, Game* game, string selFilename);
	string defaultFilename;
	string selectedFilename;
};

