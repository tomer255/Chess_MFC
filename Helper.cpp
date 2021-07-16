#include "pch.h"
#include "Helper.h"



COORD ConvLoc(COORD loc,double blocks) {
	loc.X -= 15;
	loc.Y -= 15;
	loc.X /= blocks;
	loc.Y /= blocks;
	return loc;
}

COORD ReConvLoc(COORD loc, double blocks) {
	loc.X *= blocks;
	loc.Y *= blocks;
	loc.X += 15;
	loc.Y += 15;
	return loc;
}

_COORD operator+(_COORD a, _COORD b) { return { a.X + b.X , a.Y + b.Y }; }

bool operator==(_COORD a, _COORD b) { return (a.X == b.X && a.Y == b.Y); }

_COORD operator*(_COORD a, int b) { return { a.X * (SHORT)b , a.Y * (SHORT)b }; }

bool validLoc(COORD t) {
	if (t.X < 0 || t.X > 7 || t.Y < 0 || t.Y > 7)
		return false;
	return true;
}

void GetDesktopResolution( double& blocks, double &blocks_size, double &piece_size, double &piece_center)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	int horizontal = desktop.right;
	int vertical = desktop.bottom;
	int temp = horizontal + vertical;
	blocks = 55;
	blocks_size = 10;
	piece_size = 7;
	piece_center = 5;
}