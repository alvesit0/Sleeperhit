#include "TextBoxEvent.h"

TextBoxEvent::TextBoxEvent(string evt, Npc* npc, Game* game) : Event("", npc, game) {
	loader = new TextBoxLoader(evt, game);
}

void TextBoxEvent::update() {
	loader->update();
	this->isFinished = !loader->inTextBox;
	if (!loader->inTextBox) loader = NULL;
}

void TextBoxEvent::draw() {
	loader->draw();
}

void TextBoxEvent::next() {
	loader->next();
}