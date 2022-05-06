//
//  ChessPosition.hpp
//

#ifndef ChessPosition_h
#define ChessPosition_h

#include <stdio.h>
#include <string>
using namespace std;

class ChessPosition {

public://metodo: posicio  esta en el tablero , sumar de posicions
    //ChessPosition(string pos) : m_posX(correctXCoordenate(pos[1] - 48)), m_posY(stringToYCoordenate(charToString(pos[0]))) {}; //es la versio optima, no funciona
    ChessPosition(string pos) : m_posX((pos[1] - 48) - 1), m_posY((pos[0]) - 'a') {};
    ChessPosition() : m_posX(0), m_posY(0) {}; //setejar els valors a 0 ?
    void setPosX(int x) { m_posX = x; }
    void setPosY(int y) { m_posY = y; }
    int getPosX() const { return m_posX; }
    int getPosY() const { return m_posY; }
private:
    int m_posX; //Column
    int m_posY; //Row
};

bool operator==(const ChessPosition& p1, const ChessPosition& p2);

#endif