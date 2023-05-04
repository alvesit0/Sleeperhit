#include "CombatEvent.h"

CombatEvent::CombatEvent(string evt, Npc* npc, Game* game) : Event("", npc, game) {
	this->game = game;
	this->evt = evt;
	toPlay = new Actor("", WIDTH/2, HEIGHT/2, WIDTH, HEIGHT, game);
	this->isFinished = false;
	counter = 30;
	start = Audio::createAudio("res/sound/fx/combat_start.wav", false);
	silentBackground = Audio::createAudio("res/sound/fx/silence.wav", true);
}

void CombatEvent::update() { 
	if (counter == 0) {
		BeatmapLayer* l = new BeatmapLayer(game, evt);
		l->opacityCounter = 0;
		game->combatLayer = l;
		game->layer = game->combatLayer;
	}
	if (created) {
		start->play();
		silentBackground->play();
		created = false;
	}
}

void CombatEvent::draw() { 

	if (counter > 0 && counter%3 == 0 && flag) {
		toPlay->texture = game->getTexture("res/black_screen.png");
		flag = false;
	}
	else {
		toPlay->texture = game->getTexture("");
		flag = true;
	}
	counter--;
	toPlay->draw();
}

void CombatEvent::next() {
	
}

list<string> CombatEvent::split(string str, char divider) {
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

string CombatEvent::get(list<string> l, int pos) {
	list<string>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}