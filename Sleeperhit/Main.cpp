#include "Game.h"
#undef main  //esto es para quitar el main que hay en la Librer�a SDL_main
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main() {
	Game* game = new Game();
	return 0;
}
