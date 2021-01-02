#include "chessboard.h"

using namespace std;

//https://techstop.github.io/bash-script-colors/

char empty_chessboard[] = "\nH | | | | | | | | |\nG | | | | | | | | |\nF | | | | | | | | |\nE | | | | | | | | |\nD | | | | | | | | |\nC | | | | | | | | |\nB | | | | | | | | |\nA | | | | | | | | |\n   1 2 3 4 5 6 7 8 \n";

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
	players[0] = new player('W');
	players[1] = new player('B');
}

chessboard::~chessboard () {
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (pieces[i][j] != NULL) {
				//pieces[i][j]->~piece();
				delete(pieces[i][j]);
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
	str[0] = '\0';
	
	for (i = 0; i < 8; i++) {
		strcpy(tmp, "\n  |");
		c = '8' - i;
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
	strcat(str, "   A B C D E F G H\n");
	cout << str << endl;	
}

int chessboard::coord_to_index (int x, int y) {
	return 3 + 20*(y+1) + 2*x;
}
// 3 de base car toutes les colonnes commencent par 'A |'
// 19 de taille de ligne
// et 2 car un caractere de piece et un '|'

//Piece manipulation

bool chessboard::piece_in (int x, int y) {
	return (pieces[y][x] != NULL);
}

piece * chessboard::get_piece (int x, int y) {
	return pieces[y][x];
}

bool chessboard::move_piece (int initx, int inity, int x, int y) {
	if (pieces[inity][initx]->deplacement(this, x, y)) {
		if (pieces[y][x] != NULL)
			kill(pieces[y][x]);
		pieces[y][x] = pieces[inity][initx];
		pieces[inity][initx] = NULL;
	}
	cout << "deplacement fini\n";
	return true;
}

void chessboard::kill (piece *p, int mode) {
	if (mode == 0 && p->get_value () == EN_PASSANT) {
		enPassant *ep;
		ep = (enPassant *) p;
		pieces[ep->origine->get_y()][ep->origine->get_x()] = NULL;
		delete ep->origine;
	} else if (mode == 1) {
		pieces[p->get_y()][p->get_x()] = NULL;
	}
	
	delete p;
}

bool chessboard::test_moves (int x, int y) {
	piece *p = pieces[y][x];
	if (p == NULL) {
		cout << "La case sélectionné ne contient pas de pièce\n";
		return true;
	}
	//test de couleur
	
	return false;
}

bool chessboard::double_step (int x, int y) {
	if (test_moves(x,y)) return false;
	if (pieces[y][x]->get_value() != PAWN) {
		cout << "La pièce n'est pas un pion\n";
		return false;
	}
	
	char color = pieces[y][x]->get_color();
	if (y == 1) {
		if (pieces[2][x] == NULL && pieces[3][x] == NULL) {
			pieces[y][x]->fdeplacement (x, 3);
			pieces[3][x] = pieces[y][x];
			pieces[y][x] = NULL;
			pieces[2][x] = new enPassant(color, x, 2, pieces[3][x]);
			players[1]->set_S_pass(true, x, 2);
		}
	} else if (y == 6) {
		if (pieces[5][x] == NULL && pieces[4][x] == NULL) {
			pieces[y][x]->fdeplacement (x, 4);
			pieces[4][x] = pieces[y][x];
			pieces[y][x] = NULL;
			pieces[5][x] = new enPassant(color, x, 5, pieces[4][x]);
			players[0]->set_S_pass(true, x, 5);
		}
	}
	return true;
}

void chessboard::promotion (piece *pawn, int x, int y) {
	int posx, posy;
	char couleur, c;
	posx = x;
	posy = y;
	couleur = pawn->get_color();
	
	kill(pawn);
	
	c = getchar();
	switch (c) {
	case 'K':
		pieces[posy][posx] = new king(couleur, posx, posy);
		break;
	case 'Q':
		pieces[posy][posx] = new queen(couleur, posx, posy);
		break;
	case 'B':
		pieces[posy][posx] = new bishop(couleur, posx, posy);
		break;
	case 'C':
		pieces[posy][posx] = new knight(couleur, posx, posy);
		break;
	case 'R':
		pieces[posy][posx] = new rook(couleur, posx, posy);
		break;
	default:
		//catch error
		break;
	}
}

//Other

void chessboard::turn(int i) {
	static int player;
	player = i;
	
	S_passant s = players[player]->get_S_pass();
	if (s.actif == true) {
		kill(pieces[s.y][s.x]);
		players[player]->set_S_pass(false, -1, -1);
	}
	
	//parser()
	
	
}


