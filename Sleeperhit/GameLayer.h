#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "Pad.h"

#include "Npc.h"
#include "EventLoader.h"

#include "ZoneTile.h"
#include "NpcTile.h"

#include "Audio.h"
#include "Space.h" // importar

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void resume() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	list<string> split(string str, char divider);
	string getString(list<string> l, int pos);
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	void changeOpacity(Actor* a, float value);
	bool pause;
	// Elementos de interfaz
	SDL_GameController* gamePad;
	Pad* pad;
	Actor* buttonJump;
	Actor* buttonShoot;

	Space* space;
	float scrollX;
	float scrollY;
	int mapWidthX;
	int mapWidthY;
	list<Tile*> tiles;
	list<EventTile*> eventTiles;
	list<Npc*> npcs;
	int npcPos = 0;
	string songName;
	int eventTilePos = 0;

	Audio* audioBackground;
	int newEnemyTime = 0;
	Player* player;
	Background* background;
	Actor* activeMap; // Mapa que se renderiza debajo del jugador
	Actor* topMap; // Mapa que se renderiza encima de él
	list<Enemy*> enemies;
	list<Projectile*> projectiles;

	bool controlContinue = false;
	bool controlInteract = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	Text* textPrealpha;

	EventLoader* currentEvent;
	Npc* currentNpc;

	// Oscurecedor de pantalla empleado en los efectos
	Actor* blackScreen;
};

