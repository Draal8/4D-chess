#include "piece.h"

//test si piece en (x,y+1)
//renvoie 1 si piece adverse 0 si aucune piece et -1 si piece alliée

using namespace std;

piece::piece (char name, char coul, int x, int y) {
	couleur = coul;
	value = name;
	posx = x;
	posy = y;
}

piece::~piece () { }

char piece::get_value () { return value; }
char piece::get_color () { return couleur; }

bool piece::deplacement (chessboard *c, int x, int y) {
	if (!this->test_deplacement(c,x,y)) {
		cout << "\ndeplacement illégal\n";
		return false;
	}
	posx = x;
	posy = y;
	return true;
}

bool piece::test_deplacement (chessboard *c, int x, int y) {
	cout << "erreur gros" << c << " " << x << " " << y << " " << value << endl;
	return false;
}

bool piece::tour_rencontre_piece (chessboard *c, int x, int y) {
	cout << "tour_recontre_piece" << endl;
	int i;
	if (x != posx) {
		cout << "x et posx :" << x << "-" << posx << endl;
		int signe = (posx-x) / abs(posx-x); //= 1 ou -1
		for (i = posx-signe; i != x; i = i - signe) {
			if (c->piece_in(i,y))
				return true;
		}
	} else {
		cout << "y:" << y << " et posy:" << posy << endl;
		int signe = (posy-y) / abs(posy-y);
		cout << "signe = " << signe << endl;
		for (i = posy-signe; i != y; i = i - signe) {
			cout << "piece_in : " << c->piece_in(x,i) << endl;
			if (c->piece_in(x,i)) {
				cout << "trouve en " << i << endl;
				return true;
			}
		}
	}
	return false;
}
/*
bool piece::fou_rencontre_piece (int x, int y) {
	int i, j;
	int signex = (posx-x) / abs(posx-x); //= 1 ou -1
	int signey = (posy-y) / abs(posy-y);
	j = posy+1;
	for (i = posx+1; i != x; i = i - signex) {
		j = j - signey;
		if (piece_en(x,i))
			return false;
	}
	return true;
}*/

king::king (char coul, int x, int y) : piece(KING, coul, x, y) {}

bool king::test_deplacement (chessboard *c, int x, int y) {
	cout << "test deplacement roi" << endl;
	(void) c;
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	if (abs(posx-x) == 1 || abs(posy-y) == 1)
		return true;
	return false;
}

queen::queen (char coul, int x, int y) : piece(QUEEN, coul, x, y) {}

/*
bool queen::test_deplacement (int x, int y) {
	cout << "test deplacement reine" << endl;
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	if (x == posx && y == posy)
		return false;
	if (x == posx || y == posy) {	//pas besoin de tester y != posy ou x != posx a cause le condition au-dessus
		tour_recontre_piece (x,y);
		return true;
	}
	if (abs(posx-x) == abs(posy-y)) {
		fou_rencontre_piece (x,y);
		return true;
	}
	return false;
}*/

bishop::bishop (char coul, int x, int y) : piece(BISHOP, coul, x, y) {}

/*
bool bishop::test_deplacement (int x, int y) {
 	cout << "test deplacement reine" << endl;
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	if (x == posx && y == posy)
		return false;
	if (x == posx || y == posy)	//pas besoin de tester y != posy ou x != posx a cause le condition au-dessus
		return true;
	if (abs(posx-x) == abs(posy-y))
		return true;
	return false;
}*/

knight::knight (char coul, int x, int y) : piece(KNIGHT, coul, x, y) {}

/*
bool knight::test_deplacement (int x, int y) {
	cour << "test deplacement cavalier" << endl;
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	if (x == posx && y == posy)
		return false;
	if ((abs(posx-x) == 2 && abs(posy-y) == 1) ||
	(abs(posy-y) == 2 && abs(posx-x) == 1)) {
		return true;
	}
	return false;
}*/

rook::rook (char coul, int x, int y) : piece(ROOK, coul, x, y) {}

bool rook::test_deplacement (chessboard *c, int x, int y) {
	cout << "test deplacement tour" << endl;
	(void) c;
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	if (x == posx && y == posy)
		return false;
	if (x == posx || y == posy)	//pas besoin de tester y != posy ou x != posx a cause le condition au-dessus
		if (!tour_rencontre_piece(c, x, y) && c->couleur_in(x,y) != get_color())
			return true;
	return false;
}

pawn::pawn (char coul, int x, int y) : piece(PAWN, coul, x, y) {}

bool pawn::test_deplacement (chessboard *c, int x, int y) {
	cout << "test deplacement piont" << endl;
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	
	if (abs(posy-y) == 1) {
		if (posy-y > 0 && couleur == 'B')
			return false;
		if (posy-y < 0 && couleur == 'W')
			return false;
		if (posx == x) {
			if (!c->piece_in(x, y))
				return true;
		} else if (c->piece_in(x, y)) {
			if (c->pieces[y][x]->get_color() == couleur) {
				return false;
			} else {
				return true;
			}
		}
	}
	
	return false;
}

