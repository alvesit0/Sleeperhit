#pragma once

#include "TextBox.h"

#include <list>
#include <stdio.h>
#include <string.h>
#include <cstring>

class TextBoxLoader
{
public:
	TextBoxLoader(string textCode, Game* game);
	void loadTextFromFile();
	void update();
	void draw();
	void next();
	TextBox* getCurrentTextBox();
	list<TextBox*> textList;
	list<TextBox*>::iterator it;
	string textCode;
	Actor* box;
	Animation* arrow;
	Game* game;
	bool inTextBox = true;
	bool readyForNextText;
	int currentBox = 0;
	int finalBox;
};

