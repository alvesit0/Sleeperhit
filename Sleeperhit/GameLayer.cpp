#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	gamePad = SDL_GameControllerOpen(0);
	init();
	initialWait = true;
}

void GameLayer::init() {
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);

	space = new Space(0);
	scrollX = 0;
	scrollY = 0;
	tiles.clear();

	blackScreen = new Actor("res/black_screen.png", WIDTH * 0.5, HEIGHT * 0.5, 320, 240, game);
	
	background = new Background("res/sprite/map/base_background.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	activeMap = new Actor("res/sprite/map/bedroom_day.png", WIDTH * 0.5, HEIGHT * 0.5, 216, 197, game);

	textPrealpha = new Text("pre-alpha", WIDTH * 0.75, HEIGHT * 0.05, game);

	enemies.clear(); // Vaciar por si reiniciamos el juego
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	npcs.clear();
	eventTiles.clear();

	npcPos = 0;
	eventTilePos = 0;
	loadMap("res/map" + to_string(game->currentLevel) + ".txt");
}

void GameLayer::resume() {
	fadeIn = true;
	if (initialWait) {
		waitTimer = 50;
		initialWait = false;
	}
	audioBackground = Audio::createAudio(songName, true);
	audioBackground->play();
	if (currentEvent != NULL && !endEvent) {
		currentEvent->getCurrentEvent()->isFinished = true;
		currentEvent->next();
	}
	else if (currentEvent != NULL && endEvent) {
		currentEvent = NULL;
	}
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	int npcPos = 0;
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Primera línea: Contiene metadatos del mapa
		getline(streamFile, line);
		list<string> metadata = split(line, '!');
		songName = getString(metadata, 1);
		activeMap = new Actor(getString(metadata, 2) + ".png", stoi(getString(metadata, 3)), stoi(getString(metadata, 4)), stoi(getString(metadata, 5)), stoi(getString(metadata, 6)), game);
		topMap = new Actor(getString(metadata, 2) + "_top.png", stoi(getString(metadata, 3)), stoi(getString(metadata, 4)), stoi(getString(metadata, 5)), stoi(getString(metadata, 6)), game);
		background = new Background(getString(metadata, 7), WIDTH * 0.5, HEIGHT * 0.5, -1, game);
		audioBackground = Audio::createAudio(songName, true);
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidthX = line.length() * 16; // Ancho del mapa en pixels
			mapWidthY = i * 16;
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 16 / 2 + j * 16; // x central
				float y = 16 + i * 16; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'N': {
		Tile* tile = new Tile("", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		Npc* npc = new Npc(x, y, game, npcPos, tile);
		npc->y = npc->y - npc->height / 2;
		npcs.push_back(npc);
		npcPos++;
		break;
	}
	case 'Z': {
		ZoneTile* tp = new ZoneTile(x, y, game, eventTilePos);
		// modificación para empezar a contar desde el suelo.
		tp->y = tp->y - tp->height / 2;
		eventTiles.push_back(tp);
		eventTilePos++;
		break;
	}
	case 'I': {
		NpcTile* nt = new NpcTile(x, y, game, eventTilePos);
		// modificación para empezar a contar desde el suelo.
		nt->y = nt->y - nt->height / 2;
		eventTiles.push_back(nt);
		eventTilePos++;
		break;
	}
	case 'E': {
		Enemy* enemy = new Enemy(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case '1': {
		player = new Player(x, y, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}
	case '#': {
		Tile* tile = new Tile("", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'M': {
		Tile* tile = new Tile("", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	}
}

void GameLayer::processControls() {
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
		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		// Procesar Mando
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}
	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}
}

void GameLayer::update() {

	// ***** Efectos *****
	// Fade in
	if (fadeIn) {
		if (fadeInCounter > 0) {
			changeOpacity(blackScreen, fadeInCounter);
			blackScreen->texture = game->getTexture("res/black_screen_2.png");
			fadeInCounter -= 5;
		}
		else {
			changeOpacity(blackScreen, 0);
			fadeIn = false;
			fadeInCounter = 255;
		}
	}

	// Fade out
	if (fadeOut) {
		if (fadeOutCounter < 255) {
			fadeOutCounter += 15;
			changeOpacity(blackScreen, fadeOutCounter);
			blackScreen->texture = game->getTexture("res/black_screen_2.png");
		}
		else {
			changeOpacity(blackScreen, 255);
			fadeOut = false;
			fadeOutCounter = 0;
		}
	}

	// Espera al fade in o al fade out
	if (waitTimer > 0) {
		waitTimer--;
		return;
	}

	// Modo de pausa
	if (pause) {
		return;
	}

	if (currentEvent != NULL && currentEvent->inEvent) {
		currentEvent->update();
	}

	// Si se está en un evento, parar el juego hasta que acabe
	if (currentEvent != NULL && currentEvent->inEvent) {
		// Tiempo de reposo para interactuar
		player->interactor->update();
		for (auto const& npc : npcs) {
			npc->update();
		}
		return;
	}

	space->update();
	background->update();
	player->update();
	for (auto const& npc : npcs) {
		npc->update();
	}
	
	// Colisiones

	// Interacción Jugador - NPC

	for (auto const& npc : npcs) {
		if (player->interactor->toggle && player->interactor->isOverlap(npc)) {
			this->currentNpc = npc;
			this->currentEvent = new EventLoader(npc->getString(), npc, game);
		}
	}
	player->interactor->update();

	// Colisión jugador - tile de activación
	for (auto const& et : eventTiles) {
		if (player->isOverlap(et)) {
			et->interact();
			break;
		}
	}

	// Colisión jugador - tile que activa NPC
	for (auto const& et : eventTiles) {
		for (auto const& npc : npcs) {
			if (et->returnedActor != NULL && et->returnedActor->isOverlap(npc)) {
				this->currentNpc = npc;
				this->currentEvent = new EventLoader(npc->getString(), npc, game);
			}
		}
	}

	
	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	calculateScroll();

	background->draw(scrollX, scrollY);
	activeMap->draw(scrollX, scrollY);
	for (auto const& tile : tiles) {
		tile->draw(scrollX, scrollY);
	}
	for (auto const& et : eventTiles) {
		et->draw(scrollX, scrollY);
		if (et->returnedActor != NULL) {
			et->returnedActor->draw(scrollX, scrollY);
		}
	}

	player->draw(scrollX, scrollY); 
	player->interactor->draw(scrollX, scrollY);
	topMap->draw(scrollX, scrollY);
	for (auto const& npc : npcs) {
		npc->draw(scrollX, scrollY);
	}
	if (currentEvent != NULL && currentEvent->inEvent) {
		currentEvent->draw();
	}

	blackScreen->draw();

	// Este juego no tiene contoles por mouse
	// HUD
	//if (game->input == game->inputMouse) {
	//	buttonJump->draw(); // NO TIENEN SCROLL, POSICION FIJA
	//	buttonShoot->draw(); // NO TIENEN SCROLL, POSICION FIJA
	//	pad->draw(); // NO TIENEN SCROLL, POSICION FIJA
	//}

	SDL_RenderPresent(game->renderer); // Renderiza
}

// Métodos empleado en los efectos de fade in y fade out
void GameLayer::changeOpacity(Actor* a, float value) {
	
	if (fadeIn) {
		SDL_SetTextureBlendMode(a->texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(a->texture, value);
	}
	else {
		SDL_SetTextureBlendMode(a->texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(a->texture, value);
	}	
}

void GameLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	bool buttonB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_B);
	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	// cout << "botones:" << buttonA << "," << buttonB << endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	// cout << "stickX" << stickX << endl;
	int stickY = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTY);
	// cout << "stickY" << stickX << endl;

	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	if (stickX > 7000) { // derecha
		controlMoveX = 1;
		player->orientation = game->orientationRight;
	}
	else if (stickX < -7000) { // izquierda
		controlMoveX = -1;
		player->orientation = game->orientationLeft;
	}
	else {
		controlMoveX = 0;
	}

	if (stickY > 7000) { // abajo
		controlMoveY = 1;
		player->orientation = game->orientationDown;
	}
	else if (stickY < -7000) { // arriba
		controlMoveY = -1;
		player->orientation = game->orientationUp;
	}
	else {
		controlMoveY = 0;
	}

	if (buttonA || buttonB) {
		if (currentEvent != NULL && currentEvent->inEvent) {
			currentEvent->next();
		}
		else {
			controlInteract = true;
			player->interactor->toggle = true;
		}
	}
	else controlInteract = false;

}

void GameLayer::calculateScroll() {
	// limite izquierda
	if (player->x > WIDTH * 0.4) {
		if (player->x - scrollX < WIDTH * 0.4) {
			scrollX = player->x - WIDTH * 0.4;
		}
	}

	// limite derecha
	if (player->x < mapWidthX - WIDTH * 0.4) {
		if (player->x - scrollX > WIDTH * 0.6) {
			scrollX = player->x - WIDTH * 0.6;
		}
	}

	// limite arriba
	if (player->y < mapWidthY - HEIGHT * 0.4) {
		if (player->y - scrollY > HEIGHT * 0.6) {
			scrollY = player->y - HEIGHT * 0.6;
		}
	}

	// limite abajo
	if (player->y > HEIGHT * 0.4) {
		if (player->y - scrollY < HEIGHT * 0.4) {
			scrollY = player->y - HEIGHT * 0.4;
		}
	}
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_F4:
			game->scale();
			break;
		case SDLK_RIGHT:
		case SDLK_d: // derecha
			controlMoveX = 1;
			player->orientation = game->orientationRight;
			break;
		case SDLK_LEFT:
		case SDLK_a: // izquierda
			controlMoveX = -1;
			player->orientation = game->orientationLeft;
			break;
		case SDLK_UP:
		case SDLK_w: // arriba
			controlMoveY = -1;
			player->orientation = game->orientationUp;
			break;
		case SDLK_DOWN:
		case SDLK_s: // abajo
			controlMoveY = 1;
			player->orientation = game->orientationDown;
			break;
		case SDLK_RETURN:
		case SDLK_SPACE: // dispara
			if (currentEvent != NULL && currentEvent->inEvent) {
				currentEvent->next();
			}
			else {
				controlInteract = true;
				player->interactor->toggle = true;
			}
			break;
		//case SDLK_p: // pausa
		//	if (pause == true) pause = false;
		//	else pause = true;
		//	break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_RIGHT:
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_LEFT:
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_UP:
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_DOWN:
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_RETURN:
		case SDLK_SPACE: // dispara
			controlInteract = false;
			break;
		}

	}

}

list<string> GameLayer::split(string str, char divider) {
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

string GameLayer::getString(list<string> l, int pos) {
	list<string>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}