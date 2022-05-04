
#ifndef ChessBoard_CPP
#define ChessBoard_CPP

#include "Chessboard.hpp"

ChessBoard::ChessBoard()
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

ifstream& operator>>(ifstream& input, ChessPieceType& tipus)
{
    ChessPieceType type;
    input >> type;
    tipus = type;
    return input;
}

ifstream& operator>>(ifstream& input, ChessPieceColor& color)
{
    ChessPieceColor Color;
    input >> Color;
    color = Color;
    return input;
}

void ChessBoard::LoadBoardFromFile(const string& path)  //esto con ifstream para leer de documento. 
{
    ifstream fitxer;


    fitxer.open(path);		// preguntar a profesor

    if (fitxer.is_open())
    {
        string c;
        int row, col;
        ChessPieceType tipus;
        ChessPieceColor jug;

        fitxer >> jug >> tipus >> c >> row;

        row = correctXCoordenate(row);
        col = stringToYCoordenate(c);
        setPiece(col, row, tipus, jug);

        while (!fitxer.eof())
        {
            fitxer >> jug >> tipus >> c >> row;

            row = correctXCoordenate(row);
            col = stringToYCoordenate(c);
            setPiece(col, row, tipus, jug);
            //interpretar bien el enunciado y usar MovePiece

        }
        fitxer.close();
    }
}
int ChessBoard::correctXCoordenate(int x)
{
    return x - 1;
}
int ChessBoard::stringToYCoordenate(string strin)
{
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
bool ChessBoard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)
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

VecOfPositions ChessBoard::GetValidMoves(const ChessPosition& pos)//separar per parts
{
    VecOfPositions posicions;
    int x = pos.getPosX(), y = pos.getPosY(), i, j, suma1, suma2;
    bool fiWhile1, fiWhile1_, fiWhile2, fiWhile2_;
    char type = m_board[y][x].getChessPieceType();
    char color = m_board[y][x].getChessPieceColor();

    switch (type)
    {
    case CPT_Rei:
        i = y - 1;
        while (i >= 0 && i < NUM_COLS && i <= (y + 1))
        {
            j = x - 1;
            while (j >= 0 && j < NUM_ROWS && j <= (x + 1))
            {
                if (!(i == y && j == x))
                {
                    if ((i >= 0 && i <= NUM_COLS) && (j >= 0 && j <= NUM_COLS) && (m_board[i][j].getChessPieceColor() != color))
                        afejirPosicio(posicions, j, i);
                }
                j++;
            }
            i++;
        }

        break;
    case CPT_Dama:

    case CPT_Torre:
        suma1 = 1;
        fiWhile1 = false;
        do {
            fiWhile1 = !fiWhile1;
            i = y + suma1;
            fiWhile1_ = true;

            while (fiWhile1_ && i >= 0 && i < NUM_COLS)
            {
                if (m_board[i][x].getChessPieceType() == CPT_EMPTY)
                {
                    afejirPosicio(posicions, x, i);
                    i += suma1;
                }
                else
                {
                    if (CPC_NONE != m_board[i][x].getChessPieceColor() && color != m_board[i][x].getChessPieceColor())
                        afejirPosicio(posicions, x, i);

                    fiWhile1_ = false;
                }
            }
            suma1 = -1;
        } while (fiWhile1);

        suma1 = 1;

        do {
            fiWhile1 = !fiWhile1;
            i = x + suma1;
            fiWhile1_ = true;
            while (fiWhile1_ && i >= 0 && i < NUM_ROWS)
            {
                if (m_board[y][i].getChessPieceType() == CPT_EMPTY)
                {
                    afejirPosicio(posicions, i, y);
                    i += suma1;
                }
                else
                {
                    if (CPC_NONE != m_board[y][i].getChessPieceColor() && color != m_board[y][i].getChessPieceColor())
                        afejirPosicio(posicions, i, y);

                    fiWhile1_ = false;
                }
            }
            suma1 = -1;
        } while (fiWhile1);

        if (type != CPT_Dama)
            break;
    case CPT_Alfil:

        suma1 = 1;
        fiWhile1 = false;

        do {
            fiWhile1 = !fiWhile1;
            suma2 = 1;
            fiWhile2 = false;

            do {
                fiWhile2 = !fiWhile2;
                i = x + suma2;
                j = y + suma1;
                fiWhile1_ = true;

                while (fiWhile1_ && (j >= 0 && j < NUM_ROWS) && (i >= 0 && i < NUM_COLS))
                {
                    if (m_board[j][i].getChessPieceType() == CPT_EMPTY)
                    {
                        afejirPosicio(posicions, j, i);
                        i += suma2;
                        j += suma1;
                    }
                    else
                    {
                        if (CPC_NONE != m_board[i][j].getChessPieceColor() && color != m_board[i][j].getChessPieceColor())
                            afejirPosicio(posicions, j, i);

                        fiWhile1_ = false;
                    }
                }

                suma2 = -1;
            } while (fiWhile2);

            suma1 = -1;
        } while (fiWhile1);

        break;
    case CPT_Cavall:
        suma1 = 1;
        fiWhile1 = false;

        do {
            fiWhile1 = !fiWhile1;

            for (int l = 0; l < 4; l++)
            {
                switch (l)
                {
                case 0:
                    i = y + (2 * suma1);
                    j = x - 1;
                    break;
                case 1:
                    j += 2;
                    break;
                case 2:
                    i = y - 1;
                    j = x + (2 * suma1);
                    break;
                case 3:
                    i += 2;
                    break;
                }

                if ((i >= 0 && i <= NUM_COLS) && (j >= 0 && j <= NUM_ROWS) && color != m_board[i][j].getChessPieceColor())
                    afejirPosicio(posicions, j, i);

            }

            suma1 = -1;
        } while (fiWhile1);

        break;
    case CPT_Peó:
        if (color == CPC_Blanc)
            suma1 = 1;
        if (color == CPC_Negra)
            suma1 = -1;

        i = y + suma1;
        j = x;

        if ((i >= 0 && i < NUM_COLS) && (j >= 0 && j < NUM_ROWS) && CPT_EMPTY == m_board[i][j].getChessPieceType())
            afejirPosicio(posicions, j, i);

        i = y + suma1;
        j = x + 1;

        for (int l = 0; l < 2; l++)
        {
            if (l == 1)
            {
                i = y + suma1;
                j = x - 1;
            }

            if ((i >= 0 && i <= NUM_COLS) && (j >= 0 && j <= NUM_ROWS) && CPC_NONE != m_board[i][j].getChessPieceColor() && color != m_board[i][j].getChessPieceColor())
                afejirPosicio(posicions, j, i);

        }

        break;
    }

    return posicions;
}

string ChessBoard::ToString()
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



void ChessBoard::setPiece(int col, int row, ChessPieceType  tipo, ChessPieceColor color)
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
#endif
