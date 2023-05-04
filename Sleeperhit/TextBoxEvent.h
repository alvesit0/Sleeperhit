#pragma once

#include "Event.h"
#include "TextBoxLoader.h"
#include "Npc.h"

class TextBoxEvent : public Event
{
public:
	TextBoxEvent(string evt, Npc* npc, Game* game);
	void update() override;
	void draw() override;
	void next() override;
	TextBoxLoader* loader;
};

