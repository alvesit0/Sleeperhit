#pragma once

#include "Event.h"
#include "Npc.h"

class EndEvent : public Event
{
public:
	EndEvent(string evt, Npc* npc, Game* game);
};

