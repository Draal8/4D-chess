#include <iostream>
#include "piece.h"

using namespace std;

int main() {
	piece *p = new king();
	char c = p->get_value();
	cout << "c : " << c << endl;
	
	//p->~piece();
	delete(p);
	c = p->get_value();
	cout << "c : " << c << endl;
}




















