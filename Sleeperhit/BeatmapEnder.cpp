#include "BeatmapEnder.h"

BeatmapEnder::BeatmapEnder(float x, float y, Game* game)
	: Actor("", x, y, 15, 15, game)
{

}

void BeatmapEnder::update(float addedY) {
	this->y += addedY;
}
