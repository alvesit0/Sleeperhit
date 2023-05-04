#pragma once

#include "Actor.h"

#include "MovementEvent.h"
#include "AnimationEvent.h"
#include "TextBoxEvent.h"
#include "EndEvent.h"
#include "CombatEvent.h"
#include "ZoneEvent.h"

#include "Npc.h"

class EventLoader
{
public:
	EventLoader(string id, Npc* npc, Game* game);
	list<string> split(string str, char divider);
	string getString(list<string> l, int pos);
	Event* getEvent(list<Event*> l, int pos);
	Event* getCurrentEvent();
	void loadEvents();
	list<Event*> events;
	Event* currentEvent;
	Game* game;
	void update();
	void next();
	void draw();
	string dataString;
	bool inEvent;
	bool readyForNextEvent;
	int currentEventPos;
	list<Event*>::iterator it;
	Npc* npc;
};

