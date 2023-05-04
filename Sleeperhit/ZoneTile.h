#pragma once

#include "EventTile.h"

class ZoneTile : public EventTile
{
public:
	ZoneTile(float x, float y, Game* game, int zoneTilePos);
	void interact() override;
	list<string> split(string str, char divider);
	string get(list<string> l, int pos);
};

