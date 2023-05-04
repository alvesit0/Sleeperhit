#pragma once

#include "Game.h"
#include "Actor.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class EventTile : public Actor
{
public:
	EventTile(float x, float y, Game* game);
	Actor* returnedActor;
	string getDataString(int npcPos);
	list<string> split(string str, char divider);
	string get(list<string> l, int pos);
	virtual void interact();
	string dataString;
};

