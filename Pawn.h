#pragma once
#include "piece.h"

class Pawn : public piece
{
public:
	Pawn(int);
	bool validMove(piece*[8][8], COORD, COORD);
	void setDirection();
};

