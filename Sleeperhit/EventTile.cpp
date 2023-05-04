#include "EventTile.h"

EventTile::EventTile(float x, float y, Game* game)
	: Actor("", x, y, 16, 16, game) {

}

void EventTile::interact() {}

string EventTile::getDataString(int tilePos) {
	string line, p;
	bool flag = false;
	int pos = 0;
	ifstream streamFile("res/tiles" + to_string(game->currentLevel) + ".txt");
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de texto" << endl;
		return NULL;
	}
	else {
		// Por línea
		while (getline(streamFile, line)) {
			if (pos == tilePos) {
				dataString = line;
			}
			pos++;
		}
	}
	streamFile.close();
	this->dataString = dataString;
	return dataString;
}

list<string> EventTile::split(string str, char divider) {
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

string EventTile::get(list<string> l, int pos) {
	list<string>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}