#pragma once

#include "Actor.h"

class BeatmapEventActivator : public Actor
{
public:
	BeatmapEventActivator(string filename, float x, float y, float value, Game* game);
	void update(float addedY);
	float speedValue;
};

