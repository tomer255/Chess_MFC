#include "pch.h"
#include "board.h"

IMPLEMENT_SERIAL(Board, CObject, 0);

Board::Board()
{
	turn = 1;
	CleanBoard();
	setNewBoard();
}

void Board::CleanBoard() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			mat[i][j] = nullptr;
}

void Board::setNewBoard() {
	mat[0][0] = new Rooks(0);
	mat[1][0] = new Knight(0);
	mat[2][0] = new Bishop(0);
	mat[3][0] = new Queen(0);
	mat[4][0] = new King(0);
	mat[5][0] = new Bishop(0);
	mat[6][0] = new Knight(0);
	mat[7][0] = new Rooks(0);
	mat[0][7] = new Rooks(1);
	mat[1][7] = new Knight(1);
	mat[2][7] = new Bishop(1);
	mat[3][7] = new Queen(1);
	mat[4][7] = new King(1);
	mat[5][7] = new Bishop(1);
	mat[6][7] = new Knight(1);
	mat[7][7] = new Rooks(1);
	for (int i = 0; i < 8; i++) {
		mat[i][6] = new Pawn(1);
		mat[i][1] = new Pawn(0);
	}
}

Board::~Board()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (this->mat[i][j] != nullptr)
			{
				delete[] this->mat[i][j];
			}
		}
	}
}

piece*& Board::operator[](COORD t) {
	return this->mat[t.X][t.Y];
}


bool Board::MovePiece(COORD from, COORD to) {
	piece* ToPtr = (*this)[to];
	piece* FromPtr = (*this)[from];
	if ((*this)[from]->validMove(this->mat, from, to))
	{
		(*this)[to] = (*this)[from];
		(*this)[from] = nullptr;
		if (CheckChess((*this)[to]->getPlayer())) {
			(*this)[to] = ToPtr;
			(*this)[from] = FromPtr;
			MessageBox(NULL,L"The king is threatening", L"Illegal move", MB_ICONWARNING);
			return false;
		}
		else if (FromPtr != nullptr) delete[] ToPtr;
		return true;
	}
	return false;
}

COORD Board::FindKing(int player) {
	COORD loc = { -1,-1 };
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (mat[i][j] != nullptr && mat[i][j]->getIcon() == IKing && mat[i][j]->getPlayer() == player)
				return { (SHORT)i,(SHORT)j };
}

bool Board::CheckChess(int player) {
	COORD loc = FindKing(player);
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (mat[i][j] != nullptr && mat[i][j]->getPlayer() != player)
			{
				COORD temp = { (SHORT)i,(SHORT)j };
				if ((*this)[temp]->validMove(this->mat, temp, loc))
					return true;
			}
	return false;
}

void Board::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		ar << turn;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (mat[i][j] != nullptr)
				{
					ar << (int)mat[i][j]->getIcon();
					ar << mat[i][j]->getPlayer();
				}
				else
				{
					ar << 0;
					ar << 0;
				}
			}
		}
	}
	else {
		ar >> turn;
		int listToLoad[BOARD_SIZE][BOARD_SIZE][2];
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				ar >> listToLoad[i][j][0];
				ar >> listToLoad[i][j][1];
			}
		}
		LoadFromList(listToLoad);
	}
}

void Board::LoadFromList(int list[BOARD_SIZE][BOARD_SIZE][2]) {
	CleanBoard();
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			switch (list[i][j][0])
			{
			case IPawn: mat[i][j] = new Pawn(list[i][j][1]); break;
			case IBishop: mat[i][j] = new Bishop(list[i][j][1]); break;
			case IKnight: mat[i][j] = new Knight(list[i][j][1]); break;
			case IRooks: mat[i][j] = new Rooks(list[i][j][1]); break;
			case IKing: mat[i][j] = new King(list[i][j][1]); break;
			case IQueen: mat[i][j] = new Queen(list[i][j][1]); break;
			default: break;
			}
		}
	}

}

int &Board::getTurn() {
	return turn;
}

void Board::ChangePiece(COORD loc, int newp) {
	int player = (*this)[loc]->getPlayer();
	delete[](*this)[loc];
	switch (newp)
	{
	case 0: (*this)[loc] = new Rooks(player); break;
	case 1: (*this)[loc] = new Bishop(player); break;
	case 2: (*this)[loc] = new Knight(player); break;
	case 3: (*this)[loc] = new Queen(player); break;
	default:
		break;
	}
}