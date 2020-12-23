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
	chessboard ();
	~chessboard ();
	void init_chessboard ();
	void print_chessboard ();
	int coord_to_index (int x, int y);
	bool piece_in (int x, int y);
	void move_piece (int initx, int inity, int x, int y);
	
	//protected:
	piece *pieces[8][8];		//NULL si vide ou adresse
	
	private:
	bool test_endgame ();
	void endgame ();
	
};

#endif
