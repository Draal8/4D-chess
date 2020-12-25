#ifndef H_CHESSBOARD
	#define H_CHESSBOARD

#include <iostream>
#include <cstring>
class chessboard;
#include "piece.h"

/*
 ||1|2|3|4|5|6|7|8|
A||R|C|B|Q|K|B|C|R|
B||P|P|P|P|P|P|P|P|
C|| | | | | | | | |
D|| | | | | | | | |
E|| | | | | | | | |
F|| | | | | | | | |
G||P|P|P|P|P|P|P|P|
H||R|C|B|Q|K|B|C|R|
*/

class chessboard {
	public:
	//Constructor/Destructor
	chessboard ();
	~chessboard ();
	void init_chessboard ();
	
	//Print chessboard
	void print_chessboard ();
	void print_chessboard2 ();
	int coord_to_index (int x, int y);
	
	//Piece manipulation
	bool piece_in (int x, int y);
	piece *get_piece (int x, int y);
	void move_piece (int initx, int inity, int x, int y);
	//bool test_endgame ();
	
	protected:
	piece *pieces[8][8];		//NULL si vide ou adresse
	
	private:
	int shift_color;
	int shift_nc;
	//void endgame ();
	
};

#endif
