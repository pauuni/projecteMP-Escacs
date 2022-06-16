//
//  ChessPosition.hpp
//intercambiar x i y

#ifndef ChessPosition_h
#define ChessPosition_h

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

const int NUM_X = 8;
const int NUM_Y = 8;

class ChessPosition {

public://metodo: posicio  esta en el tablero , sumar de posicions
    ChessPosition(string pos) : m_posY((pos[1] - '0') - 1), m_posX(pos[0] - 'a') {};
    ChessPosition() : m_posX(0), m_posY(0) {};
    void setPosX(int x) { m_posX = x; }
    void setPosY(int y) { m_posY = y; }
    int getPosX() const { return m_posX; }
    int getPosY() const { return m_posY; }

    string getPosXConverted()const;
private:
    int m_posX; //Column
    int m_posY; //Row
};

bool operator==(const ChessPosition& p1, const ChessPosition& p2);
typedef vector<ChessPosition> VecOfPositions;

#endif