
#ifndef Piece_h
#define Piece_h

#include <stdio.h>
#include <vector>
using namespace std;

typedef enum {
    CPT_Rei = 'R',
    CPT_Dama = 'D',
    CPT_Torre = 'T',
    CPT_Alfil = 'A',
    CPT_Cavall = 'C',
    CPT_Peó = 'P',
    CPT_EMPTY = '_'
} ChessPieceType;

typedef enum {
    CPC_Blanc = 'b',
    CPC_Negra = 'n',
    CPC_NONE = '_'
} ChessPieceColor;



class Piece {

public://fer un reset
    Piece() : m_type(CPT_EMPTY), m_color(CPC_NONE) {}
    ChessPieceType getChessPieceType() { return m_type; }
    ChessPieceColor getChessPieceColor() { return m_color; }
    void setChessPieceType(ChessPieceType type) { m_type = type; }
    void setChessPieceColor(ChessPieceColor color) { m_color = color; }

private:
    ChessPieceType  m_type;
    ChessPieceColor m_color;

};


#endif
