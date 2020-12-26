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
	c->print_chessboard2 ();
	
	c->pieces[4][4] = new pawn('B', 4, 4);
	c->print_chessboard2 ();
	c->double_step(3,6);
	c->double_step(3,1);
	piece *p = c->pieces[5][3];
	cout << (p==NULL) << "vs true " << true;
	c->move_piece(4,4,3,5);
	//c->move_piece(3,6,3,5);
	//c->move_piece(3,1,3,2);
	
	
	
	cout << endl;
	c->print_chessboard2 ();
	
	cout << (p==NULL) << "vs true " << true;
	
	c->~chessboard ();
	return 0;
}




















