
#ifndef ChessPosition_h
#define ChessPosition_h

#include <stdio.h>
#include <string>
using namespace std;

class ChessPosition {

public:
    void setPosX(int x) { m_posX = x; }
    void setPosY(int y) { m_posY = y; }
    int getPosX () const {return m_posX;} 
    int getPosY () const {return m_posY;}
private:
    int m_posX; //Column
    int m_posY; //Row
    
    
};


#endif
