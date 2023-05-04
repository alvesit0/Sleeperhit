
#include "ZoneEvent.h"

ZoneEvent::ZoneEvent(string evt, Npc* npc, Game* game) : Event("", npc, game) {
	this->isFinished = false;
	this->game = game;
	this->evt = evt;
}

void ZoneEvent::update() {
	if (game->layer->initialWait == false) {
		game->layer->fadeOut = true;
		game->layer->initialWait = true;
		game->layer->waitTimer = 20;
	}
	if (game->layer->waitTimer == 0) {
		game->currentLevel = stoi(get(split(evt, ';'), 1));
		game->layer->init();
		game->layer->resume();
		game->layer->fadeIn = true;
		game->layer->initialWait = true;
		this->isFinished = true;
	}
}

list<string> ZoneEvent::split(string str, char divider) {
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

string ZoneEvent::get(list<string> l, int pos) {
	list<string>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}