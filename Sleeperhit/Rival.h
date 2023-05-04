#pragma once

#include "Actor.h"
#include "Animation.h"

class Rival : public Actor
{
public:
	Rival(float x, float y, Game* game, list<string> data);
	void update();
	void draw();
	Animation* currentAnimation;
	Animation* start;
	Animation* loop;
	Animation* rage;
};

