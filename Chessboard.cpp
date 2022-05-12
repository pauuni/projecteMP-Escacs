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

ChessPieceColor Chessboard::readColor(char c)
{
    if (c == '1')
        return CPC_Black;
    else
        if (c == '0')
            return CPC_White;
}

ChessPieceType Chessboard::readType(char c)
{
    switch (c)
    {
    case 'R': return CPT_King;
        break;
    case 'D': return CPT_Queen;
        break;
    case 'T': return CPT_Rook;
        break;
    case 'A': return CPT_Bishop;
        break;
    case 'C': return CPT_Knight;
        break;
    case 'P': return CPT_Pawn;
        break;
    default: return CPT_EMPTY;
        break;
    }
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
    //cout << "[[[[ " << path << " ]]]]";
    file.open(path);
    if (file.is_open()) {//read every piece

        /*cout << "1";  //no s'ha llejit ninguna linea no pots guardar res
        col = readCol(line[4]); //'0. Rb1' llegeix b
        cout << "2";
        row = readRow(line[5]);//llegeix 1
        cout << "3";
        m_board[col][row].setColor(readColor(line[0])); //escriu color
        m_board[col][row].setType(readType(line[3])); //escriu tipus
        //*/
        //cout << "4";
        while (/* && */!file.eof()) { //potser no esta detectant el final de fitxer
            getline(file, line);
            col = readCol(line[4]); //'0. Rb1' llegeix b
            row = readRow(line[5]);//llegeix 1
            cout << "[" << col << "," << row << "]";
            ChessPieceColor h = readColor(line[0]);
            ChessPieceType j = readType(line[3]);
            cout << "[" << h << "," << j << "]:" << line << ";";
            m_board[col][row].setColor(h); //escriu color
            m_board[col][row].setType(j); //escriu tipus

        }
        //*/
    }

    file.close();
    //cout << endl;
    ToString();
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
    ChessPieceType type = m_board[y][x].getChessPieceType();
    ChessPieceColor color = m_board[y][x].getChessPieceColor();

    //cout << "[[[[1";

    switch (type)
    {
    case CPT_King:
        //cout << ",2";
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
        //cout << ",3";

    case CPT_Rook:
        //cout << ",4";
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
        //cout << ",5";

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
        //cout << ",6";
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
        //cout << "!" << color << "!";
        if (color == CPC_NONE)
        {
            //cout << "No se que esta pasant pero no funciona be!!";
        }
        else
        {
            if (color == CPC_White)
            {
                //cout << "No se que esta pasa!!";
                suma1 = 1;
            }
            if (color == CPC_Black)
            {
                suma1 = -1;
                //cout << "No se que esta pasa!!";
            }
            //Y_ = y + suma1;
        }
        //cout << ",7";

        //int suma1;

        /*switch (color)
        {
        case CPC_White:
            intColor = 1;
            cout << "{" << y << "," << intColor << "}";
            //Y_ = y + 1;//intColor;
            //X_ = x;
            break;
        case CPC_Black:
            intColor = -1;
            cout << "{" << y << "," << intColor << "}";
            //Y_ = y - 1;// + intColor;
            //X_ = x;
            break;
        }*/
        if (color == CPC_White)
        {
            suma1 = int(1);
            //cout << "{" << y << "," << suma1 << "}";
        }
        else
        {
            if (color == CPC_Black)
            {
                suma1 = int(-1);
                //cout << "{" << y << "," << suma1 << "}";
            }
        }

        Y_ = y + suma1;
        //cout << ".1";// << "(" << intColor << ")";
        
        X_ = x;

        //cout << "*";
        int a, b;
        //cout << "*" << y << "," << suma1 << "(" << Y_ << "," << X_ << ")";
        ChessPieceType c = m_board[Y_][X_].getChessPieceType();
        //cout << "*";
        b = c;
        //cout << "*";
        a = CPT_EMPTY;
        //cout << "*";
        bool f = (a == b);
        //cout << "*";
        
        //cout << ".2";
        
        //cout << "(" << f << ")";
        if (CPT_EMPTY == m_board[Y_][X_].getChessPieceType())
        {
            afejirPosicioIf(posicions, X_, Y_);
        }

        //cout << ".3";

        /*switch (color)// no cambia la variable en ningun moment 
        {
        case CPC_White:
            intColor = 1;
            //Y_ = y + 1;//intColor;
            //X_ = x + 1;
            break;
        case CPC_Black:
            intColor = -1;
            //Y_ = y -1;// +intColor;
            //X_ = x + 1;
            break;
        }
        //*/
        //cout << ".4";

        //Y_ = y + intColor;// no fa falta
        X_ = x + 1;

        //cout << ".45";

        for (int l = 0; l < 2; l++)
        {
            if (l == 1)
            {
                //Y_ = y + intColor;  //no fa falta no?
                X_ = x - 1;
            }

            //cout << ".5";
            if (CPC_NONE != m_board[Y_][X_].getChessPieceColor() && color != m_board[Y_][X_].getChessPieceColor())
                afejirPosicioIf(posicions, X_, Y_);

        }
        //cout << ".6";

        break;
    }

    //cout << "]]]]";

    return posicions;
}

string Chessboard::ToString()
{
    char a, b;
    cout << endl;

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
    cout << endl;

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