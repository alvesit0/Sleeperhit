#pragma once

#include "Actor.h"

class BeatInteractor : public Actor
{
public:
	BeatInteractor(string filename, float x, float y, Game* game);
	void update();
	bool tapped = false;
	bool pressed = false;
	string filename;
};

