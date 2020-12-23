#include "chessboard.h"

using namespace std;

char empty_chessboard[] = "   1 2 3 4 5 6 7 8 \nA | | | | | | | | |\nB | | | | | | | | |\nC | | | | | | | | |\nD | | | | | | | | |\nE | | | | | | | | |\nF | | | | | | | | |\nG | | | | | | | | |\nH | | | | | | | | |\n";

chessboard::chessboard () {
	init_chessboard ();
}

chessboard::~chessboard () {
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (pieces[i][j] != NULL) {
				pieces[i][j]->~piece();
				//delete(pieces[i][j]);
			}
		}
	}
}

void chessboard::init_chessboard () {
	pieces[0][4] = new king('B', 4, 0);
	pieces[7][4] = new king('W', 4, 7);
	pieces[0][3] = new queen('B', 3, 0);
	pieces[7][3] = new queen('W', 3, 7);
	pieces[0][2] = new bishop('B', 2, 0);
	pieces[0][5] = new bishop('B', 5, 0);
	pieces[7][2] = new bishop('W', 2, 7);
	pieces[7][5] = new bishop('W', 5, 7);
	pieces[0][1] = new knight('B', 1, 0);
	pieces[0][6] = new knight('B', 6, 0);
	pieces[7][1] = new knight('W', 1, 7);
	pieces[7][6] = new knight('W', 6, 7);
	pieces[0][0] = new rook('B', 0, 0);
	pieces[0][7] = new rook('B', 7, 0);
	pieces[7][0] = new rook('W', 0, 7);
	pieces[7][7] = new rook('W', 7, 7);
	
	int i;
	for (i = 0; i < 8; i++)
		pieces[1][i] = new pawn('B', i, 1);
	for (i = 0; i < 8; i++)
		pieces[6][i] = new pawn('W', i, 6);
	
	cout << "   1 2 3 4 5 6 7 8 \nA |R|C|B|Q|K|B|C|R|\nB |P|P|P|P|P|P|P|P|\nC | | | | | | | | |\nD | | | | | | | | |\nE | | | | | | | | |\nF | | | | | | | | |\nG |P|P|P|P|P|P|P|P|\nH |R|C|B|Q|K|B|C|R|\n\n";
}

void chessboard::print_chessboard () {
	int i, j;
	char str[255];
	strcpy(str, empty_chessboard);
	
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (pieces[i][j] != NULL) {
				str[coord_to_index(j,i)] = pieces[i][j]->get_value();
			}
		}
	}
	
	cout << str << endl;
}

int chessboard::coord_to_index (int x, int y) {
	return 3 + 20*(y+1) + 2*x;
}
// 3 de base car toutes les colonnes commencent par 'A||'
// 19 de taille de ligne
// et 2 car un caractere de piece et un '|'

bool chessboard::piece_in (int x, int y) {
	return (pieces[x][y] != NULL);
}

void chessboard::move_piece (int initx, int inity, int x, int y) {
	if (pieces[initx][inity]->deplacement(this, x, y)) {
		pieces[x][y] = pieces[initx][inity];
		pieces[initx][inity] = NULL;
	}
	cout << "deplacement fini\n";
}


