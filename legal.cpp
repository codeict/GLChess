#include <bits/stdc++.h>
#include "printerw.cpp"
#include "printerb.cpp"
#include "chessInterface.cpp"
using namespace std;
int hdx[8] = { 1, 2, 2, 1,-1,-2,-2,-1};
int hdy[8] = { 2, 1,-1,-2,-2,-1, 1, 2};
int bdx[4] = {1,1,-1,-1};
int bdy[4] = {1,-1,-1,1};
int rdx[4] = {1,0,-1,0};
int rdy[4] = {0,-1,0,1};
bool legalState(bool lastWhite){
	int a,b;
	bool found = false;
	for (int i =0 ; i<8; i++){
		for (int j = 0; j<8; j++){
			if (cb.board[i][j].curr.pieceDef == 6 && (cb.board[i][j].curr.white == lastWhite))
				a = i,b=j;
		}
	}
	cout<<"Checking coordinates "<<a<<" "<<b<<endl;
	for (int i = 0; i<8; i++){												//check if horse is attacking
		int x = a+hdx[i], y = b+hdy[i];
		if (x<0 || x>7 || y<0 || y>7)
			continue;
		if (cb.board[x][y].curr.pieceDef == 2 && cb.board[x][y].curr.white != lastWhite)
			return false;
	}
	for (int i = 0; i<4; i++){												//checking diagonal attack on king
		cout<<"checking diagonal\n";
		int x = a+bdx[i], y = b+bdy[i];
		while (x>=0 && x<8 && y>=0 && y<8){

			if (cb.board[x][y].curr.pieceDef != 0){

				chessPiece found = cb.board[x][y].curr;

				if (found.white == lastWhite || found.pieceDef == 2 || found.pieceDef == 4){
					// Intensionally Empty
				}

				else if (found.pieceDef == 1){		//Found opposite color Pawn or King diagonally
					if ((x == a+1 || x==a-1) && y==(b+ ((lastWhite)? 1 : -1) )){

						return false;
					}
				}

				else if (found.pieceDef == 7){		//Found opposite color Pawn or King diagonally
					if ((x == a+1 || x==a-1) && (y==b+1 || y==b-1) ){

						return false;
					}
				}

				else if (found.pieceDef == 3){								//Found opposite color Bishop diagonally
					return false;
				}

				else if (found.pieceDef == 5){								//Found opposite color Queen diagonally
					return false;
				}
				break;
			}
			else
				x+=bdx[i], y+=bdy[i];
		}
	}
	for (int i = 0; i<4; i++){												//checking horizontal and vertical attack on king
		int x = a+rdx[i], y = b+rdy[i];
		while (x>=0 && x<8 && y>=0 && y<8){
			if (cb.board[x][y].curr.pieceDef != 0){
				chessPiece found = cb.board[x][y].curr;
				cout<<"Piece at "<<x<<" "<<y<<endl;
				if (found.white == lastWhite){
					// Intensionally Empty
				}
				else if (found.pieceDef == 4 || found.pieceDef == 5 || (found.pieceDef == 7 && abs(x-a)+abs(y-b) == 1))
					return false;
				break;
			}
			else
				x+=rdx[i], y+=rdy[i];
		}
	}
	return true;
}

