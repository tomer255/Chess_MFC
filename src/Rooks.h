#pragma once
#include "piece.h"

class Rooks : public piece
{
public:
	Rooks(int);
	virtual void setDirection();
};

