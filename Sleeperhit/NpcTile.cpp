#include "NpcTile.h"

NpcTile::NpcTile(float x, float y, Game* game, int zoneTilePos)
	: EventTile(x, y, game)
{
	dataString = getDataString(zoneTilePos);
	xMoved = stoi(get(split(dataString, '#'), 1));
	yMoved = stoi(get(split(dataString, '#'), 2));
}

void NpcTile::interact() {
	returnedActor = new Actor("", x + xMoved, y + yMoved, 24, 24, game);
}

list<string> NpcTile::split(string str, char divider) {
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

string NpcTile::get(list<string> l, int pos) {
	list<string>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}