#pragma once

#include "Layer.h"
#include "Actor.h"
#include "Background.h"
#include "Audio.h"
#include "MenuItem.h"

class MenuLayer : public Layer
{
public:
	MenuLayer(Game* game);
	void init() override;
	void update() override;
	void draw() override;
	void processControls() override;
	void keysToControls(SDL_Event event);
	void resume() override;
	void changeMenuPosition(int value);
	void gamePadToControls(SDL_Event event);
	bool controlContinue;
	SDL_GameController* gamePad; // Mando
	Background* background;
	Actor* button;
	Audio* audioBackground;
	Audio* moveSound;
	Audio* denySound;
	Audio* acceptSound;

	MenuItem* newGame;
	MenuItem* resumeItem;
	MenuItem* exit;
	int selectedPosition;
};
