#ifndef H_PIECE
	#define H_PIECE
#include <iostream>
#include <cmath>
#include <string>

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
	piece (char name);
	~piece ();
	
	char get_value ();
	int deplacement (int x, int y);
	
	private:
	char value = NO_VALUE;
	int posx;
	int posy;
	
	//void p_die();
	bool test_deplacement (int x, int y);
};

//Specialisation of pieces

class king :public piece {
	public:
	king ();
	
};

class queen :public piece {
	public:
	queen ();
};

class bishop :public piece {
	public:
	bishop ();
};

class knight :public piece {
	public:
	knight ();
};

class rook :public piece {
	public:
	rook ();
};

class pawn :public piece {
	public:
	pawn ();
};

#endif
