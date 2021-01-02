#include "ttyInterface.h"

using namespace std;

ttyInterface::ttyInterface (chessboard *c) {
	chess = c;
}

ttyInterface::~ttyInterface () { }

void ttyInterface::parser (char *str) {
	int y, inity;
	char x, initx;
	if (strncmp (str, "move", 4) == 0) {
		sscanf(str, "move %c%d %c%d", &initx, &inity, &x, &y);
		if (initx < 'A' || initx > 'H' || x < 'A' || x > 'H'
		|| inity < 1 || inity > 8 || y < 1 || y > 8) {
			cout << "les coordonnées sont incorrectes\n";
			return;
		}
		chess->move_piece ((int) initx - 'A', 8 - inity, (int) x - 'A', 8 - y);
		
	} else if (strncmp (str, "petit rock", 10) == 0) {
		//TODO
	} else if (strncmp (str, "grand rock", 10) == 0) {
		//TODO
	} else if (strncmp (str, "surrender", 9) == 0) {
		//TODO
	} else {
		cout << "commande inconnue\n";
	}
}














