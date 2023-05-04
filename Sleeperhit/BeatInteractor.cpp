#include "BeatInteractor.h"

BeatInteractor::BeatInteractor(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 15, 15, game) {
	this->filename = filename;
}

void BeatInteractor::update() {
	tapped = false;
	if (pressed) 
		texture = game->getTexture(filename);
	else 
		texture = game->getTexture("");
}