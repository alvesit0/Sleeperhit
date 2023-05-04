#pragma once

#include "Actor.h"

class BeatmapEnder : public Actor
{
public:
	BeatmapEnder(float x, float y, Game* game);
	void update(float addedY);
};

