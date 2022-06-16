//
//  Chessboard.cpp
//intercambiar x i y

#ifndef ChessBoard_CPP
#define ChessBoard_CPP

#include "Chessboard.hpp"

Chessboard::Chessboard()
{
    cout << "Chessboard()\n\tIniciar Chessboard:\n";

    for (int j = 0; j < NUM_X; j++)
    {
        for (int i = 0; i < NUM_Y; i++)
        {
            cout << "[" << i << "][" << j << "](y,x):CPT_EMPTY i CPC_NONE\n";
            m_board[i][j].setChessPieceType(CPT_EMPTY);
            m_board[i][j].setChessPieceColor(CPC_NONE);
        }
    }
}

ChessPieceType Chessboard::GetPieceTypeAtPos(const ChessPosition& pos) const //s'hauria de comprimir
{
    cout << "GetPieceTypeAtPos(const ChessPosition& pos) const\n\tTornar tipo de una pocicio:\n";
    int y = pos.getPosY();
    int x = pos.getPosX();
    ChessPieceType tipo = m_board[y][x].getChessPieceType();
    char t = tipo;
    cout << "[" << y << "][" << x << "]:" << t << "\n";
    return tipo;
}

ChessPieceColor Chessboard::GetPieceColorAtPos(const ChessPosition& pos) const //s'hauria de comprimir
{
    cout << "GetPieceColorAtPos(const ChessPosition& pos) const\n\tTornar color de una pocicio:\n";
    int y = pos.getPosY();
    int x = pos.getPosX();
    ChessPieceColor color = m_board[y][x].getChessPieceColor();// la entrada de cordenadas des de el main esta el reves!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    char c = color;
    cout << "[" << y << "][" << x << "]:" << c << "\n";
    return color;
}

ChessPieceColor Chessboard::readColor(char c)
{
    cout << "readColor(char c)\n\tchar-ChessPieceColor:" << c << "\n";
    switch (c)
    {
    case '1' : return CPC_Black;
        break;
    case '0' :return CPC_White;
        break;
    }
            
}

ChessPieceType Chessboard::readType(char c)
{
    cout << "readType(char c)\n\tchar-ChessPieceType:" << c << "\n";
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
    output << "(" << pos.getPosY() << "," << pos.getPosX() << ")";
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
    cout << "LoadBoardFromFile(const string& path)\n\tllejir fitxer:\n";
    ChessPieceColor PieceColor;
    ChessPieceType PieceType;
    string line;
    ifstream file;
    int x;//char
    int y;
    //cout << "[[[[ " << path << " ]]]]";
    file.open(path);
    cout << "Fitxer obert?";
    if (file.is_open()) {//read every piece

        cout << "si;\n";
        //cout << "1";
        while (!file.eof()) { //potser no esta detectant el final de fitxer
            getline(file, line);
            x = readX(line[4]); //'0. Rb1' llegeix b
            y = readY(line[5]);//llegeix 1
            ChessPieceColor color = readColor(line[0]);
            ChessPieceType tipo = readType(line[3]);
            m_board[y][x].setColor(color); //escriu color
            m_board[y][x].setType(tipo); //escriu tipus
            char c = color, t = tipo;//cout
            cout << "[" << y << "," << x << "]" << "c:" << c << ",t:" << t << "]:" << line << ";\n";

        }
    }

    file.close();
    //cout << endl;
    ToString();
}

bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)
{
    cout << "MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)\n\tmoure pesa(crida el GetValidMoves):\n";
    const int x = posFrom.getPosX(), y = posFrom.getPosY();
    const char type = m_board[y][x].getChessPieceType();
    const char color = m_board[y][x].getChessPieceColor();

    VecOfPositions vecContiene = GetValidMoves(posFrom);

    int i = 0;
    bool fiWhile = false;
    while ((i < vecContiene.size() && !fiWhile))
    {
        cout << "Color:" << m_board[y][x].getChessPieceColor() << "  | Tipus:" << m_board[y][x].getChessPieceType() << "  [" << posFrom.getPosY() << "][" << posFrom.getPosX() << "] - > [" << posTo.getPosY() << "][" << posTo.getPosX() << "]";
        // i si: if (posTo == vecContiene[i]), m_board[y][x].setReset();
        
        if ((posTo.getPosX() == vecContiene[i].getPosX()) && (posTo.getPosY() == vecContiene[i].getPosY()))
        {
            cout << "es el escullit";
            m_board[posTo.getPosY()][posTo.getPosX()] = m_board[y][x];
            m_board[y][x].setChessPieceColor(CPC_NONE);
            m_board[y][x].setChessPieceType(CPT_EMPTY);
            //si posTo esta dentro de vecContiene return true IIIIIII el mboard de posFrom se traslada a posTo y se pone todo null en el mboard de posFrom
            return true;
        }
        cout << "Color:" << m_board[y][x].getChessPieceColor() << "  | Tipus:" << m_board[y][x].getChessPieceType() << "] - > [" << "Color:" << m_board[posTo.getPosY()][posTo.getPosX()].getChessPieceColor() << "  | Tipus:" << m_board[posTo.getPosY()][posTo.getPosX()].getChessPieceType();
        i++;
        cout << endl;
    }
    return false;      //Si llega aquí es que no hay dentro del vector de movimientos validos de ese ChessPosition ( en getValid se hayara el tipo y color de esa posicion)

}

