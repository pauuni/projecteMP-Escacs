//
//  Chessboard.cpp
//

#ifndef ChessBoard_CPP
#define ChessBoard_CPP

#include "Chessboard.hpp"

Chessboard::Chessboard()
{

    for (int i = 0; i < NUM_COLS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            m_board[i][j].setChessPieceType(CPT_EMPTY);
            m_board[i][j].setChessPieceColor(CPC_NONE);
        }
    }
}

ChessPieceType Chessboard::GetPieceTypeAtPos(const ChessPosition& pos) const //s'hauria de comprimir
{
    int y = pos.getPosY();
    int x = pos.getPosX();
    ChessPieceType tipo = m_board[x][y].getChessPieceType();
    return tipo;
}

ChessPieceColor Chessboard::GetPieceColorAtPos(const ChessPosition& pos) const //s'hauria de comprimir
{
    int y = pos.getPosY();
    int x = pos.getPosX();
    ChessPieceColor color = m_board[x][y].getChessPieceColor();
    return color;
}

ifstream& operator>>(ifstream& input, ChessPieceType& tipus)
{
    ChessPieceType type;
    input >> type;
    tipus = type;
    return input;
}

ostream& operator<<(ostream& output, ChessPosition& pos)
{
    output << "(" << pos.getPosX() << "," << pos.getPosY() << ")";
    return output;
}

ifstream& operator>>(ifstream& input, ChessPieceColor& color)
{
    ChessPieceColor Color;
    input >> Color;
    color = Color;
    return input;
}

void Chessboard::LoadBoardFromFile(const string& path)  //esto con ifstream para leer de documento. 
{
    ChessPieceColor PieceColor;
    ChessPieceType PieceType;
    string line;
    ifstream file;
    int col;//char
    int row;
    file.open(path);
    if (file.is_open()) {//read every piece

        col = readCol(line[4]); //'0. Rb1' llegeix b
        row = readRow(line[5]);//llegeix 1
        m_board[col][row].setColor(readColor(line[0])); //escriu color
        m_board[col][row].setType(readType(line[3])); //escriu tipus
        while (getline(file, line) && !file.eof()) { //potser no esta detectant el final de fitxer
            col = readCol(line[4]); //'0. Rb1' llegeix b
            row = readRow(line[5]);//llegeix 1
            m_board[col][row].setColor(readColor(line[0])); //escriu color
            m_board[col][row].setType(readType(line[3])); //escriu tipus

        }

    }

    file.close();
}
int Chessboard::correctXCoordenate(int x)
{
    return x - 1;
}
int Chessboard::stringToYCoordenate(string strin)
{//int y = strin - 'a'; //diria que fa al mateix pero mes curt (potser sa de modificar algo)( si no funciona, s'ha de pasar a char per caracters i costruir el numero)
    if (strin == "a")
    {
        return 0;
    }
    else if (strin == "b")
    {
        return 1;
    }
    else if (strin == "c")
    {
        return 2;
    }
    else if (strin == "d")
    {
        return 3;
    }
    else if (strin == "e")
    {
        return 4;
    }
    else if (strin == "f")
    {
        return 5;
    }
    else if (strin == "g")
    {
        return 6;
    }
    else if (strin == "h")
    {
        return 7;
    }
}
bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)
{

    int x = posFrom.getPosX(), y = posFrom.getPosY();
    char type = m_board[y][x].getChessPieceType();
    char color = m_board[y][x].getChessPieceColor();

    VecOfPositions vecContiene;
    vecContiene = GetValidMoves(posFrom);

    int i = 0;
    bool fiWhile = false;
    while ((i < vecContiene.size() && !fiWhile))
    {
        if ((posTo.getPosX() == vecContiene[i].getPosX()) && (posTo.getPosX() == vecContiene[i].getPosX()))
        {

            m_board[posTo.getPosX()][posTo.getPosY()] = m_board[x][y];
            m_board[x][y].setChessPieceColor(CPC_NONE);
            m_board[x][y].setChessPieceType(CPT_EMPTY);
            //si posTo esta dentro de vecContiene return true IIIIIII el mboard de posFrom se traslada a posTo y se pone todo null en el mboard de posFrom
            return true;
        }
        i++;
    }
    return false;      //Si llega aquí es que no hay dentro del vector de movimientos validos de ese ChessPosition ( en getValid se hayara el tipo y color de esa posicion)

}

