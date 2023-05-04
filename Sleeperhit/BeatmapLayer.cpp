#include "BeatmapLayer.h"

BeatmapLayer::BeatmapLayer(Game* game, string code) : Layer(game) {
	this->code = code;
	init();
	gamePad = SDL_GameControllerOpen(0);
}

void BeatmapLayer::init() {
	background = new Background("res/black_screen.png", WIDTH / 2, HEIGHT / 2, game);
	lines = new Actor("res/sprite/beatmap/lines.png", WIDTH * 0.5, HEIGHT * 0.5, 90, 240, game);

	// ***** Variables empleadas en la pantalla al perder *****
	blackScreen = new Actor("res/black_screen_3.png", WIDTH * 0.5, HEIGHT * 0.5, 320, 240, game);
	liliLost = new Animation("res/sprite/battle/lili_death.png", // Imagen
		340, // Anchura del actor
		240, // Altura del actor
		10880, // Anchura de la imagen
		240, // Altura de la imagen
		2, // Frecuencia
		32, // Frames totales
		false, game);
	playTextLost = false;
	textLost = new Animation("res/sprite/battle/lili_death_text.png", // Imagen
		340, // Anchura del actor
		240, // Altura del actor
		2040, // Anchura de la imagen
		240, // Altura de la imagen
		8, // Frecuencia
		6, // Frames totales
		false, game);
	lostTimer = 45;
	startLostTimer = false;
	// **********************************************************

	// Puntuación
	pointsText = new Text("Puntos: " + to_string(points), WIDTH * 0.05, HEIGHT * 0.95, game);
	pointsText->font = TTF_OpenFont("res/teenytiny.ttf", 5);
	points = 0;
	
	deathBox = new Actor("", WIDTH * 0.75, HEIGHT, 320, 30, game);
	activatorBox = new Actor("", WIDTH * 0.7, HEIGHT * 0.92, 30, 30, game);

	// ****** Activadores de las notas ******
	lane1 = new BeatInteractor("res/sprite/beatmap/green_circle_toggle.png", 125, 195, game);
	lane2 = new BeatInteractor("res/sprite/beatmap/red_circle_toggle.png", 148, 195, game);
	lane3 = new BeatInteractor("res/sprite/beatmap/yellow_circle_toggle.png", 171, 195, game);
	lane4 = new BeatInteractor("res/sprite/beatmap/blue_circle_toggle.png", 194, 195, game);

	key1 = new Animation("res/sprite/beatmap/d_key.png", 32, 32, 160, 32, 1, 5, false, game);
	key2 = new Animation("res/sprite/beatmap/f_key.png", 32, 32, 160, 32, 1, 5, false, game);
	key3 = new Animation("res/sprite/beatmap/j_key.png", 32, 32, 160, 32, 1, 5, false, game);
	key4 = new Animation("res/sprite/beatmap/k_key.png", 32, 32, 160, 32, 1, 5, false, game);

	// Cooldowns para que no se puedan machacar las teclas y ganar
	lane1cd = 0;
	lane2cd = 0;
	lane3cd = 0;
	lane4cd = 0;
	// **************************************

	loadMap("res/" + code + ".txt");

	healthBorderPlayer = new Actor("res/sprite/beatmap/healthbar_border.png", WIDTH * 0.16, HEIGHT * 0.8, 49, 7, game);
	barPlayer = new Healthbar(WIDTH * 0.16 + 5, HEIGHT * 0.79 + 3, game);
	numPlayer = new Text(to_string(ph), WIDTH * 0.24 + 1, HEIGHT * 0.79, game);
	numPlayer->font = TTF_OpenFont("res/teenytiny.ttf", 5);

	healthBorderRival = new Actor("res/sprite/beatmap/healthbar_border.png", WIDTH * 0.8, HEIGHT * 0.8, 49, 7, game);
	barRival = new Healthbar(WIDTH * 0.8 + 5, HEIGHT * 0.79 + 3, game);
	numRival = new Text(to_string(rh), WIDTH * 0.88 + 1, HEIGHT * 0.79, game);
	numRival->font = TTF_OpenFont("res/teenytiny.ttf", 5);

	hitSound = Audio::createAudio("res/sound/fx/soft_slidertick.wav", false);

	ph = 100;
	rh = 100;
	timePassed = 0;
	startTimePassed = 300;
	playerStartAnimationPlayed = false;
	rivalStartAnimationPlayed = false;
	lost = false;

	soundPlayed = false;
	enragePlayed = false;
}

