#include "player.h"

player::player (char col) {
	color = col;
	S_pass.actif = false;
}

player::~player () { }

/*void player::turn(chessboard *c) {
	if (S_pass.actif == true) {
		c->kill(c->get_piece(S_pass.x, S_pass.y), 1);
		S_pass.actif = false;
	}
	
	
}*/

//Getters/Setters
char player::get_color () {
	return color;
}

struct S_passant player::get_S_pass () {
	return S_pass;
}

void player::set_S_pass (bool a, int x, int y) {
	S_pass.actif = a;
	S_pass.x = x;
	S_pass.y = y;	
}

bool player::get_castling (int mode) {
	return (mode = 'b')? b_castling : l_castling;
}

void player::set_castling (int mode, int value) {
	(mode = 'b')? b_castling = value : l_castling = value;
}






