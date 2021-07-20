#include "pch.h"
#include "Pawn.h"

Pawn::Pawn(int player) {
	this->player = player;
	distance = 2;
	setDirection();
	icon = IPawn;
}

void Pawn::setDirection() {
	int PD = getPlayer() * (-2) + 1;
	Direction.push_back({ 0,(SHORT)(1 * PD) });
	Direction.push_back({ 1,(SHORT)(1 * PD) });
	Direction.push_back({ -1,(SHORT)(1 * PD) });
}

bool Pawn::validMove(piece *board[][BOARD_SIZE], COORD from, COORD to) {
	COORD temp;
	int j;
	for (int i = 1; i <= this->distance; i++) {
		temp = getNewLoc(from, 0, i);
		if (temp.X < 0 || temp.X >= BOARD_SIZE || temp.Y < 0 || temp.Y >= BOARD_SIZE)
			break;
		if (board[temp.X][temp.Y] != nullptr)
			break;
		if (temp == to) {
			this->distance = 1;
			return true;
		}
	}
	for (j = 1; j < NumDirection(); j++) {
		temp = getNewLoc(from, j, 1);
		if (temp.X < 0 || temp.X >= BOARD_SIZE || temp.Y < 0 || temp.Y >= BOARD_SIZE);
		else if (board[temp.X][temp.Y] != nullptr && board[temp.X][temp.Y]->getPlayer() != this->player && temp == to) {
			distance = 1;
			return true;
		}
	}
	return false;
}