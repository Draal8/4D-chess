#ifndef H_PLAYER
	#define H_PLAYER

#include <iostream>
class player;
struct S_passant;
#include "piece.h"

struct S_passant {
	bool actif;
	int x;
	int y;
};

class player {
	public:
	player(char col);
	~player();
	
	//void turn();
	
	//Getter/Setters
	char get_color ();
	struct S_passant get_S_pass ();
	void set_S_pass (bool a, int x, int y);
	bool get_castling (int mode);
	void set_castling (int mode, int value);
	int get_rewind_timeout ();
	void set_rewind_timeout (int time);
	
	private:
	char color;
	struct S_passant S_pass;
	int rewind_timeout = 0;
	bool b_castling = true;
	bool l_castling = true;
};

#endif
