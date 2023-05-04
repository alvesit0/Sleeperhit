#pragma once

#include "Game.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class Actor
{
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	~Actor();
	virtual void draw(float scrollX = 0, float scrollY = 0);
	bool isOverlap(Actor* actor);
	bool containsPoint(int pointX, int pointY); // contiene punto
	bool isInRender(float scrollX = 0, float scrollY = 0);
	list<string> split(string str, char divider);
	string getString(list<string> l, int pos);
	bool collisionDown;
	bool outRight;
	bool outLeft;

	bool clicked; // Está pulsado
	SDL_Texture* texture;
	int x;
	int y;
	float vx;
	float vy;
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	string fileName;
	Game* game; // referencia al juego
};

