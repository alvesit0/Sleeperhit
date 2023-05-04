#include "MenuLayer.h"

MenuLayer::MenuLayer(Game* game)
	: Layer(game) {
	init();
	gamePad = SDL_GameControllerOpen(0);
}

void MenuLayer::init() {
	// Fondo normal, sin velocidad
	background = new Background("res/sprite/menu/menu_background.png", WIDTH * 0.5, HEIGHT * 0.5, game);

	newGame = new MenuItem("res/sprite/menu/nueva.png", 250, 120, game, "res/sprite/menu/nueva_sel.png");
	resumeItem = new MenuItem("res/sprite/menu/continuar.png", 250, 145, game, "res/sprite/menu/continuar_sel.png");
	exit = new MenuItem("res/sprite/menu/salir.png", 250, 170, game, "res/sprite/menu/salir_sel.png");
	selectedPosition = 0;

	audioBackground = Audio::createAudio("res/sound/music/it_was_futile.wav", true);
	audioBackground->play();
}

void MenuLayer::resume() {
	audioBackground = Audio::createAudio("res/sound/music/it_was_futile.wav", true);
	audioBackground->play();
}

void MenuLayer::update() {
	switch (selectedPosition) {
	case 0:
		newGame->texture = game->getTexture(newGame->selectedFilename);
		break;
	case 1:
		resumeItem->texture = game->getTexture(resumeItem->selectedFilename);
		break;
	case 2:
		exit->texture = game->getTexture(exit->selectedFilename);
	}
}

void MenuLayer::draw() {
	background->draw();

	newGame->draw();
	resumeItem->draw();
	exit->draw();

	SDL_RenderPresent(game->renderer); // Renderiza NO PUEDE FALTAR
}

void MenuLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}
		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar teclas
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		// No hay control por ratón
		/*if (game->input == game->inputMouse) {
			mouseToControls(event);
		}*/
	}

	//procesar controles
	if (controlContinue) {
		switch (selectedPosition) {
		case 0:
			acceptSound = Audio::createAudio("res/sound/fx/menu_accept.wav", false);
			acceptSound->play();
			game->layer = game->gameLayer;
			game->layer->resume();
			break;
		// La funcionalidad de continuar partida aún no ha sido implementada
		case 1:
			denySound = Audio::createAudio("res/sound/fx/menu_deny.wav", false);
			denySound->play();
			break;
		case 2:
			game->loopActive = false;
			break;
		}
		// Cambia la capa
		controlContinue = false;
	}
}

void MenuLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE: // derecha
			game->loopActive = false;
			break;
		case SDLK_s:
			changeMenuPosition(1);
			break;
		case SDLK_w:
			changeMenuPosition(-1);
			break;
		case SDLK_F4:
			game->scale();
			break;
		case SDLK_SPACE: // activar
			controlContinue = true;
			break;
		}
	}
}

void MenuLayer::changeMenuPosition(int value) {
	int temp = this->selectedPosition + value;
	if (temp > 2) selectedPosition = 0;
	else if (temp < 0) selectedPosition = 2;
	else selectedPosition = temp;

	newGame->texture = game->getTexture(newGame->defaultFilename);

	resumeItem->texture = game->getTexture(resumeItem->defaultFilename);

	exit->texture = game->getTexture(exit->defaultFilename);

	moveSound = Audio::createAudio("res/sound/fx/menu_select.wav", false);
	moveSound->play();
}

void MenuLayer::gamePadToControls(SDL_Event event) {
	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	int stickY = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTY);

	if (buttonA) {
		controlContinue = true;
	}
	if (stickY > 7000) { // abajo
		changeMenuPosition(-1);
	}
	else if (stickY < -7000) { // aarriba
		changeMenuPosition(1);
	}

}



