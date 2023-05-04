#include "AnimationEvent.h"

AnimationEvent::AnimationEvent(string evt, Npc* npc, Game* game) : Event("", npc, game) {
	this->game = game;
	this->npc = npc;
	toPlay = new Animation(get(split(evt, ';'), 1), stoi(get(split(evt, ';'), 2)), stoi(get(split(evt, ';'), 3)),
		128, 59, stoi(get(split(evt, ';'), 4)), stoi(get(split(evt, ';'), 5)), false, game);
	previousAnimation = new Animation(get(split(evt, ';'), 1), stoi(get(split(evt, ';'), 2)), stoi(get(split(evt, ';'), 3)),
		128, 59, stoi(get(split(evt, ';'), 4)), stoi(get(split(evt, ';'), 5)), true, game);
	this->isFinished = false;
	this->flagAnim = false;
}

void AnimationEvent::update() {
	if (!flagAnim) {
		npc->animation = toPlay;
		flagAnim = true;
	}
	if (npc->animation->currentFrame == npc->animation->totalFrames) {
		npc->animation = previousAnimation;
		isFinished = true;
	}
}

void AnimationEvent::draw() { }

void AnimationEvent::next() { }

list<string> AnimationEvent::split(string str, char divider) {
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

string AnimationEvent::get(list<string> l, int pos) {
	list<string>::iterator it = l.begin();
	for (int i = 0; i < pos; i++) {
		++it;
	}
	return *it;
}