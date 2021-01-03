#ifndef H_TTY_INTERFACE
	#define H_TTY_INTERFACE

#include <iostream>
#include <string>

#include "chessboard.h"

class ttyInterface {
	public :
	ttyInterface (chessboard *c);
	~ttyInterface ();
	
	void play ();
	int parser (char *str);
	void time_travel();
	
	private :
	chessboard *chess;
};

#endif
