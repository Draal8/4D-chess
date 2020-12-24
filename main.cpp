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
	
	//cout << "\033[1;36mbonjour\033[0m" << endl;
	
	chessboard *c = new chessboard ();
	c->pieces[4][1] = new rook('W', 1, 4);
	c->print_chessboard ();
	
	c->move_piece(1,4,1,6);
	cout << endl;
	c->print_chessboard ();
	
	
	
	c->~chessboard ();
	return 0;
}




















