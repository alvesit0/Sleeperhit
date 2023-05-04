#include "BeatCircle.h"

BeatCircle::BeatCircle(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 15, 15, game) {

}

void BeatCircle::update(float addedY) {
	this->y += addedY;
}