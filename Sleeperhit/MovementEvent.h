#pragma once

#include "Event.h"
#include "Npc.h"

class MovementEvent : public Event
{
public:
	MovementEvent(string evt, Npc* npc, Game* game);
	void update() override;
	void draw() override;
	void next() override;
	list<string> split(string str, char divider);
	string get(list<string> l, int pos);
	Animation* previousAnimation;
	bool flagAnim;
	Animation* toPlay;
	Npc* npc;
	Game* game;
	float finalX;
	float finalY;
	float movedX = 0;
	float movedY = 0;
	float speed;
};

