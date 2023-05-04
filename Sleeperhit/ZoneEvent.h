#pragma once

#include "Event.h"
#include "Npc.h"

class ZoneEvent : public Event
{
public:
	ZoneEvent(string evt, Npc* npc, Game* game);
	void update() override;
	list<string> split(string str, char divider);
	string get(list<string> l, int pos);
	Game* game;
	string evt;
};

