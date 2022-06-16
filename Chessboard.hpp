//
//  Chessboard.hpp
//intercambiar x i y

#ifndef ChessBoard_h
#define ChessBoard_h

#include <stdio.h>
#include "GameInfo.h"
#include "ChessPosition.hpp"
/*
#include <vector>// esta en GameInfo.h
#include "ChessPosition.hpp"
int const NUM_X = 8;
int const NUM_Y = 8;
typedef vector<ChessPosition> VecOfPositions;
*/
#include "Piece.hpp"
#include <fstream>
#include <iostream>

using namespace std;


class Chessboard {

public:
    Chessboard();

    void LoadBoardFromFile(const string& path);  //esto con ifstream para leer de documento. 
    bool MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo);
    void setPiece(int x, int y, ChessPieceType  tipo, ChessPieceColor color);
    void ToString();

    VecOfPositions GetValidMoves(const ChessPosition& pos);
    Piece getPiece(int x, int y) { return m_board[y][x]; }
    ChessPieceColor GetPieceColorAtPos(const ChessPosition& pos) const;
    ChessPieceType GetPieceTypeAtPos(const ChessPosition& pos) const;
    int readY(char c) { int y = (c - '0') - 1; return y; }
    int readX(char c) { int x = c - 'a'; return x; }
    
    ChessPieceColor readColor(char c);
    ChessPieceType readType(char c);
    void Render();
    void RenderMoviments(VecOfPositions posDesti, const ChessPosition& posInicial);

private:
    Piece m_board[NUM_Y][NUM_X];

};

void afejirPosicio(VecOfPositions& vec, int x, int y);
void afejirPosicioIf(VecOfPositions& vec, int x, int y);
ifstream& operator>>(ifstream& input, ChessPieceType& tipus);
ifstream& operator>>(ifstream& input, ChessPieceColor& color);
ostream& operator<<(ostream& output, ChessPosition& pos);

#endif