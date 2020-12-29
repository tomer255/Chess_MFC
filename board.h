#pragma once

#include "Helper.h"
#include "piece.h"
#include "Pawn.h"
#include "Rooks.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"

//template<class T>
class Board : public CObject
{
private:
	void LoadFromList(int list[BOARD_SIZE][BOARD_SIZE][2]);
	int turn;
	piece* mat[BOARD_SIZE][BOARD_SIZE];
	COORD FindKing(int);
public:
	void CleanBoard();
	void setNewBoard();
	int &getTurn();
	void ChangePiece(COORD,int);
	Board();
	~Board();
	bool MovePiece(COORD, COORD);
	piece*& operator[](COORD);
	bool CheckChess(int);
	//bool Checkmatec(int, COORD);
	void Serialize(CArchive& ar);
	DECLARE_SERIAL(Board);
};

