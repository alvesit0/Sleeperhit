#pragma once

#include <list>
#include <stdio.h>
#include <string.h>
#include <cstring>

#include "Game.h"
#include "Npc.h"

class Event
{
public:
	Event(string type, Npc* npc, Game* game);
	virtual void update();
	virtual void draw();
	virtual void next();
	string type;
	Npc* npc;
	bool isFinished;
};