vector<int> legalMoves(int pos, bool lastWhite){								//Castling and Empassant's yet to be implemented
	int a = pos/8,b = pos%8;
	chessPiece found =  cb.board[a][b].curr;
	vector<int> moves;
	if (found.pieceDef == 0 || found.white == lastWhite)
		return moves;


	if (found.pieceDef == 1){													//piece is a pawn
		int x = a;
		int y = b + ((found.white)? 1 : -1);
		if (x>=0 && x<8 && y>=0 && y<8 && cb.board[x][y].curr.pieceDef == 0){
			found.pieceDef = 0;
			cb.board[x][y].curr.pieceDef = 1;
			cb.board[x][y].curr.white = found.white;
			if (legalState(!lastWhite)){
				moves.push_back(x*8 + y);
			}
			found.pieceDef = 1;
			cb.board[x][y].curr.pieceDef = 0;
		}
		x--;
		if (x>=0 && x<8 && y>=0 && y<8 && cb.board[x][y].curr.pieceDef != 0 && cb.board[x][y].curr.white == lastWhite){
			int delp = cb.board[x][y].curr.pieceDef;
			found.pieceDef = 0;
			cb.board[x][y].curr.pieceDef = 1;
			cb.board[x][y].curr.white = found.white;
			if (legalState(!lastWhite)){
				moves.push_back(x*8 + y);
			}
			found.pieceDef = 1;
			cb.board[x][y].curr.pieceDef = delp;
			cb.board[x][y].curr.white = !found.white;
		}
		x+=2;
		if (x>=0 && x<8 && y>=0 && y<8 && cb.board[x][y].curr.pieceDef != 0 && cb.board[x][y].curr.white == lastWhite){
			int delp = cb.board[x][y].curr.pieceDef;
			found.pieceDef = 0;
			cb.board[x][y].curr.pieceDef = 1;
			cb.board[x][y].curr.white = found.white;
			if (legalState(!lastWhite)){
				moves.push_back(x*8 + y);
			}
			found.pieceDef = 1;
			cb.board[x][y].curr.pieceDef = delp;
			cb.board[x][y].curr.white = !found.white;
		}
		x--;
		if ((found.white && y == 2 )||((!found.white) && y == 5) ){					//Initial Jump
			if (cb.board[x][y].curr.pieceDef == 0){
			y += ((found.white)? 1 : -1);
			if (x>=0 && x<8 && y>=0 && y<8 && cb.board[x][y].curr.pieceDef == 0){
				found.pieceDef = 0;
				cb.board[x][y].curr.pieceDef = 1;
				cb.board[x][y].curr.white = found.white;
				if (legalState(!lastWhite)){
					moves.push_back(x*8 + y);
				}
				found.pieceDef = 1;
				cb.board[x][y].curr.pieceDef = 0;
			}}
		}
	}

	else if (found.pieceDef == 2){													//piece is a horse
		int x,y;
		for (int i = 0; i<8; i++){
			x = a+hdx[i], y = b+hdy[i];
			if (x <0 || x > 7 || y<0 || y>7)
				continue;
			if (cb.board[x][y].curr.pieceDef == 0 || cb.board[x][y].curr.white == lastWhite){
				int delp = cb.board[x][y].curr.pieceDef;
				found.pieceDef = 0;
				cb.board[x][y].curr.pieceDef = 2;
				cb.board[x][y].curr.white = found.white;
				if (legalState(!lastWhite)){
					moves.push_back(x*8 + y);
				}
				found.pieceDef = 2;
				cb.board[x][y].curr.pieceDef = delp;
				cb.board[x][y].curr.white = !found.white;
			}
		}
	}


	else if (found.pieceDef == 3){													//piece is a bishop
		for (int i = 0; i<4; i++){
			int x = a+bdx[i], y = b+bdy[i];
			while (x>=0 && x<8 && y>=0 && y<8){

				if (cb.board[x][y].curr.pieceDef != 0){
					if (cb.board[x][y].curr.white == lastWhite){
					int delp = cb.board[x][y].curr.pieceDef;
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 3;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 3;
					cb.board[x][y].curr.pieceDef = delp;
					cb.board[x][y].curr.white = !found.white;
				}
					break;
				}
				else{
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 3;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 3;
					cb.board[x][y].curr.pieceDef = 0;
					x+=bdx[i], y+=bdy[i];
				}
			}
		}
	}


	else if (found.pieceDef == 4){													//piece is a rook
		for (int i = 0; i<4; i++){
		int x = a+rdx[i], y = b+rdy[i];
		while (x>=0 && x<8 && y>=0 && y<8){

			if (cb.board[x][y].curr.pieceDef != 0){
					if (cb.board[x][y].curr.white == lastWhite){
					int delp = cb.board[x][y].curr.pieceDef;
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 4;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 4;
					cb.board[x][y].curr.pieceDef = delp;
					cb.board[x][y].curr.white = !found.white;
				}
					break;
				}
				else{
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 4;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 4;
					cb.board[x][y].curr.pieceDef = 0;
					x+=rdx[i], y+=rdy[i];
				}
			}
		}
	}
	else if (found.pieceDef == 5){													//piece is a queen
		for (int i = 0; i<4; i++){													//checking diagonal moves
			int x = a+bdx[i], y = b+bdy[i];
			while (x>=0 && x<8 && y>=0 && y<8){

				if (cb.board[x][y].curr.pieceDef != 0){
					if (cb.board[x][y].curr.white == lastWhite){
					int delp = cb.board[x][y].curr.pieceDef;
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 5;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 5;
					cb.board[x][y].curr.pieceDef = delp;
					cb.board[x][y].curr.white = !found.white;
				}
					break;
				}
				else{
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 5;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 5;
					cb.board[x][y].curr.pieceDef = 0;
					x+=bdx[i], y+=bdy[i];
				}
			}
		}
		for (int i = 0; i<4; i++){													//checking horizontal and vertical moves
		int x = a+rdx[i], y = b+rdy[i];
		while (x>=0 && x<8 && y>=0 && y<8){

			if (cb.board[x][y].curr.pieceDef != 0){
					if (cb.board[x][y].curr.white == lastWhite){
					int delp = cb.board[x][y].curr.pieceDef;
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 5;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 5;
					cb.board[x][y].curr.pieceDef = delp;
					cb.board[x][y].curr.white = !found.white;
				}
					break;
				}
				else{
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 5;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 5;
					cb.board[x][y].curr.pieceDef = 0;
					x+=rdx[i], y+=rdy[i];
				}
			}
		}
	}
	else {																			//checking moves of King
		for (int i = 0; i<4; i++){													//checking horizontal and vertical moves
			int x = a+bdx[i], y = b+bdy[i];
			if ((x>=0 && x<8 && y>=0 && y<8)&&(cb.board[x][y].curr.pieceDef == 0 || cb.board[x][y].curr.white == lastWhite)){
				int delp = cb.board[x][y].curr.pieceDef;
				found.pieceDef = 0;
				cb.board[x][y].curr.pieceDef = 6;
				cb.board[x][y].curr.white = found.white;
				if (legalState(!lastWhite)){
					cout<<"Success checking king at "<<x<<" "<<y<<endl;
					moves.push_back(x*8 + y);
				}
				found.pieceDef = 6;
				cb.board[x][y].curr.pieceDef = delp;
				cb.board[x][y].curr.white = !found.white;
			}
			x = a+rdx[i], y = b+rdy[i];
			if ((x>=0 && x<8 && y>=0 && y<8)&&(cb.board[x][y].curr.pieceDef == 0 || cb.board[x][y].curr.white == lastWhite)){
				int delp = cb.board[x][y].curr.pieceDef;
				found.pieceDef = 0;
				cb.board[x][y].curr.pieceDef = 6;
				cb.board[x][y].curr.white = found.white;
				cout<<"1checking king at "<<x<<" "<<y<<endl;
				if (legalState(!lastWhite)){
					cout<<"1Success checking king at "<<x<<" "<<y<<endl;
					moves.push_back(x*8 + y);
				}
				found.pieceDef = 6;
				cb.board[x][y].curr.pieceDef = delp;
				cb.board[x][y].curr.white = !found.white;
			}
		}
	}
	return moves;
}
