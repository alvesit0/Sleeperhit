#pragma once

#include "Event.h"
#include "Animation.h"
#include "Npc.h"

class AnimationEvent : public Event
{
public:
	AnimationEvent(string evt, Npc* npc, Game* game);
	void update() override;
	void draw() override;
	void next() override;
	list<string> split(string str, char divider);
	string get(list<string> l, int pos);
	bool flagAnim;
	Animation* toPlay;
	Animation* previousAnimation;
	Npc* npc;
	Game* game;
};

