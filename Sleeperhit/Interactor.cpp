#include "Interactor.h"

Interactor::Interactor(float x, float y, Game* game)
	: Actor("", x, y, 20, 20, game) {

}

void Interactor::update() {
	// Código usado en pruebas en su momento
	// Ahora no tiene uso
	if (toggle) {
		texture = game->getTexture("");
		toggle = false;
		if (interactCd > 0) {
			interactCd--;
		}
	}
	else
		texture = game->getTexture("");
}