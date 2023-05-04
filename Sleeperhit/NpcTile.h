#pragma once

#include "EventTile.h"

class NpcTile : public EventTile
{
public:
	NpcTile(float x, float y, Game* game, int zoneTilePos);
	void interact() override;
	list<string> split(string str, char divider);
	string get(list<string> l, int pos);
	float xMoved;
	float yMoved;
};