VecOfPositions Chessboard::GetValidMoves(const ChessPosition& pos)//separar per parts
{
    cout << "GetValidMoves(const ChessPosition& pos)\n\tmoviments posivles:\n";
    VecOfPositions posicions;
    int x = pos.getPosX(), y = pos.getPosY(), Y_, X_, suma1, suma2;
    bool fiWhile1, fiWhile1_, fiWhile2;
    ChessPieceType type = m_board[y][x].getChessPieceType();
    ChessPieceColor color = m_board[y][x].getChessPieceColor();

    cout << "switch (type:{" << type << "})->";

    switch (type)
    {
    case CPT_King:
        cout << "CPT_King\n";
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
        cout << "CPT_Queen\n";

    case CPT_Rook:
        cout << "CPT_Rook\n";
        suma1 = 1;

        fiWhile1 = false;   //Executar 2 cops
        do {
            fiWhile1 = !fiWhile1;

            Y_ = y + suma1;
            fiWhile1_ = true;
            while (fiWhile1_ && Y_ >= 0 && Y_ < NUM_X)
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
            while (fiWhile1_ && Y_ >= 0 && Y_ < NUM_Y)
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
        cout << "CPT_Bishop\n";

        suma1 = 1;

        fiWhile1 = false;   //Executar 2 cops
        do {
            fiWhile1 = !fiWhile1;

            suma2 = 1;

            fiWhile2 = false;   //Executar 2 cops
            do {
                fiWhile2 = !fiWhile2;

                 X_ = x + suma2;
                 Y_ = y + suma1;
                fiWhile1_ = true;
                while (fiWhile1_ && (X_ >= 0 && X_ < NUM_X) && (Y_ >= 0 && Y_ < NUM_Y))
                {
                    if (m_board[Y_][X_].getChessPieceType() == CPT_EMPTY)
                    {
                        afejirPosicio(posicions, X_, Y_);
                         X_ += suma2;
                         Y_ += suma1;
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
        cout << "CPT_Knight\n";
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
        cout << "CPT_Pawn\n";

        switch (color)
        {
        case CPC_White:
            suma2 = 1; //fila, moure 2
            suma1 = 1;
            break;
        case CPC_Black:
            suma2 = 6; //fila, moure 2
            suma1 = -1;
            break;
        }

        
        Y_ = y + suma1;

        for (X_ = x - 1; X_ < (x + 2); X_++)
        {
            if (CPT_EMPTY == m_board[Y_][X_].getChessPieceType() && X_ == x)
                afejirPosicioIf(posicions, X_, Y_);

            if ((CPC_NONE != m_board[Y_][X_].getChessPieceColor() && color != m_board[Y_][X_].getChessPieceColor()) && X_ != x)
                afejirPosicioIf(posicions, X_, Y_);
        }

        Y_ = y + suma1 + suma1;
        X_ = x;

        if (CPT_EMPTY == m_board[Y_][X_].getChessPieceType() && suma2 == y)
            afejirPosicioIf(posicions, X_, Y_);

        break;
    }

    return posicions;
}

void Chessboard::ToString()
{
    cout << "ToString()\n\tmostre:\n";
    char a, b;
    cout << endl;

    for (int i = (NUM_Y - 1); i >= 0; i--)
    {
        cout << i;
        for (int j = 0; j < NUM_X; j++)
        {
            a = m_board[i][j].getChessPieceColor();
            b = m_board[i][j].getChessPieceType();
            cout << " " << a << b;
            cout << "(" << i << "," << j << ")";
        }
        cout << endl;
    }
    cout << "  0  1  2  3  4  5  6  7";
    cout << endl;

}



void Chessboard::setPiece(int x, int y, ChessPieceType  tipo, ChessPieceColor color)
{
    cout << "setPiece(int x, int y, ChessPieceType  tipo, ChessPieceColor color)\n\set:\n";
    cout << "[" << y << "][" << x << "] tipo:" << tipo << " | color:" << color << "\n";
    m_board[y][x].setChessPieceType(tipo);
    m_board[y][x].setChessPieceColor(color);
    char t = m_board[y][x].getChessPieceType();//cout
    char c = m_board[y][x].getChessPieceColor();//cout
    cout << "[" << y << "][" << x << "] tipo:" << t << " | color:" << c << "\n";
}

void Chessboard::Render()
{
    for (int i = 0; i < NUM_Y; i++)
    {
        for (int j = 0; j < NUM_X; j++)
        {
            m_board[i][j].Render(j, i);
        }
        cout << endl;
    }

}

void Chessboard::RenderMoviments(VecOfPositions posDesti, const ChessPosition& posInicial)
{
    for (vector<ChessPosition>::iterator i = posDesti.begin(); i != posDesti.end(); i++)
    {
        m_board[posInicial.getPosY()][posInicial.getPosX()].RenderPlus(i->getPosX(), i->getPosY());
    }
}

void afejirPosicio(VecOfPositions& vec, int x, int y)
{
    vec.resize((vec.size() + 1));
    vec[(vec.size() - 1)].setPosX(x);
    vec[(vec.size() - 1)].setPosY(y);
}

void afejirPosicioIf(VecOfPositions& vec, int x, int y)
{
    if ((y >= 0 && y < NUM_X) && (x >= 0 && x < NUM_Y))
    {
        vec.resize((vec.size() + 1));
        vec[(vec.size() - 1)].setPosX(x);
        vec[(vec.size() - 1)].setPosY(y);
    }
}

#endif