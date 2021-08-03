#include <iostream>
#include "piece.h"
#include "chessboard.h"
#include "ttyInterface.h"

using namespace std;

int main() {
	chessboard *c = new chessboard ();
	ttyInterface *t = new ttyInterface (c);
	t->play();
	
	return 0;
}




















