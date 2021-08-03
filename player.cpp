#include "player.h"

player::player (char col) {
	color = col;
	S_pass.actif = false;
}

player::~player () { }

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
	return (mode == 'b')? b_castling : l_castling;
}

void player::set_castling (int mode, bool value) {
	(mode == 'b')? b_castling = value : l_castling = value;
}






