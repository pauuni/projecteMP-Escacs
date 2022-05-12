
#include "Chessboard.hpp"
#include <iostream>
using namespace std;

int main()
{

	VecOfPositions vector;
	ChessBoard vector1;
	ChessPosition v1;
	v1.setPosX(4);
	v1.setPosY(4);
	string v = vector1.ToString();
	cout << endl;
	cout << endl;
	cout << endl;
	vector = vector1.GetValidMoves(v1);
	cout << endl;
	cout << endl;
	cout << endl;
	v = vector1.ToString();
	cout << endl;
	cout << endl;
	cout << endl;
	for (int i = 0; i < vector.size(); i++)
	{
		cout << "(" << vector[i].getPosX() << "," << vector[i].getPosY() << ")";
	}
	return 0;
}