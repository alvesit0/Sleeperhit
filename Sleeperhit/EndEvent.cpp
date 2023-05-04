#include "EndEvent.h"

EndEvent::EndEvent(string evt, Npc* npc, Game* game) : Event("", npc, game) {
	this->isFinished = true;
}

