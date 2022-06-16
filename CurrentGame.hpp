//
//  CurrentGame.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef CurrentGame_hpp
#define CurrentGame_hpp
#include <queue>
#include <stdio.h>
#include <string>
#include "GameInfo.h"
#include "Chessboard.hpp"
#include "Moviment.hpp"

using namespace std;


typedef enum {
    white,
    black
} jugador;


class CurrentGame {

public:
    CurrentGame() { m_pos.setPosX(NUM_X); m_pos.setPosY(NUM_Y); m_posBool = false; m_color = false; }
    
    void init(GameMode mode, const string& intitialBoardFile, const string& movementsFile);
	bool updateAndRender(int mousePosX, int mousePosY, bool mouseStatus);
    void end();  
    
    void interpretaTurno();
    void cambiaTurno();
    
private:
    GameMode modoJuego;
    string ficheroSiNormal;     //dos atributos para manejar END. El primero para guardar el modo, el segundo para que en caso de normal sepamos donde guardar los datos 

    Chessboard m_board;
    queue <Moviment> m_moviment;
    bool m_posBool;
    ChessPosition m_pos;
    Piece m_piecePos;
    VecOfPositions m_posicions;
    bool m_color;               // false-> blanc  / true-> negre  

    jugador m_torn;


    
};

#endif /* CurrentGame_hpp */
