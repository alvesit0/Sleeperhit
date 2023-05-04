#include "EventLoader.h"

EventLoader::EventLoader(string dataString, Npc* npc, Game* game) {
	this->game = game;
	this->dataString = dataString;
	this->npc = npc;

	loadEvents();
	currentEvent = getEvent(events, 0);
	it = events.begin();
	inEvent = true;
}

void EventLoader::update() {
	if (getCurrentEvent() != NULL) getCurrentEvent()->update();

	if (getCurrentEvent() != NULL && getCurrentEvent()->type != "-" && getCurrentEvent()->isFinished) next();
}

void EventLoader::draw() {
	if (getCurrentEvent() != NULL) getCurrentEvent()->draw();
}

Event* EventLoader::getCurrentEvent() {
	Event* result;
	if (readyForNextEvent && *it != *(--events.end())) {
		++it;
	}
	result = *it;

	readyForNextEvent = false;
	return result;
}

  void EventLoader::next() {
	if (*it == *(--events.end())) {
		inEvent = false;
	}
	if (getCurrentEvent()->isFinished) {
		readyForNextEvent = true;
	}
	else {
		getCurrentEvent()->next();
	}
}

void EventLoader::loadEvents() {
	list<string> toSplit = split(dataString, '#');
	for (string evt : toSplit) {
		switch (evt[0]) {
			case '-': {
				Event* e = new TextBoxEvent(evt, npc, game);
				events.push_back(e);
				break;
			}
			case '&': {
				Event* e = new MovementEvent(evt, npc, game);
				events.push_back(e);
				break;
			}
			case '*': {
				Event* e = new AnimationEvent(evt, npc, game);
				events.push_back(e);
				break;
			}
			case 'E': {
				Event* e = new EndEvent(evt, npc, game);
				events.push_back(e);
				break;
			}
			case '_': {
				Event* e = new CombatEvent(evt, npc, game);
				events.push_back(e);
				break;
			}
			case '$': {
				Event* e = new ZoneEvent(evt, npc, game);
				events.push_back(e);
				break;
			}
		}
	}
}

list<string> EventLoader::split(string str, char divider) {
	list<string> result;
	string strToAdd;
	for (char c : str) {
		if (c != divider)
			strToAdd = strToAdd + c;
		else {
			result.push_back(strToAdd);
			strToAdd = "";
		}
	}
	return result;
}

string EventLoader::getString(list<string> l, int pos) {
	list<string>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}

Event* EventLoader::getEvent(list<Event*> l, int pos) {
	list<Event*>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}