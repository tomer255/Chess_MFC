#include "pch.h"
#include "Rooks.h"

Rooks::Rooks(int player) {
	this->player = player;
	setDirection();
	icon = IRooks;
}

void Rooks::setDirection() {
	Direction.push_back({ 1, 0 });
	Direction.push_back({ 0, 1 });
	Direction.push_back({ -1, 0 });
	Direction.push_back({ 0, -1 });
}