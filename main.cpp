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
	//c->print_chessboard2 ();
	
	c->pieces[4][4] = new pawn('B', 4, 4);
	c->turn(0); 
	c->double_step(3,6);
	c->print_chessboard2 ();
	c->turn(1);
	c->double_step(3,1);
	c->print_chessboard2 ();
	c->turn(0);
	c->print_chessboard2 ();
	c->move_piece(4,4,4,5);
	c->turn(1);
	c->print_chessboard2 ();
	//c->move_piece(3,6,3,5);
	//c->move_piece(3,1,3,2);
	
	
	
	cout << endl;
	cout << "print chessboard" << endl;
	c->print_chessboard2 ();
	
	c->~chessboard ();
	return 0;
}




