void BeatmapLayer::draw() {

	if (lost) {
		background->draw();

		liliLost->draw(WIDTH * 0.5, HEIGHT * 0.5);
		if (playTextLost)
			textLost->draw(WIDTH * 0.5, HEIGHT * 0.5);

		SDL_RenderPresent(game->renderer); // Renderiza NO PUEDE FALTAR
		return;
	}

	incrementOpacity(lines);

	background->draw();
	lines->draw();

	deathBox->draw();
	activatorBox->draw();

	lane1->draw();
	lane2->draw();
	lane3->draw();
	lane4->draw();

	// Puntos
	pointsText->content = "Puntos: " + to_string(points);
	pointsText->draw();

	// **** Jugador **** 
	barPlayer->draw();
	healthBorderPlayer->draw();
	numPlayer->content = to_string(ph);
	numPlayer->draw();

	// **** Rival ****
	barRival->draw();
	healthBorderRival->draw();
	numRival->content = to_string(rh);
	numRival->draw();

	player->draw();
	rival->draw();

	for (auto const& beat : beats)
		beat->draw();

	key1->draw(126, 215);
	key2->draw(149, 215);
	key3->draw(172, 215);
	key4->draw(195, 215);

	ender->draw();

	SDL_RenderPresent(game->renderer); // Renderiza NO PUEDE FALTAR
}

