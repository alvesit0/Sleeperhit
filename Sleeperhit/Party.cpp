#include "Party.h"

Party::Party(float x, float y, Game* game, list<string> data)
	: Actor("", x, y, 0, 0, game) {
	currentAnimation = new Animation(
		"res/sprite/battle/" + Actor::getString(data, 10) + "/" + Actor::getString(data, 10) + "_start_first.png",
		stof(Actor::getString(data, 11)), // Anchura de la animación
		stof(Actor::getString(data, 12)), // Altura de la animación
		stof(Actor::getString(data, 13)) * stof(Actor::getString(data, 11)), // Anchura de la imágen (frame * num de frames)
		stof(Actor::getString(data, 12)), // Altura de la imágen (misma que la del actor)
		2, // Frecuencia de actualización
		stoi(Actor::getString(data, 13)), // Frames totales
		true, game);
	start = new Animation(
		"res/sprite/battle/" + Actor::getString(data, 10) + "/" + Actor::getString(data, 10) + "_start.png",
		stof(Actor::getString(data, 11)), // Anchura de la animación
		stof(Actor::getString(data, 12)), // Altura de la animación
		stof(Actor::getString(data, 14)) * stof(Actor::getString(data, 11)), // Anchura de la imágen (frame * num de frames)
		stof(Actor::getString(data, 12)), // Altura de la imágen (misma que la del actor)
		2, // Frecuencia de actualización
		stoi(Actor::getString(data, 14)), // Frames totales
		false, game);
	loop = new Animation(
		"res/sprite/battle/" + Actor::getString(data, 10) + "/" + Actor::getString(data, 10) + "_loop.png",
		stof(Actor::getString(data, 11)), // Anchura de la animación
		stof(Actor::getString(data, 12)), // Altura de la animación
		stof(Actor::getString(data, 15)) * stof(Actor::getString(data, 11)), // Anchura de la imágen (frame * num de frames)
		stof(Actor::getString(data, 12)), // Altura de la imágen (misma que la del actor)
		2, // Frecuencia de actualización
		stoi(Actor::getString(data, 15)), // Frames totales
		true, game);
	miss = new Animation(
		"res/sprite/battle/" + Actor::getString(data, 10) + "/" + Actor::getString(data, 10) + "_miss.png",
		stof(Actor::getString(data, 11)), // Anchura de la animación
		stof(Actor::getString(data, 12)), // Altura de la animación
		stof(Actor::getString(data, 16)) * stof(Actor::getString(data, 11)), // Anchura de la imágen (frame * num de frames)
		stof(Actor::getString(data, 12)), // Altura de la imágen (misma que la del actor)
		2, // Frecuencia de actualización
		stoi(Actor::getString(data, 16)), // Frames totales
		false, game);
	this->width = width;
	this->height = height;
}

void Party::update() {
	currentAnimation->update();
}

void Party::draw() {
	currentAnimation->draw(x, y);
}