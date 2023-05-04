#pragma once

#include "Actor.h"
#include "Game.h"
#include "Animation.h"
#include "Tile.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class Npc : public Actor
{
public:
	Npc(float x, float y, Game* game, int npcPos, Tile* collisionTile);
	string getDataString(int npcPos);
	void update();
	void draw(float scrollX = 0, float scrollY = 0) override;
	string getString();
	list<string> split(string str, char divider);
	string getCode();
	string get(list<string> l, int pos);
	string dataString;
	int npcPos;
	Animation* animation;
	int maxSoundTime = 40;
	int startSoundTime = 0;
	void moveX(float x);
	void moveY(float y);
	Tile* collisionTile;
};

