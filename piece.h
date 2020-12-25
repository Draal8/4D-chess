#ifndef H_PIECE
	#define H_PIECE
#include <iostream>
#include <cmath>
#include <string>
class piece;	//necessaire de declarer avant chessboard.h
class king;		//car on a une dependance cyclique
class queen;
class bishop;
class knight;
class rook;
class pawn;
#include "chessboard.h"

enum p_value {
	NO_VALUE = '0',			//Default
	KING = 'K',				//Roi
	QUEEN = 'Q',			//Dame
	BISHOP = 'B',			//Fou
	KNIGHT = 'C',			//Cavalier
	ROOK = 'R',				//Tour
	PAWN = 'P'				//Pion
};

class piece {
	public:
	//constructor/destructor
	piece (char name, char coul, int x, int y);
	~piece ();
	
	bool deplacement (chessboard *c, int x, int y);
	
	//accesseurs
	char get_value ();
	char get_color ();
	
	//uniquement accessible par les fils
	protected:
	char couleur;	//'B' ou 'N'
	char value = NO_VALUE;
	int posx;
	int posy;
	
	//test de rencontre de pieces au passage
	bool tour_rencontre_piece (chessboard *c, int x, int y);
	bool fou_rencontre_piece (chessboard *c, int x, int y);
	
	private:
	virtual bool test_deplacement (chessboard *c, int x, int y);
	//void p_die();
	
};

/*
===========================================================
				Specialisation of pieces
===========================================================
*/

class king :public piece {
	public:
	king (char coul, int x, int y);
	bool test_deplacement (chessboard *c, int x, int y);
};

class queen :public piece {
	public:
	queen (char coul, int x, int y);
	bool test_deplacement (chessboard *c, int x, int y);
};

class bishop :public piece {
	public:
	bishop (char coul, int x, int y);
	bool test_deplacement (chessboard *c, int x, int y);
};

class knight :public piece {
	public:
	knight (char coul, int x, int y);
	bool test_deplacement (chessboard *c, int x, int y);
};

class rook :public piece {
	public:
	rook (char coul, int x, int y);
	bool test_deplacement (chessboard *c, int x, int y);
};

class pawn :public piece {
	public:
	pawn (char coul, int x, int y);
	bool test_deplacement (chessboard *c, int x, int y);
};

#endif
