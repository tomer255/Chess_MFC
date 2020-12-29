#include "pch.h"
#include "Knight.h"


Knight::Knight(int player) {
	this->player = player;
	setDirection();
	distance = 1;
	icon = IKnight;
}

void Knight::setDirection() {
	Direction.push_back({ 2, 1 });
	Direction.push_back({ 2, -1 });
	Direction.push_back({ -2, 1 });
	Direction.push_back({ -2, -1 });
	Direction.push_back({ 1, 2 });
	Direction.push_back({ -1, 2 });
	Direction.push_back({ 1, -2 });
	Direction.push_back({ -1, -2 });
}

