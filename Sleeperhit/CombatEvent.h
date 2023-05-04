#pragma once

#include "Event.h"
#include "BeatmapLayer.h"
#include "Audio.h"

class CombatEvent : public Event
{
public:
	CombatEvent(string evt, Npc* npc, Game* game);
	void update() override;
	void draw() override;
	void next() override;
	list<string> split(string str, char divider);
	string get(list<string> l, int pos);
	Actor* toPlay;
	Game* game;
	int counter;
	bool flag = false;
	bool created = true;
	Audio* start;
	Audio* silentBackground;
	string evt;
};

