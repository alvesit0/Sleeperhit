#pragma once

#include "Layer.h"
#include "Actor.h"
#include "Background.h"
#include "Text.h"
#include "Audio.h"

#include "Beatcircle.h"
#include "BeatmapEventActivator.h"
#include "BeatInteractor.h"
#include "BeatmapEnder.h"
#include "Healthbar.h"
#include "Party.h"
#include "Rival.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class BeatmapLayer : public Layer
{
public:
	BeatmapLayer(Game* game, string code);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void loadMapActivator(char character, float x, float y, float value);
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event);
	void gamePadToControls(SDL_Event event);
	void incrementOpacity(Actor* actor);
	list<string> split(string str, char divider);
	string getString(list<string> l, int pos);
	SDL_GameController* gamePad; // Mando
	Background* background;

	// Dibujo de las líneas de fondo
	Actor* lines;
	// Valor para calcular la vida del rival
	int startTimePassed;

	// Puntuación
	Text* pointsText;
	int points;

	// ************* Jugador **************
	list<string> playerData;
	Actor* healthBorderPlayer;
	Healthbar* barPlayer;
	Text* numPlayer;
	Party* player;
	int ph;
	bool playerStartAnimationPlayed;
	// ************************************

	// ************** Rival ***************
	list<string> rivalData;
	Actor* healthBorderRival;
	Healthbar* barRival;
	Text* numRival;
	Rival* rival;
	int rh;
	float realRh;
	float timePassed;
	bool rivalStartAnimationPlayed;
	// ************************************

	// Hitboxes que activan los eventos y las notas fallidas
	Actor* deathBox;
	Actor* activatorBox;

	// Dirección del .wav de la canción
	string songName;
	// Velocidad de los beats
	float mapSpeed;
	// Canción del beatmap
	Audio* song;
	
	// Beat obligatorio que indica que se ha llegado al final
	// de la canción
	BeatmapEnder* ender;

	// Notas y eventos del beatmap
	list<BeatCircle*> beats;
	list<BeatmapEventActivator*> activators;

	// Activadores de notas y animaciones de las teclas
	BeatInteractor* lane1;
	BeatInteractor* lane2;
	BeatInteractor* lane3;
	BeatInteractor* lane4;
	Animation* key1;
	Animation* key2;
	Animation* key3;
	Animation* key4;

	// Cooldowns para que no se puedan machacar las teclas y ganar
	int lane1cd;
	int lane2cd;
	int lane3cd;
	int lane4cd;

	// *** Sonidos al acertar una nota *** 
	Audio* hitSound;
	bool soundPlayed;
	int soundPlayedCounter;
	// *********************************** 

	// Opacidad inicial
	int opacityCounter = 0;

	// Código de la canción
	string code;

	// Indica si se ha perdido o no
	bool lost;

	// Sonido de enrage
	Audio* soundEnrage;

	// Sonido de fallar una nota y cooldown para que
	// no se repita muchas veces
	Audio* soundMiss;
	int soundMissCd;

	// ***** Batalla perdida *****
	bool enragePlayed;
	Actor* blackScreen;
	Animation* liliLost;
	Animation* textLost;
	bool playTextLost;
	bool startLostTimer;
	int lostTimer;
	// ***************************
};

