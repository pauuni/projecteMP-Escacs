//
//  ChessPosition.cpp
//

#include "ChessPosition.hpp"

#include <stdio.h>
#include <string>
using namespace std;

bool operator==(const ChessPosition& p1, const ChessPosition& p2)
{
    return ((p1.getPosX() == p2.getPosX()) && (p1.getPosY() == p2.getPosY()));
}
string ChessPosition::getPosXConverted() const
{
	switch (m_posX)
	{
	case 0:
		return "a";
		break;
	case 1:
		return "b";
		break;
	case 2:
		return "c";
		break;
	case 3:
		return "d";
		break;
	case 4:
		return "e";
		break;
	case 5:
		return "f";
		break;
	case 6:
		return "g";
		break;
	case 7:
		return "h";
		break;
	default:
		break;
	}
}
