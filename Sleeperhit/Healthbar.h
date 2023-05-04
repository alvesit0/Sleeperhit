#pragma once

#include "Actor.h"

class Healthbar : public Actor
{
public:
	Healthbar(float x, float y, Game* game);
	void update(int val);
};

