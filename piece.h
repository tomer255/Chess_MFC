#pragma once
#include "Helper.h"
#include <iostream>
#include <vector>
#define BOARD_SIZE 8

using namespace std;

//enum icon {
//	IPawn = L'♟',
//	IBishop = L'♝',
//	IKnight = L'♞',
//	IRooks = L'♜',
//	IKing = L'♚',
//	IQueen = L'♛'
//};

enum icon {
	IPawn = L'♙',
	IBishop = L'♗',
	IKnight = L'♘',
	IRooks = L'♖',
	IKing = L'♔',
	IQueen = L'♕'
};

class piece
{
protected:
	vector<COORD> Direction;
	wchar_t icon;
	int player;
	int distance = BOARD_SIZE;
public:
	virtual bool validMove(piece*[8][8], COORD, COORD);
	virtual ~piece() {};
	int getPlayer();
	COORD getNewLoc(COORD, int, int);
	virtual void setDirection() = 0;
	int NumDirection();
	wchar_t getIcon();
};

