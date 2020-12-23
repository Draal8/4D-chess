#include <iostream>
#include "piece.h"
#include "chessboard.h"

using namespace std;

int main() {
	/*piece *p = new king();
	char c = p->get_value();
	cout << "c : " << c << endl;
	
	p->~piece();
	delete(p);
	c = p->get_value();
	cout << "c : " << c << endl;*/
	
	chessboard *c = new chessboard ();
	c->print_chessboard ();
	c->move_piece(0,6,0,5);
	
	c->~chessboard ();
	return 0;
}




















