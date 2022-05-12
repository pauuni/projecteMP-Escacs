//
//  Chessboard.hpp
//

#ifndef ChessBoard_h
#define ChessBoard_h

#include <stdio.h>
#include "GameInfo.h"
/*
#include <vector>// esta en GameInfo.h
#include "ChessPosition.hpp"
int const NUM_COLS = 8;
int const NUM_ROWS = 8;
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
    void setPiece(int col, int row, ChessPieceType  tipo, ChessPieceColor color);
    string ToString();

    VecOfPositions GetValidMoves(const ChessPosition& pos);
    Piece getPiece(int col, int row) { return m_board[col][row]; }
    ChessPieceColor GetPieceColorAtPos(const ChessPosition& pos) const;
    ChessPieceType GetPieceTypeAtPos(const ChessPosition& pos) const;

    ChessPieceColor readColor(char c);
    ChessPieceType readType(char c);
    int readRow(char c) {int row = (c - '0') - 1; return row; }
    int readCol(char c) {int col = c - 'a'; return col;}
    int stringToYCoordenate(string strin);
    int correctXCoordenate(int x);

private:
    Piece m_board[NUM_COLS][NUM_ROWS];

};

void afejirPosicio(VecOfPositions& vec, int x, int y);
void afejirPosicioIf(VecOfPositions& vec, int x, int y);
ifstream& operator>>(ifstream& input, ChessPieceType& tipus);
ifstream& operator>>(ifstream& input, ChessPieceColor& color);
ostream& operator<<(ostream& output, ChessPosition& pos);

#endif