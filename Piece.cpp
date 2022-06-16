#ifndef Piece_CPP
#define Piece_CPP

#include "Piece.hpp"
#include "../GraphicManager.h"
#include "ChessPosition.hpp"


void Piece::Render(const int& posX, const int& posY)
{
	IMAGE_NAME piece = IMAGE_BOARD;

    switch (m_type)
    {
    case CPT_King :
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_KING_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_KING_WHITE;
            break;
        }
        break;
    case CPT_Queen :
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_QUEEN_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_QUEEN_WHITE;
            break;
        }
        break;
    case CPT_Rook :
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_ROOK_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_ROOK_WHITE;
            break;
        }
        break;
    case CPT_Bishop :
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_BISHOP_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_BISHOP_WHITE;
            break;
        }
        break;
    case CPT_Knight :
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_KNIGHT_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_KNIGHT_WHITE;
            break;
        }
        break;
    case CPT_Pawn :
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_PAWN_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_PAWN_WHITE;
            break;
        }
        break;
    }

    if(piece != IMAGE_BOARD)
	    GraphicManager::getInstance()->drawSprite(piece,(CELL_INIT_X + (posX * CELL_W)), (CELL_INIT_Y + ((-posY + NUM_Y - 1) * CELL_H)));
}

void Piece::RenderPlus(const int& posX, const int& posY)
{
    IMAGE_NAME piece = IMAGE_BOARD;

    switch (m_type)
    {
    case CPT_King:
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_KING_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_KING_WHITE;
            break;
        }
        break;
    case CPT_Queen:
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_QUEEN_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_QUEEN_WHITE;
            break;
        }
        break;
    case CPT_Rook:
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_ROOK_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_ROOK_WHITE;
            break;
        }
        break;
    case CPT_Bishop:
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_BISHOP_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_BISHOP_WHITE;
            break;
        }
        break;
    case CPT_Knight:
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_KNIGHT_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_KNIGHT_WHITE;
            break;
        }
        break;
    case CPT_Pawn:
        switch (m_color)
        {
        case CPC_Black:
            piece = IMAGE_PIECE_PAWN_BLACK;
            break;
        case CPC_White:
            piece = IMAGE_PIECE_PAWN_WHITE;
            break;
        }
        break;
    }

    if (piece != IMAGE_BOARD)
    {
        //GraphicManager::getInstance()->drawSprite(piece, (CELL_INIT_X + (posX * CELL_W)), (CELL_INIT_Y + ((-posY + NUM_Y - 1) * CELL_H)));
        GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X - 3 + (posX * CELL_W), CELL_INIT_Y + 4 + ((-posY + (NUM_Y - 1)) * CELL_H));
    }
        
}

#endif