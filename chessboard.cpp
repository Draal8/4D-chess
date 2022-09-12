#include "chessboard.h"

using namespace std;

char empty_chessboard[] = "\n8 | | | | | | | | |\n7 | | | | | | | | |\n6 | | | | | | | | |\n5 | | | | | | | | |\n4 | | | | | | | | |\n3 | | | | | | | | |\n2 | | | | | | | | |\n1 | | | | | | | | |\n   A B C D E F G H \n";

//https://techstop.github.io/bash-script-colors/

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
	players[0] = new player('W', pieces[7][4]);
	players[1] = new player('B', pieces[0][4]);
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
	player *player = players[pturn];
	if (pieces[inity][initx] == NULL) {
		cout << "Aucune pièce a l'endroit indiqué\n";
		return false;
	}
	if (pieces[inity][initx]->get_color() != player->get_color()) {
		cout << "Le joueur ne peut pas deplacer une piece qui ne lui appartient pas\n";
		return false;
	}
	if (pieces[inity][initx]->deplacement(this, x, y)) {
		
		//On empeche de faire des rock dans le futur si on bouge certaines pieces
		if (pieces[inity][initx]->get_value() == KING) {
			player->set_castling('l', false);
			player->set_castling('b', false);
		} else if (pieces[inity][initx]->get_value() == ROOK) {
			if (initx == 0 && (inity == 0 || inity == 7)) {
				player->set_castling('b', false);
			} else if (initx == 7 && (inity == 0 || inity == 7)) {
				player->set_castling('l', false);
			}
		}
		
		if (pieces[y][x] != NULL) {
			cout << "kill : " << pieces[y][x]->get_value() << endl;
			kill(pieces[y][x]);
		}
		pieces[y][x] = pieces[inity][initx];
		pieces[inity][initx] = NULL;
	} else {
		return false;
	}
	
	if (pieces[y][x]->test_promote())
		promotion(pieces[y][x], x, y);
	
	turn();
	return true;
}

void chessboard::kill (piece *p/*, int mode*/) {
	/*if (mode == 0 && p->get_value () == EN_PASSANT) {
		enPassant *ep;
		ep = (enPassant *) p;*/
		
		/*we remove the original piece from the chessboard
		we kill the original piece of the en passant token
		we change the status of the en passant token to inactive*/
		
		/*pieces[ep->origine->get_y()][ep->origine->get_x()] = NULL;
		kill (ep->origine);
		players[(pturn+1)%2]->set_S_pass(false, -1, -1);
	} else if (p->get_value () == EN_PASSANT) {
		cout << "a piece killed : " << p->get_value() << endl;
		pieces[p->get_y()][p->get_x()] = NULL;
		players[(pturn+1)%2]->set_S_pass(false, -1, -1);
	} else {
		cout << "piece killed : " << p->get_value() << endl;
		pieces[p->get_y()][p->get_x()] = NULL;
	}*/
	
	cout << "piece killed : " << p->get_value() << endl;
	pieces[p->get_y()][p->get_x()] = NULL;
	delete p;
}

/*
void chessboard::double_step (int x, int y) {
	char color = pieces[y][x]->get_color();*/
	
	/*if the pawn is on the first line of each colour then you can double step
	there is no need to check the colour because you can't go backward
	and you can't double step forward from line 7 as whites and the contrary*/
	/*
	if (y == 1) {
		pieces[2][x] = new enPassant(color, x, 2, pieces[1][x]);
		//players[1]->set_S_pass(true, x, 2);
	} else if (y == 6) {
		pieces[5][x] = new enPassant(color, x, 5, pieces[6][x]);
		//players[0]->set_S_pass(true, x, 5);
	}
}*/

bool chessboard::castling (char mode) {
	int y = (pturn+1)%2*7;
	//whites = 0 and blacks = 1 (so 1*7 = 7)

	if (mode == 'l') {
		if (!players[pturn]->get_castling('l')) {
			cout << "You already moved a piece involved in this castling" << endl;
			return false;
		}
		if (pieces[y][5] != NULL || pieces[y][6] != NULL) {
			cout << "There are still pieces in the way of your castling" << endl;
			return false;
		}
		
		pieces[y][7]->fdeplacement(5,y);
		pieces[y][5] = pieces[y][7];
		pieces[y][7] = NULL;
		
		pieces[y][4]->fdeplacement(6,y);
		pieces[y][6] = pieces[y][4];
		pieces[y][4] = NULL;
		
	} else if (mode == 'b') {
		if (!players[pturn]->get_castling('b')) {
			cout << "You already moved a piece involved in this castling" << endl;
			return false;
		}
		if (pieces[y][3] != NULL || pieces[y][2] != NULL || pieces[y][1] != NULL) {
			cout << "There are still pieces in the way of your castling" << endl;
			return false;
		}
		
		pieces[y][0]->fdeplacement(3,y);
		pieces[y][3] = pieces[y][0];
		pieces[y][0] = NULL;
		
		pieces[y][4]->fdeplacement(2,y);
		pieces[y][2] = pieces[y][4];
		pieces[y][4] = NULL;
		
	} else {
		cout << "incorrect castling mode" << endl;
		return false;
	}
	
	players[pturn]->set_castling('l', false);
	players[pturn]->set_castling('b', false);
	turn();
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
	fflush(stdin);
	
}


