#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h" // incluir animacion 
#include "Interactor.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	int lifes = 3;
	int invulnerableTime = 0;
	bool onAir;
	int orientation;
	int state;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aIdleUp;
	Animation* aIdleDown;
	Animation* aWalkingRight;
	Animation* aWalkingLeft;
	Animation* aWalkingUp;
	Animation* aWalkingDown;
	Animation* animation; // Referencia a la animación mostrada
	Audio* audioShoot;
	int shootCadence = 30;
	int shootTime = 0;

	Interactor* interactor;
};

