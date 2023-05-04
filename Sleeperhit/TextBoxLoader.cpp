#include "TextBoxLoader.h"

TextBoxLoader::TextBoxLoader(string textCode, Game* game) {
	box = new Actor("res/textbox.png", WIDTH, HEIGHT, 320, 60, game);
	arrow = new Animation("res/textarrow.png", 22, 13, 91, 13, 4, 4, true, game);
	this->textCode = textCode;
	this->game = game;
	loadTextFromFile();
	readyForNextText = false;
	it = textList.begin();
}

void TextBoxLoader::next() {
	if (*it == *(--textList.end())) {
		inTextBox = false;
	}
	readyForNextText = true;
}

void TextBoxLoader::update() {
	arrow->update();
	if (getCurrentTextBox() != NULL) getCurrentTextBox()->update();
}

void TextBoxLoader::draw() {
	if (inTextBox) {
		box->draw(WIDTH * 0.5, 30);
		arrow->draw(WIDTH * 0.95, 225);
		if (getCurrentTextBox() != NULL) getCurrentTextBox()->draw(0, 0);
	}
}

TextBox* TextBoxLoader::getCurrentTextBox() {
	TextBox* result;
	if (readyForNextText && *it != *(--textList.end())) {
		++it;
	}
	/*if (readyForNextText && *it == *(--textList.end())) {
		inTextBox = false;
	}*/
	result = *it;
	
	readyForNextText = false;
	return result;
}

void TextBoxLoader::loadTextFromFile() {
	char character;
	string portraits = "NLGYM";
	int counter = 0;
	string lines[3];
	string line, p;
	bool flag = false;
	ifstream streamFile("res/dialogs.txt");
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de texto" << endl;
		return;
	}
	else {
		// Por línea
		while (getline(streamFile, line)) {
			if (line == textCode) {
				while (line[0] != '#') {
					// Si el inicio de la línea se corresponde con un caracter, comienza
					if (line[0] == '-') {
						p = line[1];
						// Leemos las tres líneas
						while (getline(streamFile, line) && line[0] != '#' && line[0] != '.') {
							lines[counter] = line;
							counter++;
						}
						// Creamos una TextBox
						textList.push_back(new TextBox(lines[0], lines[1], lines[2], p[0], game));
						counter = 0;
					}
					// Si encontramos un '.', añadimos más
					if (line[0] == '.') {
						p = line[1];
						while (getline(streamFile, line) && line[0] != '#' && line[0] != '.') {
							lines[counter] = line;
							counter++;
						}
						// Creamos una TextBox
						textList.push_back(new TextBox(lines[0], lines[1], lines[2], p[0], game));
						counter = 0;
					}
				}
			}
		}
	}
	streamFile.close();
}
