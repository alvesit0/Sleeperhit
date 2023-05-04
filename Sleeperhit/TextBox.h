#pragma once

#include "Actor.h"
#include "Text.h"
#include "Animation.h"
#include "Audio.h"

#include <list>
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String

class TextBox : public Actor
{
public:
	TextBox(string t1, string t2, string t3, char portrait, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
	void update();
	void fillLine1();
	void fillLine2();
	void fillLine3();
	void drawPortrait();
	list<char> stringToChars(string str);

	Actor* portrait;
	Text* line1;
	Text* line2;
	Text* line3;

	char p;
	list<char> toIterator1;
	list<char> toIterator2;
	list<char> toIterator3;

	list<char>::iterator it1;
	list<char>::iterator it2;
	list<char>::iterator it3;

	bool filled1;
	bool filled2;
	bool filled3;

	Audio* keyAudio;
};

