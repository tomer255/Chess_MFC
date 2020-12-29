#pragma once

//#include <iostream>
//#include <Windows.h>
//#include <conio.h>
//#include <time.h>
//#include <fcntl.h>
//#include <io.h>
//#include <stdlib.h>

void GetDesktopResolution(double&, double&, double&, double&);

//#define BLOKS 80
//#define BLOKS_SIZE 7
//#define PIECE_SIZE 5.5
//#define PIECE_SENER 6.25

//#define BLOKS 55
//#define BLOKS_SIZE 11
//#define PIECE_SIZE 8
//#define PIECE_SENER 5



_COORD operator+(_COORD a, _COORD b);
bool operator==(_COORD a, _COORD b);
_COORD operator*(_COORD a, int b);

COORD ConvLoc(COORD loc, double);
COORD ReConvLoc(COORD loc, double);
bool validLoc(COORD);