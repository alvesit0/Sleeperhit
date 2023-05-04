#include "Rival.h"

Rival::Rival(float x, float y, Game* game, list<string> data)
	: Actor("", x, y, 0, 0, game) {
	currentAnimation = new Animation(
		"res/sprite/battle/" + Actor::getString(data, 3) + "/" + Actor::getString(data, 3) + "_start_first.png",
		stof(Actor::getString(data, 4)), // Anchura de la animación
		stof(Actor::getString(data, 5)), // Altura de la animación
		stof(Actor::getString(data, 6)) * stof(Actor::getString(data, 4)), // Anchura de la imágen (frame * num de frames)
		stof(Actor::getString(data, 5)), // Altura de la imágen (misma que la del actor)
		2, // Frecuencia de actualización
		stoi(Actor::getString(data, 6)), // Frames totales
		true, game);
	start = new Animation(
		"res/sprite/battle/" + Actor::getString(data, 3) + "/" + Actor::getString(data, 3) + "_start.png",
		stof(Actor::getString(data, 4)), // Anchura de la animación
		stof(Actor::getString(data, 5)), // Altura de la animación
		stof(Actor::getString(data, 7)) * stof(Actor::getString(data, 4)), // Anchura de la imágen (frame * num de frames)
		stof(Actor::getString(data, 5)), // Altura de la imágen (misma que la del actor)
		2, // Frecuencia de actualización
		stoi(Actor::getString(data, 7)), // Frames totales
		false, game);
	loop = new Animation(
		"res/sprite/battle/" + Actor::getString(data, 3) + "/" + Actor::getString(data, 3) + "_loop.png",
		stof(Actor::getString(data, 4)), // Anchura de la animación
		stof(Actor::getString(data, 5)), // Altura de la animación
		stof(Actor::getString(data, 8)) * stof(Actor::getString(data, 4)), // Anchura de la imágen (frame * num de frames)
		stof(Actor::getString(data, 5)), // Altura de la imágen (misma que la del actor)
		2, // Frecuencia de actualización
		stoi(Actor::getString(data, 8)), // Frames totales
		true, game);
	rage = new Animation(
		"res/sprite/battle/" + Actor::getString(data, 3) + "/" + Actor::getString(data, 3) + "_rage.png",
		stof(Actor::getString(data, 4)), // Anchura de la animación
		stof(Actor::getString(data, 5)), // Altura de la animación
		stof(Actor::getString(data, 9)) * stof(Actor::getString(data, 4)), // Anchura de la imágen (frame * num de frames)
		stof(Actor::getString(data, 5)), // Altura de la imágen (misma que la del actor)
		1, // Frecuencia de actualización
		stoi(Actor::getString(data, 9)), // Frames totales
		true, game);
	this->width = width;
	this->height = height;
}

void Rival::update() {
	currentAnimation->update();
}

void Rival::draw() {
	currentAnimation->draw(x, y);
}