#include "BeatmapEventActivator.h"

BeatmapEventActivator::BeatmapEventActivator(string filename, float x, float y, float value, Game* game)
	: Actor(filename, x, y, 15, 15, game)
{
	this->speedValue = value;
}

void BeatmapEventActivator::update(float addedY) {
	this->y += addedY;
}
