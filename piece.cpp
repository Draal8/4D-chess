#include "piece.h"

//test si piece en (x,y+1)
//renvoie 1 si piece adverse 0 si aucune piece et -1 si piece alliée

using namespace std;

piece::piece (char name) {
	value = name;
}

piece::~piece () { }

char piece::get_value() {
	return value;
}

int piece::deplacement (int x, int y) {
	if (!test_deplacement(x,y)) {
		//catch_error
		return -1;
	}
	//déplacer en x,y
}

king::king () : piece(KING) {}

bool king::test_deplacement (int x, int y) {
	cout << "test deplacement roi" << endl;
	if (x < 0 || y < 0 || x > 8 || y > 8)
		return false;
	if (x == posx && y == posy)
		return false;
	if (x > posx+1 || x < posx -1 || y > posy+1 || y < posy-1)
		return false;
	return true;
}

queen::queen () : piece(QUEEN) {}

//TODO : tester si il y a une piece sur le chemin

bool queen::test_deplacement (int x, int y) {
	cout << "test deplacement reine" << endl;
	if (x < 0 || y < 0 || x > 8 || y > 8)
		return false;
	if (x == posx && y == posy)
		return false;
	if (x == posx || y == posy)	//pas besoin de tester y != posy ou x != posx a cause le condition au-dessus
		return true;
	if (abs(posx-x) == abs(posy-y))
		return true;
	return false;
}

bishop::bishop () : piece(BISHOP) {}

bool bishop::test_deplacement (int x, int y) {
 	cout << "test deplacement reine" << endl;
	if (x < 0 || y < 0 || x > 8 || y > 8)
		return false;
	if (x == posx && y == posy)
		return false;
	if (x == posx || y == posy)	//pas besoin de tester y != posy ou x != posx a cause le condition au-dessus
		return true;
	if (abs(posx-x) == abs(posy-y))
		return true;
	return false;
}

knight::knight () : piece(KNIGHT) {}

bool knight::test_deplacement (int x, int y) {
	cour << "test deplacement cavalier" << endl;
	if (x < 0 || y < 0 || x > 8 || y > 8)
		return false;
	if (x == posx && y == posy)
		return false;
	if ((abs(posx-x) == 2 && abs(posy-y) == 1) ||
	(abs(posy-y) == 2 && abs(posx-x) == 1)) {
		return true;
	}
	return false;
}

rook::rook () : piece(ROOK) {}

bool rook::test_deplacement (int x, int y) {
	cout << "test deplacement tour" << endl;
	if (x < 0 || y < 0 || x > 8 || y > 8)
		return false;
	if (x == posx && y == posy)
		return false;
	if (x == posx || y == posy)	//pas besoin de tester y != posy ou x != posx a cause le condition au-dessus
		return true;
}

pawn::pawn () : piece(PAWN) {}

bool pawn::test_deplacement (int x, int y) {
	cout << "test deplacement piont" << endl;
	if (x < 0 || y < 0 || x > 8 || y > 8)
		return false;
	if (abs(posy-y) == 1) {
		if (posx == x) {
			//test si piece en (x,y+1)
			if (!piece en (x, abs(posy-y)))
				return true;
		} else if (piece en (abs(posx-x), abs(posy-y))) {
			return true;
		}
	}
	return false;
}

