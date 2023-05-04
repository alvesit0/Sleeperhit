#pragma once

#include "Actor.h"

class Interactor : public Actor
{
public:
	Interactor(float x, float y, Game* game);
	void update();

	bool toggle = false;
	int interactCd = 0;
};

