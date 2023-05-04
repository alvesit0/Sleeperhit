#include "Healthbar.h"

Healthbar::Healthbar(float x, float y, Game* game)
	: Actor("res/sprite/beatmap/healthbar.png", x, y, 36, 2, game) {
}

void Healthbar::update(int val) {
	width = (int) ((36 * val) / 100);
}