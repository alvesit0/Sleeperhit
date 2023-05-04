#include "Npc.h"

using namespace std;

Npc::Npc(float x, float y, Game* game, int npcPos, Tile* collisionTile)
	: Actor("", x, y, 0, 0, game) {
	width = stoi(get(split(getDataString(npcPos), '#'), 2));
	height = stoi(get(split(getDataString(npcPos), '#'), 3));
	animation = new Animation(get(split(getDataString(npcPos), '#'), 1), width, height,
		102, 38, 8, 1, true, game);
	this->npcPos = npcPos;
	this->collisionTile = collisionTile;
}

void Npc::update() {
	animation->update();
}

void Npc::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void Npc::moveX(float x) {
	this->x += x;
	this->collisionTile->x += x;
}

void Npc::moveY(float y) {
	this->y += y;
	this->collisionTile->y += y;
}

string Npc::getString() {
	return getDataString(npcPos);
}

string Npc::getCode() {
	return get(split(getDataString(npcPos), '#'), 0);
}

string Npc::getDataString(int npcPos) {
	string line, p;
	bool flag = false;
	int pos = 0;
	ifstream streamFile("res/npcs" + to_string(game->currentLevel) + ".txt");
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de texto" << endl;
		return NULL;
	}
	else {
		// Por línea
		while (getline(streamFile, line)) {
			if (pos == npcPos) {
				dataString = line;
			}
			pos++;
		}
	}
	streamFile.close();
	this->dataString = dataString;
	return dataString;
}

list<string> Npc::split(string str, char divider) {
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

string Npc::get(list<string> l, int pos) {
	list<string>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}