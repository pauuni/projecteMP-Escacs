
#include "ChessPosition.hpp"

#include <stdio.h>
#include <string>
using namespace std;

bool operator==(const ChessPosition& p1, const ChessPosition& p2)
{
    return ((p1.getPosX() == p2.getPosX()) && (p1.getPosY() == p2.getPosY()));
}