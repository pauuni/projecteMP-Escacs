//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "CurrentGame.hpp"
#include "GameInfo.h"
#include "../GraphicManager.h"
#include <Windows.h>


/*CurrentGame::CurrentGame()
{

} */ 

void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)//initial(inicial) Board(taular) File , movements(moviments) File
{
    modoJuego = mode;
    m_board.LoadBoardFromFile(intitialBoardFile);
    switch (mode)
    {
    case GM_NORMAL:
    {
        //guardar(aplicar en el tauler) movementsFile
        
        ficheroSiNormal = movementsFile;
    }
        break;

    case GM_REPLAY:
    {
        //preparar per mostrar per pantalla movementsFile
        ifstream fitxer;
        fitxer.open(movementsFile);
        if (fitxer.is_open())
        {
            string line;
            getline(fitxer, line);
            while (!fitxer.eof())
            {
                if (line != "")
                {
                    Moviment m(line[0], line[1] ,line[3] ,line[4]);
                    m_moviment.push(m);
                    getline(fitxer, line);
                }

            }
        }

    }
        break;
    }
}

void CurrentGame::end()
{
    if (modoJuego == GM_NORMAL)
    {
        ofstream fitxer;
        string fich = ficheroSiNormal;
        Moviment v;
        fitxer.open(fich);
        if (fitxer.is_open())
        {
            int n = 0;
            while (n < m_moviment.size())
            {
                //obtenir valor per escriure
                v = m_moviment.front();
                fitxer << v.getXInici() << v.getYInici() << v.getXFinal() << v.getYFinal();
            }
            fitxer.close();
        }
    }
}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus) 
{
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);

    if (modoJuego == GM_NORMAL)
    {
        GraphicManager::getInstance()->drawFont(FONT_RED_30, 20, SCREEN_SIZE_Y - 200, 1, "Game Mode: Normal Play");
    }
    else
    {
        GraphicManager::getInstance()->drawFont(FONT_RED_30, 20, SCREEN_SIZE_Y - 200, 1, "Game Mode: RePlay");
    }
    m_board.Render();
    if (modoJuego == GM_REPLAY)
    {   //EN TOERIA DEBERIA YA IR BIEN SIN CONSIDERAR LOS TURNOS DE BLANCO O NEGRO PUES PARTIMOS DE LA BASE QUE EL DOCUMENTO ESTE BIEN Y SOLAMENTE RECREA LOS MOVIMIENTOS
        if (mouseStatus)
        {
            int i = m_moviment.size();
            
                Moviment v = m_moviment.front();
                ChessPosition inici, final;
                inici.setPosX(v.getXInici());
                inici.setPosY(v.getYInici());

                ChessPieceType tipo = m_board.GetPieceTypeAtPos(inici);
                ChessPieceColor color = m_board.GetPieceColorAtPos(inici);
                m_board.setPiece(v.getXFinal(), v.getYFinal(), tipo, color);
                m_board.setPiece(v.getXInici(), v.getYInici(), CPT_EMPTY, CPC_NONE);
                Sleep (500);
        }
        return false;
    }
    else
    {
        if (mouseStatus)
        {
            m_posBool = false;
        }
        if ((mouseStatus) && ((mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y)) && ((mousePosX <= (CELL_INIT_X + CELL_W * NUM_X)) && (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_Y))))
        {


            bool esta = false;
            int i = 0;
            int x = ((mousePosX - CELL_INIT_X - 2) / CELL_W);
            int y = (-((mousePosY - CELL_INIT_Y - 2) / CELL_H) + (NUM_Y - 1));
            while (!esta && i < m_posicions.size())
            {
                if ((m_posicions[i].getPosX() == x) && (m_posicions[i].getPosY() == y))
                {
                    esta = true;
                }
                i++;
            }

            if (esta)
            {
                //moure fitxa nomes a la memoria
                Piece p = m_board.getPiece(m_pos.getPosX(), m_pos.getPosY());
                m_board.setPiece(x, y, p.getChessPieceType(), p.getChessPieceColor());
                m_board.setPiece(m_pos.getPosX(), m_pos.getPosY(), CPT_EMPTY, CPC_NONE);
                // /\

                m_posicions.resize(0);
            }
            else
            {
                m_pos.setPosX((mousePosX - CELL_INIT_X - 2) / CELL_W);
                m_pos.setPosY(-((mousePosY - CELL_INIT_Y - 2) / CELL_H) + (NUM_Y - 1));
                m_posicions = m_board.GetValidMoves(m_pos);
                m_posBool = true;
            }


        }
        if (m_posBool)
        {
            //GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X - 3 + (m_pos.getPosX() * CELL_W) , CELL_INIT_Y + 4 + ((-m_pos.getPosY() + (NUM_Y - 1)) * CELL_H));
            m_board.RenderMoviments(m_posicions, m_pos);
        }



        return false;
    }
}




void CurrentGame::cambiaTurno()
{
    if (torn == white)
        torn = black;
    else
        torn = white;
}
