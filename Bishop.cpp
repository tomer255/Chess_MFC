#include "pch.h"
#include "Bishop.h"

Bishop::Bishop(int player) {
	this->player = player;
	setDirection();
	 icon = IBishop;
}

void Bishop::setDirection() {
	Direction.push_back({ 1, 1 });
	Direction.push_back({ -1, 1 });
	Direction.push_back({ 1, -1 });
	Direction.push_back({ -1, -1 });
}
