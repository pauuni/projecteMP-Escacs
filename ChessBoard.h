
#ifndef ChessBoard_h
#define ChessBoard_h

#include <stdio.h>
#include <vector>
#include "Piece.hpp"
#include "ChessPosition.hpp"
#include <fstream>
#include <iostream>
using namespace std;

int const NUM_COLS = 8;
int const NUM_ROWS = 8;
typedef vector<ChessPosition> VecOfPositions;

class ChessBoard {

public:
    ChessBoard();

    void LoadBoardFromFile(const string& path);  //esto con ifstream para leer de documento. 
    bool MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo);
    void setPiece(int col, int row, ChessPieceType  tipo, ChessPieceColor color);

    VecOfPositions GetValidMoves(const ChessPosition& pos);
    string ToString();
    Piece getPiece(int col, int row) { return m_board[col][row]; }

    int stringToYCoordenate(string strin);
    int correctXCoordenate(int x);

private:
    Piece m_board[NUM_COLS][NUM_ROWS];

};

void afejirPosicio(VecOfPositions& vec, int x, int y);
ifstream& operator>>(ifstream& input, ChessPieceType& tipus);
ifstream& operator>>(ifstream& input, ChessPieceColor& color);

#endif