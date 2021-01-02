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
	
	c->turn(0); 
	c->double_step(0,1);
	c->move_piece(3,0,4,0);
	c->turn(1);
	c->move_piece(0,0,3,0);
	c->print_chessboard2 ();
	c->pieces[1][0] = new pawn('W', 0, 1);
	c->move_piece(0,1,1,0);
	//c->pieces[1][0]->deplacement(c, 1, 0);
	c->print_chessboard2 ();
	//c->move_piece(3,6,3,5);
	//c->move_piece(3,1,3,2);
	
	
	
	cout << endl;
	cout << "print chessboard" << endl;
	c->print_chessboard2 ();
	
	c->~chessboard ();
	return 0;
}




















