#include "MovementEvent.h"

MovementEvent::MovementEvent(string evt, Npc* npc, Game* game) : Event("", npc, game) {
	this->game = game;
	this->npc = npc;
	previousAnimation = npc->animation;
	list<string> test = split(evt, ';');
	toPlay = new Animation(
		get(split(evt, ';'), 1), // Imagen
		stoi(get(split(evt, ';'), 2)), // Anchura del actor
		stoi(get(split(evt, ';'), 3)), // Altura del actor
		stoi(get(split(evt, ';'), 4)), // Anchura de la imagen
		stoi(get(split(evt, ';'), 5)), // Altura de la imagen
		stoi(get(split(evt, ';'), 6)), // Frecuencia
		stoi(get(split(evt, ';'), 7)), // Frames totales
		true, game);
	previousAnimation = new Animation(
		get(split(evt, ';'), 1), // Imagen
		stoi(get(split(evt, ';'), 2)), // Anchura del actor
		stoi(get(split(evt, ';'), 3)), // Altura del actor
		stoi(get(split(evt, ';'), 4)), // Anchura de la imagen
		stoi(get(split(evt, ';'), 5)), // Altura de la imagen
		stoi(get(split(evt, ';'), 6)), // Frecuencia
		stoi(get(split(evt, ';'), 7)), // Frames totales
		true, game);
	finalX = stoi(get(split(evt, ';'), 8));
	finalY = stoi(get(split(evt, ';'), 9));
	speed = stoi(get(split(evt, ';'), 10));
	this->isFinished = false;
	this->flagAnim = false;
}

void MovementEvent::update() {
	if (!flagAnim) {
		npc->animation = toPlay;
		flagAnim = true;
	}
	// Derecha
	if (movedX < finalX && finalX > 0) {
		movedX += speed;
		npc->moveX(speed);
	}
	// Izquierda
	if (movedX > finalX && finalX < 0) {
		movedX -= speed;
		npc->moveX((-1) * speed);
	}
	// Abajo
	if (movedY < finalY && finalY > 0) {
		movedY += speed;
		npc->moveY(speed);
	}
	// Arriba
	if (movedY > finalY && finalY < 0) {
		movedY -= speed;
		npc->moveY((-1)* speed);
	}
	if (movedY == finalY && movedX == finalX) {
		npc->animation = previousAnimation;
		isFinished = true;
	}
}

void MovementEvent::draw() { }

void MovementEvent::next() { }

list<string> MovementEvent::split(string str, char divider) {
	list<string> result;
	string strToAdd;
	for (char c : str) {
		if (c != divider)
			strToAdd = strToAdd + c;
		else {
			result.push_back(strToAdd);
			strToAdd = "";
		}
	}
	return result;
}

string MovementEvent::get(list<string> l, int pos) {
	list<string>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}