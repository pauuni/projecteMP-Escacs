//
//  Piece.hpp
//intercambiar x i y

#ifndef Piece_h
#define Piece_h

#include <stdio.h>
#include <vector>
#include "GameInfo.h"//??

using namespace std;

typedef enum {
    CPT_King = 'R',
    CPT_Queen = 'D',
    CPT_Rook = 'T',
    CPT_Bishop = 'A',
    CPT_Knight = 'C',
    CPT_Pawn = 'P',
    CPT_EMPTY = '_'
} ChessPieceType;

typedef enum {
    CPC_White = 'b',  //blanc
    CPC_Black = 'n',  //negra
    CPC_NONE = '_'
} ChessPieceColor;


class Piece {

public:
    Piece() : m_type(CPT_EMPTY), m_color(CPC_NONE) {}
    ChessPieceType getChessPieceType() const { return m_type; }
    ChessPieceColor getChessPieceColor() const { return m_color; }
    void setChessPieceType(ChessPieceType type) { m_type = type; }
    void setChessPieceColor(ChessPieceColor color) { m_color = color; }
    void setReset() { m_type = CPT_EMPTY; m_color = CPC_NONE; };
    void setColor(ChessPieceColor color) { m_color = color; }
    void setType(ChessPieceType type) { m_type = type; }
    void Render(const int& posX, const int& posY);
    void RenderPlus(const int& posX, const int& posY);

private:
    ChessPieceType  m_type;
    ChessPieceColor m_color;

};

/*
bool operator==(const ChessPieceType& t1, const ChessPieceType& t2);
bool operator==(const ChessPieceColor& c1, const ChessPieceColor& c2);
//*/

#endif