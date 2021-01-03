#include "ttyInterface.h"

using namespace std;

ttyInterface::ttyInterface (chessboard *c) {
	chess = c;
}

ttyInterface::~ttyInterface () { }

void ttyInterface::play () {
	char ch, str[255];
	int i, end = 0;
	while (end != -2) {
		ch = getc(stdin);
		for (i = 0; i < 254 && ch != '\0' && ch != '\n'; i++) {
			str[i] = ch;
			ch = getc(stdin);
		}
		str[i] = '\0';
	
		cout << str << endl;
		end = parser(str);
		if (end == 0) {
			chess->print_chessboard2 ();
		}
	}
}


int ttyInterface::parser (char *str) {
	int y, inity;
	char x, initx;
	if (strncmp (str, "move", 4) == 0) {
		sscanf(str, "move %c%d %c%d", &initx, &inity, &x, &y);
		if (initx < 'A' || initx > 'H' || x < 'A' || x > 'H'
		|| inity < 1 || inity > 8 || y < 1 || y > 8) {
			cout << "les coordonnées sont incorrectes" << endl;
			return -1;
		}
		chess->move_piece ((int) initx - 'A', 8 - inity, (int) x - 'A', 8 - y);
		return 0;
	} else if (strncmp (str, "petit rock", 10) == 0) {
		//TODO
	} else if (strncmp (str, "grand rock", 10) == 0) {
		//TODO
	} else if (strncmp (str, "surrender", 9) == 0) {
		return -2;
	} else {
		cout << "commande inconnue" << endl;
		return -1;
	}
}














