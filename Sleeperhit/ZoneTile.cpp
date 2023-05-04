#include "ZoneTile.h"

ZoneTile::ZoneTile(float x, float y, Game* game, int zoneTilePos)
	: EventTile(x, y, game) 
{
	dataString = getDataString(zoneTilePos);
}

void ZoneTile::interact() {
	if (game->layer->initialWait == false) {
		game->layer->fadeOut = true;
		game->layer->initialWait = true;
		game->layer->waitTimer = 20;
	}
	if (game->layer->waitTimer == 0) {
		game->currentLevel = stoi(get(split(dataString, '#'), 1));
		game->layer->init();
		game->layer->resume();
		game->layer->fadeIn = true;
		game->layer->initialWait = true;
	}
}

list<string> ZoneTile::split(string str, char divider) {
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

string ZoneTile::get(list<string> l, int pos) {
	list<string>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}