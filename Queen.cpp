#include "pch.h"
#include "Queen.h"

Queen::Queen(int player) {
	this->player = player;
	setDirection();
	icon = IQueen;
}


void Queen::setDirection() {
	Direction.push_back({ 1, 0 });
	Direction.push_back({ 0, 1 });
	Direction.push_back({ -1, 0 });
	Direction.push_back({ 0, -1 });
	Direction.push_back({ 1, 1 });
	Direction.push_back({ -1, 1 });
	Direction.push_back({ 1, -1 });
	Direction.push_back({ -1, -1 });
}
