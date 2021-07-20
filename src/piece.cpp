#include "pch.h"
#include "piece.h"


bool piece::validMove(piece *board[][BOARD_SIZE], COORD from, COORD to) {
	COORD temp;
	for (int j = 0; j < NumDirection(); j++) {
		for (int i = 1; i <= this->distance; i++) {
			temp = getNewLoc(from, j, i);
			if (temp.X < 0 || temp.X >= BOARD_SIZE || temp.Y < 0 || temp.Y >= BOARD_SIZE)
				break;
			if (board[temp.X][temp.Y] != nullptr && this->player == board[temp.X][temp.Y]->player)
				break;
			if (temp == to)
				return true;
			if (board[temp.X][temp.Y] != nullptr)
				break;
		}
	}
	return false;
}

int piece::getPlayer() {
	return this->player;
}

COORD piece::getNewLoc(COORD start, int num, int distance) {
	return start + Direction[num] * distance;
}

int piece::NumDirection() {
	return Direction.size();
}

wchar_t piece::getIcon() {
	return icon;
}