void BeatmapLayer::update() {

	// Si se pierde
	if (lost) {
		// Se para la música
		song = Audio::createAudio("res/sound/fx/silence.wav", true);
		song->play();
		// Se pone la pantalla en negro
		// Se pone la animación de lili perdiendo
		liliLost->update();
		if (liliLost->currentFrame == liliLost->totalFrames) {
			liliLost->currentFrame--;
			playTextLost = true;
		}
		// Se pone el texto de "dulces sueños"

		if (playTextLost) {
			textLost->update();
			if (textLost->currentFrame == textLost->totalFrames) {
				textLost->currentFrame--;
				startLostTimer = true;
			}
		}
		// Se esperan 1.5 segundos
		if (startLostTimer) {
			lostTimer--;
		}
		// Se vuelve al menu principal
		if (lostTimer == 0) {
			game->currentLevel = 0;
			game->gameLayer->init();
			game->layer = game->menuLayer;
			game->gameLayer->endEvent = true;
			game->layer->resume();
		}

		return;
	}

	background->update();

	// Movimiento de los circulos
	for (auto const& beat : beats)
		beat->update(mapSpeed);

	// Movimiento de los activadores
	for (auto const& act : activators)
		act->update(mapSpeed);

	// ***** Animación de las teclas *****
	// D
	if (lane1->pressed) {
		key1->update();
		if (key1->currentFrame == key1->totalFrames)
			key1->currentFrame--;
	}
	else {
		key1->currentFrame = 0;
		key1->updateTime = 0;
		key1->update();
	}

	// F
	if (lane2->pressed) {
		key2->update();
		if (key2->currentFrame == key2->totalFrames)
			key2->currentFrame--;
	}
	else {
		key2->currentFrame = 0;
		key2->updateTime = 0;
		key2->update();
	}

	// J
	if (lane3->pressed) {
		key3->update();
		if (key3->currentFrame == key3->totalFrames)
			key3->currentFrame--;
	}
	else {
		key3->currentFrame = 0;
		key3->updateTime = 0;
		key3->update();
	}

	// K
	if (lane4->pressed) {
		key4->update();
		if (key4->currentFrame == key4->totalFrames)
			key4->currentFrame--;
	}
	else {
		key4->currentFrame = 0;
		key4->updateTime = 0;
		key4->update();
	}
	// ***********************************

	// Movimiento del terminador
	ender->update(mapSpeed);
	
	// Cálculo de la vida del rival
	rh = 100 - (int) ((timePassed * 110)/(realRh * 30));

	if (rh == 50) {
		rival->currentAnimation = rival->rage;
		if (!enragePlayed) {
			soundEnrage = Audio::createAudio("res/sound/fx/enrage.wav", false);
			soundEnrage->play();
			enragePlayed = true;
		}
	}
	barPlayer->update(ph);
	barRival->update(rh);

	// Animaciones de la party y del rival
	player->update();
	rival->update();

	// Finalización de la animación si esta es de duración limitada
	// Para el jugador
	if (player->currentAnimation->loop == false &&
		player->currentAnimation->totalFrames == player->currentAnimation->currentFrame) {
		player->currentAnimation->updateTime = 0;
		player->currentAnimation->currentFrame = 0;
		player->currentAnimation = player->loop;
	}
	// Para el rival
	if (rival->currentAnimation->loop == false &&
		rival->currentAnimation->totalFrames == rival->currentAnimation->currentFrame) {
		rival->currentAnimation->updateTime = 0;
		rival->currentAnimation->currentFrame = 0;
		rival->currentAnimation = rival->loop;
	}

	// ****** COLISIONES ******

	list<BeatmapEventActivator*> deleteActivators;
	list<BeatCircle*> deleteBeats;

	// Activación del activador
	for (auto const& act : activators) {
		if (act->isOverlap(activatorBox)) {
			// Cambiará cuando se añadan mas tipos de eventos
			// (si da tiempo a ello)
			this->mapSpeed = act->speedValue;
			// draw(); // Añadido para más precisión
			deleteActivators.push_back(act);
		}
	}

	// Eliminación de beats
	for (auto const& beat : beats) {
		// Si se ha acertado
		if (beat->isOverlap(lane1) && lane1->tapped == true && lane1cd == 0)
			deleteBeats.push_back(beat);
		if (beat->isOverlap(lane2) && lane2->tapped == true && lane2cd == 0)
			deleteBeats.push_back(beat);
		if (beat->isOverlap(lane3) && lane3->tapped == true && lane3cd == 0)
			deleteBeats.push_back(beat);
		if (beat->isOverlap(lane4) && lane4->tapped == true && lane4cd == 0)
			deleteBeats.push_back(beat);
		// Si se ha fallado
		if (beat->isOverlap(deathBox)) {
			if (ph > 0 && ph - 5 > 0) {
				ph -= 5;
				points -= 20;
				player->currentAnimation = player->miss;
			}
			else {
				ph = 0;
				lost = true;
			}
			if (soundMissCd == 0) {
				soundMiss = Audio::createAudio("res/sound/fx/menu_deny.wav", false);
				soundMiss->play();
				soundMissCd = 3;
			}
			deleteBeats.push_back(beat);
		}
		// Si se ha pulsado la tecla pero no se ha dado a una nota
		// Se pone un cooldown en esa línea de 1/6 de segundo
		if (!beat->isOverlap(lane1) && lane1->tapped == true
			&& beat->x > 110 && beat->x < 146)
			lane1cd = 5;
		if (!beat->isOverlap(lane2) && lane2->tapped == true
			&& beat->x > 147 && beat->x < 169)
			lane2cd = 5;
		if (!beat->isOverlap(lane3) && lane3->tapped == true
			&& beat->x > 170 && beat->x < 180)
			lane3cd = 5;
		if (!beat->isOverlap(lane4) && lane4->tapped == true
			&& beat->x > 181 && beat->x < 210)
			lane4cd = 5;
	}

	if (lane1cd > 0) lane1cd--;
	if (lane2cd > 0) lane2cd--;
	if (lane3cd > 0) lane3cd--;
	if (lane4cd > 0) lane4cd--;

	// Finalización del combate sin perder

	if (ender->isOverlap(activatorBox)) {
		game->layer = game->gameLayer;
		game->layer->initialWait = true;
		game->layer->resume();
	}
		
	// ****** LIMPIEZA ******
	
	for (auto const& act : deleteActivators) {
		activators.remove(act);
		delete act;
	}

	for (auto const& beat : deleteBeats) {
		beats.remove(beat);
		delete beat;
	}

	// ****** OTROS ******

	// Las lineas solo detectan el frame en el que se pulsan

	lane1->update();
	lane2->update();
	lane3->update();
	lane4->update();

	// ******* CONTADORES ******

	// Contador para que no suenen varios sonidos a la vez

	if (soundPlayedCounter > 0) {
		soundPlayedCounter--;
	}
	else soundPlayed = false;

	// Opacidad inicial de los componentes
	if (opacityCounter < 255) opacityCounter += 5; 
	else {
		opacityCounter = 255;
		if (!playerStartAnimationPlayed) {
			player->currentAnimation = player->start;
			playerStartAnimationPlayed = true;
		}
		if (!rivalStartAnimationPlayed) {
			rival->currentAnimation = rival->start;
			rivalStartAnimationPlayed = true;
		}
	}

	// Contador para la animación inicial de los personajes
	if (startTimePassed == 0) {
		if (timePassed < (realRh * 30)) {
			timePassed++;
		}
	}
	else startTimePassed--;

	// Contador para que no se repitan sonidos
	if (soundMissCd > 0) soundMissCd--;
}

