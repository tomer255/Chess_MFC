#include "pch.h"
#include "Helper.h"



COORD ConvLoc(COORD loc,double bloks) {
	loc.X -= 15;
	loc.Y -= 15;
	loc.X /= bloks;
	loc.Y /= bloks;
	return loc;
}

COORD ReConvLoc(COORD loc, double bloks) {
	loc.X *= bloks;
	loc.Y *= bloks;
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

void GetDesktopResolution( double& bloks, double &bloks_size, double &piece_size, double &piece_sener)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	int horizontal = desktop.right;
	int vertical = desktop.bottom;
	int temp = horizontal + vertical;
	bloks = temp / 40;
	bloks_size = bloks / 10;
	piece_size = bloks_size-1;
	piece_sener = temp / 320;
}