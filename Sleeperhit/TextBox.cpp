#include "TextBox.h"

TextBox::TextBox(string t1, string t2, string t3, char p, Game* game) 
	: Actor("res/textbox.png", WIDTH * 0.5, 210, 320, 60, game) {
	line1 = new Text(" ", WIDTH * 0.05, 190, game);
	line2 = new Text(" ", WIDTH * 0.05, 205, game);
	line3 = new Text(" ", WIDTH * 0.05, 220, game);
	portrait = new Actor("", WIDTH * 0.75, 80, 200, 200, game);
	this->p = p;
	toIterator1 = stringToChars(t1);
	toIterator2 = stringToChars(t2);
	toIterator3 = stringToChars(t3);
	it1 = toIterator1.begin();
	it2 = toIterator2.begin();
	it3 = toIterator3.begin();
	this->filled1 = false;
	this->filled2 = false;
	this->filled3 = false;
}

void TextBox::draw(float scrollX, float scrollY) {
	line1->draw();
	line2->draw();
	line3->draw();
	portrait->draw();
}

void TextBox::update() {
	drawPortrait();
	if (!filled1)
		fillLine1();
	else if (filled1 && !filled2)
		fillLine2();
	else if (filled2 && !filled3)
		fillLine3();
}

void TextBox::fillLine1() {
	if (*it1 != *(--toIterator1.end())) {
		line1->content += *it1;
		++it1;
		keyAudio->play();
	}
	else filled1 = true;
}

void TextBox::fillLine2() {
	if (*it2 != *(--toIterator2.end())) {
		line2->content += *it2;
		++it2;
		keyAudio->play();
	}
	else filled2 = true;
}

void TextBox::fillLine3() {
	if (*it3 != *(--toIterator3.end())) {
		line3->content += *it3;
		++it3;
		keyAudio->play();
	}
	else filled3 = true;
}

void TextBox::drawPortrait() {
	switch (p) {
	case 'N':
		portrait = new Actor("",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_default.wav", false);
		break;
	case 'W':
		portrait = new Actor("res/sprite/portrait/frog_portrait.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_default.wav", false);
		break;
	case 'L':
		portrait = new Actor("res/sprite/portrait/lili_portrait_neutral.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_lili.wav", false);
		break;
	case 'K':
		portrait = new Actor("res/sprite/portrait/lili_portrait_sleepy.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_lili.wav", false);
		break;
	case 'J':
		portrait = new Actor("res/sprite/portrait/lily_portrait_worry.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_lili.wav", false);
		break;
	case 'H':
		portrait = new Actor("res/sprite/portrait/lili_portrait_happy.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_lili.wav", false);
		break;
	case 'G':
		portrait = new Actor("res/sprite/portrait/glock_portrait_neutral.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_glock.wav", false);
		break;
	case 'F':
		portrait = new Actor("res/sprite/portrait/glock_portrait_sad.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_glock.wav", false);
		break;
	case 'D':
		portrait = new Actor("res/sprite/portrait/glock_portrait_smile.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_glock.wav", false);
		break;
	case 'Y':
		portrait = new Actor("res/sprite/portrait/yan_portrait.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_yan.wav", false);
		break;
	case 'M':
		portrait = new Actor("res/sprite/portrait/marcos_portrait_neutral.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_marcos.wav", false);
		break;
	case 'B':
		portrait = new Actor("res/sprite/portrait/marcos_portrait_smug.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_marcos.wav", false);
		break;
	case 'V':
		portrait = new Actor("res/sprite/portrait/marcos_portrait_yell.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_marcos.wav", false);
		break;
	case 'C':
		portrait = new Actor("res/sprite/portrait/marcos_portrait_angry.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_marcos.wav", false);
		break;
	case 'T':
		portrait = new Actor("res/sprite/portrait/takoto_portrait.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_default.wav", false);
		break;
	case 'S':
		portrait = new Actor("res/sprite/portrait/bakami_portrait.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_default.wav", false);
		break;
	case 'Q':
		portrait = new Actor("res/sprite/portrait/connie_portrait.png",
			WIDTH * 0.75, 80, 200, 200, game);
		keyAudio = Audio::createAudio("res/sound/fx/letter_default.wav", false);
		break;
	}
}

list<char> TextBox::stringToChars(string str) {
	list<char> result;
	for (char c : str) {
		result.push_back(c);
	}
	return result;
}