#include "Event.h"

Event::Event(string type, Npc* npc, Game* game) {
	this->type = type;
}

void Event::update() { }

void Event::draw() { }

void Event::next() { }