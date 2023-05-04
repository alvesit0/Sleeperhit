#pragma once

#include "Actor.h"

class BeatCircle : public Actor
{
public:
	BeatCircle(string filename, float x, float y, Game* game);
	void update(float addedY);
};

