#pragma once

#include "Actor.h"
#include "Animation.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class Party : public Actor
{
public:
	Party(float x, float y, Game* game, list<string> data);
	void draw();
	void update();
	Animation* currentAnimation;
	Animation* start;
	Animation* loop;
	Animation* miss;
};