/*if we want something that is maybe faster by a little bit we can maintain a chessboard
with booleans if attacked by whites and bollean for blacks. Then is_checked is just checking booleans.
which means instead of checking every ennemy piece/turn. We update discovered cases and remove blindspots
so that we don't iterate (hopefully) on every pieces.
Maybe the idea isn't that smart though it seems we still have to iterate on multiple pieces to find blindspots
Better idea maybe just maintain this only for cases next to the king and on the last line for castling*/

//echec
piece *chessboard::is_attacked(int x, int y, char color) {
	piece *danger = malloc(16 * sizeof(piece *));	//hopefully you won't get attacked by more than all of the opponent's pieces :)
	int nb_dangers = 0;
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; i < 8; i++) {
			if (pieces[i][j] != NULL && pieces[i][j]->couleur != color) {	//if piece exist and is of the other color
				if (pieces[i][j]->test_deplacement(this,x,y)) {		//test if it can reach the specific case
					danger[nb_dangers] = pieces[i][j];
					nb_dangers++;
					//flag = 2;
				}
			}
		}
	}
	if (nb_dangers == 0) {
		free(danger);
		return NULL;
	}
	return danger;
}

//flag = {0: nothing, 1: checkmate, 2: check}
int chessboard::is_checked() {	//checking checks and checkmates
	piece *k = player[pturn]->king;
	int x = k->posx;
	int y = k->posy
	int nb_dangers = 0;
	flag = 0;
	
	piece *danger = chessboard::is_attacked(x, y, k->couleur);	//is the king in danger ?
	if (danger == NULL) return 0;	//no check was found
	else 
		for (int i = 0; i < 16 && danger[i] != NULL; i++) nb_dangers++;	//count the number of times it is
	
	//can the king move ?
	if (flagking_can_move() == 1) return 1;	//check was found but there is at least one legal move therefore no mate
	if (nb_dangers > 1)	return 2;	//you can't escape a mate from multiple sources without moving
	
	//can we kill the piece attacking then ?
	if (is_attacked(danger[0]->x, danger[0]->y, danger[0]->couleur) != NULL) return 1;
	
	//can we block the attack then ?
	if (danger[0]->get_value() == 'C' || ) return 2;	//cannot block a knight
	if (danger[0]->can_be_blocked(this, k)) return 1;
	else return 2;
	
	
	/*//sending the dangerous pieces to the chessboard
	piece **msg = malloc(sizeof(*piece) * nb_dangers);
	for (int i = 0; i < nb_dangers; i++) {
		msg[i] = danger[i];
	}
	this->piece_that_checks = msg;
	 
	return flag*/
}

int chessboard::king_can_move() {
	int flag = 0;
	piece *k = player[pturn]->king;
	for (int i = 0; i < 3 && flag == 0; i++) {
		for (int j = 0; i < 3 && flag == 0; i++) {
			int x = k->posx-1+i;
			int y = k->posy-1+j;
			if (i != 1 && j != 1 && k->test_deplacement(this, x, y)) { //if j == 1 and i == 1 then it'd check again
				piece *temp = this->is_attacked(x, y, k->couleur);
				if (piece == NULL) flag = 1;
				else free(piece);	//no need to free and malloc each time we need to use this->piece_that_checks that needs one allocation and then we set its cases to NULL when needed
			}
		}
	}
	
	return flag;
}

//Other

void chessboard::turn() {
	pturn = (pturn + 1) % 2;
	int temp = is_checked();
	if (temp == 1) {
		cout << "This is the end\n";
		this->endgame();
	} else if (temp == 2) {
		this->is_checked = true;
	}
	//we verify if the en passant token is active
	
	
	//parser()
}

void endgame () {
	
	
	
	
}

