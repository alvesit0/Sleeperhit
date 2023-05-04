#pragma once

#include "Game.h"
class Game;

class Layer
{
public:
	Layer(Game* game);
	virtual void init() {};
	virtual void resume() {};
	virtual void processControls() {};
	virtual void update() {};
	virtual void draw() {};

	// Variables para efectos en todas las capas
	bool initialWait;
	bool fadeIn = false;
	bool fadeOut = false;

	// Empleado en el "fade in" que se hace cada vez que se cambia de layer
	// para que visualmente no sea tan brusco
	int fadeInCounter = 255;

	// Empleado en el "fade out"
	int fadeOutCounter = 0;
	int waitTimer;

	bool endEvent;

	Game* game;
};
