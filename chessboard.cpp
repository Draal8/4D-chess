#include "chessboard.h"

using namespace std;

//https://techstop.github.io/bash-script-colors/

char empty_chessboard[] = "   1 2 3 4 5 6 7 8 \nA | | | | | | | | |\nB | | | | | | | | |\nC | | | | | | | | |\nD | | | | | | | | |\nE | | | | | | | | |\nF | | | | | | | | |\nG | | | | | | | | |\nH | | | | | | | | |\n";

char black[] = "\e[0;30m";
char red[] = "\e[0;91m";
char green[] = "\e[0;32m";
char yellow[] = "\e[0;33m";
char blue[] = "\e[0;34m";
char purple[] = "\e[0;35m";
char cyan[] = "\e[0;36m";
char white[] = "\e[0;37m";
char noColor[] = "\033[0m";
int colLen = 7;
int NcLen = 4;

//Constructor/Destructor

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
	
	print_chessboard2 ();
}

//Print chessboard

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

void chessboard::print_chessboard2 () {
	int i, j;
	char str[511], tmp[5], color[16];
	char c;
	shift_color = 0;
	shift_nc = 0;
	snprintf(color, 16, "%s %s|", yellow, noColor);
	strcpy(str, "   1 2 3 4 5 6 7 8 \n");
	
	for (i = 0; i < 8; i++) {
		strcpy(tmp, "\n  |");
		c = 'A' + i;
		tmp[1] = c;
		strcat(&str[strlen(str)], tmp);
		
		for (j = 0; j < 8; j++) {
			if (pieces[i][j] != NULL) {
				if (pieces[i][j]->get_color() == 'B') {
					strcat(&str[strlen(str)], color);
					str[strlen(str)-colLen+1] = pieces[i][j]->get_value();
				} else {
					strcat(&str[strlen(str)], " |");
					str[strlen(str)-2] = pieces[i][j]->get_value();
				}
			} else {
				strcat(&str[strlen(str)], " |");
			}
		}
	}
	str[strlen(str)+1] = '\0';
	str[strlen(str)] = '\n';
	cout << str << endl;	
}

int chessboard::coord_to_index (int x, int y) {
	return 3 + 20*(y+1) + 2*x;
}
// 3 de base car toutes les colonnes commencent par 'A||'
// 19 de taille de ligne
// et 2 car un caractere de piece et un '|'

//Piece manipulation

bool chessboard::piece_in (int x, int y) {
	return (pieces[y][x] != NULL);
}

piece * chessboard::get_piece (int x, int y) {
	return pieces[y][x];
}

void chessboard::move_piece (int initx, int inity, int x, int y) {
	if (pieces[inity][initx]->deplacement(this, x, y)) {
		pieces[y][x] = pieces[inity][initx];
		pieces[inity][initx] = NULL;
	}
	cout << "deplacement fini\n";
}


