#pragma once

#include "piece.h"
#include "Rooks.h"
#include "Bishop.h"

class Queen : public piece
{
public:
	Queen(int);
	void setDirection();
};

