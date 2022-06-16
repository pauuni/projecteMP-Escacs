//
//  Piece.hpp
//intercambiar x i y

#ifndef Moviment_HPP
#define Moviment_HPP

#include <stdio.h>
#include <vector>
#include "GameInfo.h"
#include "Piece.hpp"
#include "ChessPosition.hpp"


class Moviment {

public:
    Moviment() { setXInici(NUM_X); setYInici(NUM_Y); setXFinal(NUM_X); setYFinal(NUM_Y); }
    Moviment(int xInici, int yInici, int xFinal, int yFinal) { setXInici(xInici); setYInici(yInici); setXFinal(xFinal); setYFinal(yFinal); }
    Moviment(char xInici, char yInici, char xFinal, char yFinal) { setXInici(xInici); setYInici(yInici); setXFinal(xFinal); setYFinal(yFinal); }

    int getXInici() const { return m_inici.getPosX(); }
    int getYInici() const { return m_inici.getPosY(); }
    int getXFinal() const { return m_final.getPosX(); }
    int getYFinal() const { return m_final.getPosY(); }

    ChessPosition getInici() const { return m_inici; }
    ChessPosition getFinal() const { return m_final; }

    void setXInici(int x) { m_inici.setPosX(x); }
    void setYInici(int y) { m_inici.setPosY(y); }
    void setXFinal(int x) { m_final.setPosX(x); }
    void setYFinal(int y) { m_final.setPosY(y); }

    void setXInici(char x) { m_inici.setPosX(x - 'a'); }
    void setYInici(char y) { m_inici.setPosY((y - '0') - 1); }
    void setXFinal(char x) { m_final.setPosX(x - 'a'); }
    void setYFinal(char y) { m_final.setPosY((y - '0') - 1); }

private:
    ChessPosition m_inici;
    ChessPosition m_final;

};

#endif