VecOfPositions Chessboard::GetValidMoves(const ChessPosition& pos)//separar per parts
{
    VecOfPositions posicions;
    int x = pos.getPosX(), y = pos.getPosY(), Y_, X_, suma1, suma2;
    bool fiWhile1, fiWhile1_, fiWhile2;
    char type = m_board[y][x].getChessPieceType();
    char color = m_board[y][x].getChessPieceColor();

    switch (type)
    {
    case CPT_King:
        Y_ = y - 1;
        while (Y_ <= (y + 1))
        {
            X_ = x - 1;
            while (X_ <= (x + 1))
            {
                if ((m_board[Y_][X_].getChessPieceColor() != color))
                    afejirPosicioIf(posicions, X_, Y_);

                X_++;
                if (Y_ == y)  //treure pocicio actual
                    X_++;
            }
            Y_++;
        }

        break;
    case CPT_Queen:

    case CPT_Rook:
        suma1 = 1;

        fiWhile1 = false;   //Executar 2 cops
        do {
            fiWhile1 = !fiWhile1;

            Y_ = y + suma1;
            fiWhile1_ = true;
            while (fiWhile1_ && Y_ >= 0 && Y_ < NUM_COLS)
            {
                if (m_board[Y_][x].getChessPieceType() == CPT_EMPTY)
                {
                    afejirPosicio(posicions, x, Y_);
                    Y_ += suma1;
                }
                else
                {
                    if (CPC_NONE != m_board[Y_][x].getChessPieceColor() && color != m_board[Y_][x].getChessPieceColor())
                        afejirPosicio(posicions, x, Y_);

                    fiWhile1_ = false;
                }
            }
            suma1 = -1;
        } while (fiWhile1);

        suma1 = 1;

        do {
            fiWhile1 = !fiWhile1;   //Executar 2 cops

            Y_ = x + suma1;
            fiWhile1_ = true;
            while (fiWhile1_ && Y_ >= 0 && Y_ < NUM_ROWS)
            {
                if (m_board[y][Y_].getChessPieceType() == CPT_EMPTY)
                {
                    afejirPosicio(posicions, Y_, y);
                    Y_ += suma1;
                }
                else
                {
                    if (CPC_NONE != m_board[y][Y_].getChessPieceColor() && color != m_board[y][Y_].getChessPieceColor())
                        afejirPosicio(posicions, Y_, y);

                    fiWhile1_ = false;
                }
            }
            suma1 = -1;
        } while (fiWhile1);

        if (type != CPT_Queen)
            break;
    case CPT_Bishop:

        suma1 = 1;

        fiWhile1 = false;   //Executar 2 cops
        do {
            fiWhile1 = !fiWhile1;

            suma2 = 1;

            fiWhile2 = false;   //Executar 2 cops
            do {
                fiWhile2 = !fiWhile2;

                Y_ = x + suma2;
                X_ = y + suma1;
                fiWhile1_ = true;
                while (fiWhile1_ && (X_ >= 0 && X_ < NUM_ROWS) && (Y_ >= 0 && Y_ < NUM_COLS))
                {
                    if (m_board[X_][Y_].getChessPieceType() == CPT_EMPTY)
                    {
                        afejirPosicio(posicions, X_, Y_);
                        Y_ += suma2;
                        X_ += suma1;
                    }
                    else
                    {
                        if (CPC_NONE != m_board[Y_][X_].getChessPieceColor() && color != m_board[Y_][X_].getChessPieceColor())
                            afejirPosicio(posicions, X_, Y_);

                        fiWhile1_ = false;
                    }
                }

                suma2 = -1;
            } while (fiWhile2);

            suma1 = -1;
        } while (fiWhile1);

        break;
    case CPT_Knight:
        suma1 = 1;

        fiWhile1 = false;   //Executar 2 cops
        do {
            fiWhile1 = !fiWhile1;

            for (int i = 0; i < 4; i++)
            {
                switch (i)
                {
                case 0:
                    Y_ = y + (2 * suma1);
                    X_ = x - 1;
                    break;
                case 1:
                    X_ += 2;
                    break;
                case 2:
                    Y_ = y - 1;
                    X_ = x + (2 * suma1);
                    break;
                case 3:
                    Y_ += 2;
                    break;
                }

                if (color != m_board[Y_][X_].getChessPieceColor())
                    afejirPosicioIf(posicions, X_, Y_);

            }

            suma1 = -1;
        } while (fiWhile1);

        break;
    case CPT_Pawn:

        switch (color)
        {
        case CPC_White:
            suma1 = 1;
            break;
        case CPC_Black:
            suma1 = -1;
            break;
        }

        Y_ = y + suma1;
        X_ = x;

        if (CPT_EMPTY == m_board[Y_][X_].getChessPieceType())
            afejirPosicioIf(posicions, X_, Y_);

        Y_ = y + suma1;
        X_ = x + 1;

        for (int l = 0; l < 2; l++)
        {
            if (l == 1)
            {
                Y_ = y + suma1;
                X_ = x - 1;
            }

            if (CPC_NONE != m_board[Y_][X_].getChessPieceColor() && color != m_board[Y_][X_].getChessPieceColor())
                afejirPosicioIf(posicions, X_, Y_);

        }

        break;
    }

    return posicions;
}

string Chessboard::ToString()
{
    char a, b;

    for (int i = (NUM_COLS - 1); i >= 0; i--)
    {
        cout << i;
        for (int j = 0; j < NUM_ROWS; j++)
        {
            a = m_board[i][j].getChessPieceColor();
            b = m_board[i][j].getChessPieceType();
            cout << " " << a << b;
        }
        cout << endl;
    }
    cout << "  0  1  2  3  4  5  6  7";

    return "Hola";
}



void Chessboard::setPiece(int col, int row, ChessPieceType  tipo, ChessPieceColor color)
{
    m_board[col][row].setChessPieceType(tipo);
    m_board[col][row].setChessPieceColor(color);
}

void afejirPosicio(VecOfPositions& vec, int x, int y)
{
    vec.resize((vec.size() + 1));
    vec[(vec.size() - 1)].setPosX(x);
    vec[(vec.size() - 1)].setPosY(y);
}

void afejirPosicioIf(VecOfPositions& vec, int x, int y)
{
    if ((y >= 0 && y < NUM_COLS) && (x >= 0 && x < NUM_ROWS))
    {
        vec.resize((vec.size() + 1));
        vec[(vec.size() - 1)].setPosX(x);
        vec[(vec.size() - 1)].setPosY(y);
    }
}
#endif