void BeatmapLayer::incrementOpacity(Actor* a) {
	SDL_SetTextureBlendMode(a->texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(a->texture, opacityCounter);
}

void BeatmapLayer::loadMap(string name) {
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
		mapSpeed = stof(getString(metadata, 2)) / (float) 30;
		song = Audio::createAudio(songName, true);
		song->play();
		playerData = { getString(metadata, 3) , getString(metadata, 4), getString(metadata, 5) };
		rivalData = { getString(metadata, 6) , getString(metadata, 7), getString(metadata, 8) };
		realRh = stof(getString(metadata, 17));
		player = new Party(WIDTH * 0.2, HEIGHT * 0.65, game, metadata);
		rival = new Rival(WIDTH * 0.82, HEIGHT * 0.65, game, metadata);

		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = (j * 23) + 125; // x central
				float y = i * 23 * (- 1);
				if (character == 'b')
					loadMapObject(character, x, y);
				else if (character == 's')
					loadMapActivator(character, x, y, stof(getString(split(line, ';'), 2)));
				else if (character == 'e')
					ender = new BeatmapEnder(x - 40, y - 40, game);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void BeatmapLayer::loadMapObject(char character, float x, float y)
{
	BeatCircle* beat = new BeatCircle("res/sprite/beatmap/beatcircle.png", x, y, game);
	beats.push_back(beat);
}

void BeatmapLayer::loadMapActivator(char character, float x, float y, float val)
{
	BeatmapEventActivator* act = new BeatmapEventActivator("res/sprite/beatcircle.png", x, y, val / (float) 30, game);
	activators.push_back(act);
}

void BeatmapLayer::processControls() {
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
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
	}
}

void BeatmapLayer::keysToControls(SDL_Event event) {
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
			// Líneas
		case SDLK_d:
			if (!lane1->pressed)
				lane1->tapped = true;
			lane1->pressed = true;
			for (auto const& beat : beats) {
				if (beat->isOverlap(lane1) && lane1->tapped == true
					&& !soundPlayed && lane1cd == 0) {
					hitSound->play();
					soundPlayed = true;
					soundPlayedCounter = 3;
					if (ph < 100) ph++;
					points += 100;
				}
			}
			break;
		case SDLK_f:
			if (!lane2->pressed)
				lane2->tapped = true;
			lane2->pressed = true;
			for (auto const& beat : beats) {
				if (beat->isOverlap(lane2) && lane2->tapped == true
					&& !soundPlayed && lane2cd == 0) {
					hitSound->play();
					soundPlayed = true;
					soundPlayedCounter = 3;
					if (ph < 100) ph++;
					points += 100;
				}
			}
			break;
		case SDLK_j:
			if (!lane3->pressed)
				lane3->tapped = true;
			lane3->pressed = true;
			for (auto const& beat : beats) {
				if (beat->isOverlap(lane3) && lane3->tapped == true
					&& !soundPlayed && lane3cd == 0) {
					hitSound->play();
					soundPlayed = true;
					soundPlayedCounter = 3;
					if (ph < 100) ph++;
					points += 100;
				}
			}
			break;
		case SDLK_k:
			if (!lane4->pressed)
				lane4->tapped = true;
			lane4->pressed = true;
			for (auto const& beat : beats) {
				if (beat->isOverlap(lane4) && lane4->tapped == true
					&& !soundPlayed && lane4cd == 0) {
					hitSound->play();
					soundPlayed = true;
					soundPlayedCounter = 3;
					if (ph < 100) ph++;
					points += 100;
				}
			}
			break;
		}
	}

	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d:
			lane1->pressed = false;
			break;
		case SDLK_f:
			lane2->pressed = false;
			break;
		case SDLK_j:
			lane3->pressed = false;
			break;
		case SDLK_k:
			lane4->pressed = false;
			break;
		}
	}
	
}

void BeatmapLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	// Cada vez que hacen click
	/*if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (button->containsPoint(motionX, motionY)) {
			controlContinue = true;
		}
	}*/
}

void BeatmapLayer::gamePadToControls(SDL_Event event) {
	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);

	/*if (buttonA) {
		controlContinue = true;
	}*/
}

list<string> BeatmapLayer::split(string str, char divider) {
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

string BeatmapLayer::getString(list<string> l, int pos) {
	list<string>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}