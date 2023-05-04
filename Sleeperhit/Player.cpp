#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 32, 37, game) {

	orientation = game->orientationDown;
	state = game->stateMoving;

	aIdleRight = new Animation("res/sprite/lili/lili_stand_right.png", width, height,
		32, 37, 8, 1, true, game);
	aIdleLeft = new Animation("res/sprite/lili/lili_stand_left.png", width, height,
		32, 37, 8, 1, true, game);
	aIdleUp = new Animation("res/sprite/lili/lili_stand_up.png", width, height,
		32, 37, 8, 1, true, game);
	aIdleDown = new Animation("res/sprite/lili/lili_stand_down.png", width, height,
		32, 37, 8, 1, true, game);

	aWalkingRight = new Animation("res/sprite/lili/lili_walk_right.png", width, height,
		128, 37, 4, 4, true, game);
	aWalkingLeft = new Animation("res/sprite/lili/lili_walk_left.png", width, height,
		128, 37, 4, 4, true, game);
	aWalkingUp = new Animation("res/sprite/lili/lili_walk_up.png", width, height,
		128, 37, 4, 4, true, game);
	aWalkingDown = new Animation("res/sprite/lili/lili_walk_down.png", width, height,
		128, 37, 4, 4, true, game);

	interactor = new Interactor(x, y, game);
	animation = aIdleDown;
}


void Player::update() {
	bool endAnimation = animation->update();

	// Establecer orientación
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}
	if (vy < 0) {
		orientation = game->orientationUp;
	}
	if (vy > 0) {
		orientation = game->orientationDown;
	}

	// Selección de animación basada en estados
	if (state == game->stateMoving) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aWalkingRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aWalkingLeft;
			}
		}
		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
		}
		if (vy != 0) {
			if (orientation == game->orientationUp) {
				animation = aWalkingUp;
			}
			if (orientation == game->orientationDown) {
				animation = aWalkingDown;
			}
		}
		if (vy == 0) {
			if (orientation == game->orientationUp) {
				animation = aIdleUp;
			}
			if (orientation == game->orientationDown) {
				animation = aIdleDown;
			}
		}
	}

	// Colocación del interactor
	// Derecha
	if (orientation == game->orientationRight) {
		interactor->x = x + 25;
		interactor->y = y;
	}
	// Izquierda 
	if (orientation == game->orientationLeft) {
		interactor->x = x - 25;
		interactor->y = y;
	}
	// Abajo
	if (orientation == game->orientationDown) {
		interactor->x = x;
		interactor->y = y + 25;
	}
	// Arriba
	if (orientation == game->orientationUp) {
		interactor->x = x;
		interactor->y = y - 25;
	}
	
}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

void Player::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

