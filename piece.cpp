#include "piece.h"

//test si piece en (x,y+1)
//renvoie 1 si piece adverse 0 si aucune piece et -1 si piece alliée

using namespace std;

/**********************************************************
						Class Piece
**********************************************************/

piece::piece (char name, char coul, int x, int y) {
	couleur = coul;
	value = name;
	posx = x;
	posy = y;
}

piece::~piece () { }

char piece::get_value () { return value; }
char piece::get_color () { return couleur; }
int piece::get_y () { return posy; }
int piece::get_x () { return posx; }

bool piece::test_promote() { return false; }
bool pawn::test_promote() { return (posx == 0 || posx == 7); }

bool piece::deplacement (chessboard *c, int x, int y) {
	if (!this->test_deplacement(c,x,y)) {
		cout << "\ndeplacement illégal\n";
		return false;
	}
	
	posx = x;
	posy = y;
	return true;
}

void piece::fdeplacement (int x, int y) {
	posx = x;
	posy = y;
}

bool piece::test_deplacement (chessboard *c, int x, int y) {
	cout << "erreur surcharge" << c << " " << x << " " << y << " " << value << endl;
	return false;
}

bool piece::tour_rencontre_piece (chessboard *c, int x, int y) {
	int i;
	if (x != posx) {
		int signe = (posx-x) / abs(posx-x); //= 1 ou -1
		for (i = posx-signe; i != x; i = i - signe) {
			if (c->piece_in(i,y))
				return true;
		}
	} else {
		int signe = (posy-y) / abs(posy-y);
		for (i = posy-signe; i != y; i = i - signe) {
			if (c->piece_in(x,i)) {
				return true;
			}
		}
	}
	return false;
}

bool piece::fou_rencontre_piece (chessboard *c, int x, int y) {
	int i, j;
	int signex = (posx-x) / abs(posx-x); //= 1 ou -1
	int signey = (posy-y) / abs(posy-y);
	j = posy-signey;
	for (i = posx-signex; i != x; i = i - signex) {
		if (c->piece_in(i,j))
			return true;
		j = j - signey;
	}
	return false;
}


/**********************************************************
						Class King
**********************************************************/

king::king (char coul, int x, int y) : piece(KING, coul, x, y) {}

king::~king () {
	value = NO_VALUE;
}

bool king::test_deplacement (chessboard *c, int x, int y) {
	(void) c;
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	if (abs(posx-x) == 1 || abs(posy-y) == 1)
		return true;
	return false;
}


/**********************************************************
						Class Queen
**********************************************************/

queen::queen (char coul, int x, int y) : piece(QUEEN, coul, x, y) {}

queen::~queen () {
	value = NO_VALUE;
}

bool queen::test_deplacement (chessboard *c, int x, int y) {
	piece *p;
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	if (x == posx && y == posy)
		return false;
	if (x == posx || y == posy) {	//pas besoin de tester y != posy ou x != posx a cause le condition au-dessus
		if (!tour_rencontre_piece (c,x,y)) {
			p = c->get_piece(x,y);
			if (p != NULL && p->get_color() != couleur)
				return true;
			if (p == NULL) return true;
		}
	}
	if (abs(posx-x) == abs(posy-y)) {
		if (!fou_rencontre_piece (c,x,y)) {
			p = c->get_piece(x,y);
			if (p != NULL && p->get_color() != couleur)
				return true;
			if (p == NULL) return true;
		}
	}
	return false;
}


/**********************************************************
						Class Bishop
**********************************************************/

bishop::bishop (char coul, int x, int y) : piece(BISHOP, coul, x, y) {}

bishop::~bishop () {
	value = NO_VALUE;
}

bool bishop::test_deplacement (chessboard *c, int x, int y) {
 	(void) c;
 	piece *p;
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	if (x == posx && y == posy)
		return false;
	if (abs(posx-x) == abs(posy-y)) {
		if (!fou_rencontre_piece(c, x, y)) {
			p = c->get_piece(x,y);
			if (p != NULL && p->get_color() != couleur)
				return true;
			if (p == NULL) return true;
		}
	}
	return false;
}


/**********************************************************
						Class Knight
**********************************************************/

knight::knight (char coul, int x, int y) : piece(KNIGHT, coul, x, y) {}

knight::~knight () {
	value = NO_VALUE;
}

bool knight::test_deplacement (chessboard *c, int x, int y) {
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	if (x == posx && y == posy)
		return false;
	if ((abs(posx-x) == 2 && abs(posy-y) == 1) ||
	(abs(posy-y) == 2 && abs(posx-x) == 1)) {
		if (c->piece_in (x, y)) {
			piece * p = c->get_piece (x, y);
			if (p->get_color() == couleur)
				return false;
		}
		return true;
	}
	return false;
}


/**********************************************************
						Class Rook
**********************************************************/

rook::rook (char coul, int x, int y) : piece(ROOK, coul, x, y) {}

rook::~rook () {
	value = NO_VALUE;
}

bool rook::test_deplacement (chessboard *c, int x, int y) {
	(void) c;
	piece *p;
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	if (x == posx && y == posy)
		return false;
	if (x == posx || y == posy)	//pas besoin de tester y != posy ou x != posx a cause le condition au-dessus
		if (!tour_rencontre_piece(c, x, y)) {
			p = c->get_piece(x,y);
			if (p != NULL && p->get_color() != couleur)
				return true;
			if (p == NULL) return true;
		}
	return false;
}


/**********************************************************
						Class Pawn
**********************************************************/

pawn::pawn (char coul, int x, int y) : piece(PAWN, coul, x, y) {}

pawn::~pawn () {
	value = NO_VALUE;
}

bool pawn::test_deplacement (chessboard *c, int x, int y) {
	bool ret = false;
	
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return false;
	if (posy-y > 0 && couleur == 'B')
		return false;
	if (posy-y < 0 && couleur == 'W')
		return false;
	
	if (abs(posy-y) == 1) {
		
		if (posx == x) {
			if (!c->piece_in(x, y))
				ret = true;
		} else if (c->piece_in(x, y)) {
			piece *p = c->get_piece(x,y);
			if (p->get_color() == couleur) {
				return false;
			} else {
				ret = true;
			}
		}
	} else if (abs(posy-y) == 2) {
		int signe = (posy-y) / abs(posy-y);
		if (posx == x) {
			if (!c->piece_in(x, y) && !c->piece_in(x, y-signe)) {
				ret = true;
				c->double_step(posx, posy);
			}
		}
	}
	
	if (y == 0 || y == 7) {
		c->promotion (this, posx, posy);
	}
	
	return ret;
}


/**********************************************************
						Class En_passant
**********************************************************/

enPassant::enPassant (char coul, int x, int y, piece *p) : piece(EN_PASSANT, coul, x, y) {
	origine = p;
}

enPassant::~enPassant () {
	value = NO_VALUE;
}


