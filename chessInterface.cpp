#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

string CHESS[7] = {"empty","pawn","horse","bishop","rook","queen","king"};
int hdx[8] = { 1, 2, 2, 1,-1,-2,-2,-1};
int hdy[8] = { 2, 1,-1,-2,-2,-1, 1, 2};
int bdx[4] = {1,1,-1,-1};
int bdy[4] = {1,-1,-1,1};
int rdx[4] = {1,0,-1,0};
int rdy[4] = {0,-1,0,1};
vector<int> legalMoves(int, bool);

class chessPiece{
public:
	int pieceDef;
	bool white;
	chessPiece (int pd,bool w){
		pieceDef = pd;
		white = w;
	}

	chessPiece(){
		pieceDef = 0;
		white = true;
	}
	void draw(int x, int y ){
		//cout << "piece draw called"<<endl;
		glColor3f(1.0,1.0,0.0);
		glRecti(x+15,y+15,x+85,y+15);
		glFlush();
	}

	void setEmpty(){
		pieceDef= 0;
	}

	void operator =(chessPiece c){
		this->pieceDef = c.pieceDef;
		this->white = c.white;
	}
};

class chessSquare{
public:
	int x , y;
	chessPiece curr;
	bool white;
	bool legal;

	chessSquare(){
		x=0;y=0;
		white = true;
		legal = false;
	}

	void clearSquare(){
		curr.setEmpty();
	}

	void setSquare(chessPiece cp){
		curr.white = cp.white;
		curr.pieceDef = cp.pieceDef;
	}
};

class chessboard{
public:
chessSquare board[8][8];
bool isSelected ;
int m,n;
	void initiate(){
		isSelected = false;
		bool white = true;
		int x = 100,y = 100;
		for(int i = 0 ; i <8;i++){
			for(int j = 0 ; j <8;j++){
					board[i][j].x = x;
					board[i][j].y = y;
					board[i][j].white = !white;
					glRecti(x,y,x+100,y+100);
					x+=100;
					if(white){
						glColor3f(0.941,0.941,0.874);
					}else{
						glColor3f(0.247,0.345,0.4);
					}
					white = !white;
			}
			if(white){
				glColor3f(0.941,0.941,0.874);
			}else{
				glColor3f(0.247,0.345,0.4);
			}
			white = !white;
			x = 100;
			y+=100;
		}
		glFlush();
	}
	void setpieces(){
		int order[8] = {4,2,3,5,6,3,2,4};
		for(int i = 0 ; i < 8 ; i++){
			//board[i][1].curr.pieceDef = 1;
			board[i][1].curr.white = true;
			board[i][0].curr.white = true;
			board[i][0].curr.pieceDef = order[i];
			board[i][6].curr.pieceDef = 1;
			board[i][6].curr.white = false;
			board[i][7].curr.white = false;
			board[i][7].curr.pieceDef = order[i];
		}

	}

	void getlegal(int a , int b){
		m =a ; n = b ;
	}

	void resetLegal(){
		for(int i = 0 ; i < 8 ; i++){
			for(int j = 0 ; j < 8 ; j++){
				board[i][j].legal = false;
			}
		}
	}

	void move(int a , int b){
		if(m==a && n==b){
			isSelected = false;
			return;
		}
		if(board[a][b].legal || true){
			resetLegal();
			board[a][b].curr = board[m][n].curr;
			board[m][n].clearSquare();
			isSelected = false;
		}
	}

 void click(int button, int state, int x, int y){
			if(state == GLUT_DOWN){
			int a = x;
			int b = 1000 - y;
			a = a/100;
			b = b/100;
			a--,b--;
			if(a>=0&&a<8&&b>=0&&b<8){
				if(!isSelected){
					char c = 'A' + b;
					cout << "squareSelected "<<c<<a<<endl;
					cout << "\tsquare color = "<<(board[a][b].white?"white":"black") << endl;
					cout << "\tselected piece = "<<CHESS[board[a][b].curr.pieceDef]<<endl;
					cout << "\tpiece color = "<<(board[a][b].curr.white?"white":"black") << endl;
					vector<int> moves = legalMoves(a*8+b, false);
					for (auto x : moves){
						cout<<x/8<<","<<x%8<<endl;
					}
				}else{
					move(a, b);
				}
			}
		}
	}


}cb;

bool legalState(bool lastWhite){
	int a,b;
	for (int i =0 ; i<8; i++){
		for (int j = 0; j<8; j++){
			if (cb.board[i][j].curr.pieceDef == 6 && cb.board[i][j].curr.white == lastWhite)
				a = i,b=j;
		}
	}

	for (int i = 0; i<8; i++){												//check if horse is attacking
		int x = a+hdx[i], y = b+hdy[i];
		if (x<0 || x>7 || y<0 || y>7)
			continue;
		if (cb.board[x][y].curr.pieceDef == 2 && cb.board[x][y].curr.white != lastWhite)
			return false;
	}
	for (int i = 0; i<4; i++){												//checking diagonal attack on king
		int x = a+bdx[i], y = b+bdy[i];
		while (x>=0 && x<8 && y>=0 && y<8){

			if (cb.board[x][y].curr.pieceDef != 0){

				chessPiece found = cb.board[x][y].curr;
				
				if (found.white == lastWhite || found.pieceDef == 2 || found.pieceDef == 4){
					// Intensionally Empty
				}

				else if (found.pieceDef == 1 || found.pieceDef == 7){		//Found opposite color Pawn or King diagonally
					if ((x == a+1 || x==a-1) && y==(b+ ((lastWhite)? 1 : -1) )){
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
}

vector<int> legalMoves(int pos, bool lastWhite){
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
			cb.board[x][y].curr.pieceDef == 1;
			cb.board[x][y].curr.white = found.white;
			if (legalState(!lastWhite)){
				moves.push_back(x*8 + y);
			}
			found.pieceDef = 1;
			cb.board[x][y].curr.pieceDef == 0;
		}
		x--;
		if (x>=0 && x<8 && y>=0 && y<8 && cb.board[x][y].curr.pieceDef != 0 && cb.board[x][y].curr.white == lastWhite){
			int delp = cb.board[x][y].curr.pieceDef;
			found.pieceDef = 0;
			cb.board[x][y].curr.pieceDef == 1;
			cb.board[x][y].curr.white = found.white;
			if (legalState(!lastWhite)){
				moves.push_back(x*8 + y);
			}
			found.pieceDef = 1;
			cb.board[x][y].curr.pieceDef == delp;
			cb.board[x][y].curr.white = !found.white;
		}
		x+=2;
		if (x>=0 && x<8 && y>=0 && y<8 && cb.board[x][y].curr.pieceDef != 0 && cb.board[x][y].curr.white == lastWhite){
			int delp = cb.board[x][y].curr.pieceDef;
			found.pieceDef = 0;
			cb.board[x][y].curr.pieceDef == 1;
			cb.board[x][y].curr.white = found.white;
			if (legalState(!lastWhite)){
				moves.push_back(x*8 + y);
			}
			found.pieceDef = 1;
			cb.board[x][y].curr.pieceDef == delp;
			cb.board[x][y].curr.white = !found.white;
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
				cb.board[x][y].curr.pieceDef == 2;
				cb.board[x][y].curr.white = found.white;
				if (legalState(!lastWhite)){
					moves.push_back(x*8 + y);
				}
				found.pieceDef = 2;
				cb.board[x][y].curr.pieceDef == delp;
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
					cb.board[x][y].curr.pieceDef == 3;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 3;
					cb.board[x][y].curr.pieceDef == delp;
					cb.board[x][y].curr.white = !found.white;
				}
					break;				
				}
				else{
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef == 3;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 3;
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
					cb.board[x][y].curr.pieceDef == 4;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 4;
					cb.board[x][y].curr.pieceDef == delp;
					cb.board[x][y].curr.white = !found.white;
				}
					break;				
				}
				else{
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef == 4;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 4;
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
					cb.board[x][y].curr.pieceDef == 5;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 5;
					cb.board[x][y].curr.pieceDef == delp;
					cb.board[x][y].curr.white = !found.white;
				}
					break;				
				}
				else{
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef == 5;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 5;
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
					cb.board[x][y].curr.pieceDef == 5;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 5;
					cb.board[x][y].curr.pieceDef == delp;
					cb.board[x][y].curr.white = !found.white;
				}
					break;				
				}
				else{
					found.pieceDef = 0;
					cb.board[x][y].curr.pieceDef == 5;
					cb.board[x][y].curr.white = found.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					found.pieceDef = 5;
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
				cb.board[x][y].curr.pieceDef == 6;
				cb.board[x][y].curr.white = found.white;
				if (legalState(!lastWhite)){
					moves.push_back(x*8 + y);
				}
				found.pieceDef = 6;
				cb.board[x][y].curr.pieceDef == delp;
				cb.board[x][y].curr.white = !found.white;
			}
			x = a+rdx[i], y = b+rdy[i];
			if ((x>=0 && x<8 && y>=0 && y<8)&&(cb.board[x][y].curr.pieceDef == 0 || cb.board[x][y].curr.white == lastWhite)){
				int delp = cb.board[x][y].curr.pieceDef;
				found.pieceDef = 0;
				cb.board[x][y].curr.pieceDef == 6;
				cb.board[x][y].curr.white = found.white;
				if (legalState(!lastWhite)){
					moves.push_back(x*8 + y);
				}
				found.pieceDef = 6;
				cb.board[x][y].curr.pieceDef == delp;
				cb.board[x][y].curr.white = !found.white;
			}
		}
	}
	return moves;
}

void click(int button, int state, int x, int y){
		 cb.click(button,state,x,y);
}

void init2d()//how to display
{
	glClearColor (1.0,1.0,1.0,0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0,1000.0, 0.0, 1000.0);//same like window size(xl,xh,yl,yh)
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glRecti(90,90,910,910);
	glColor3f(0.247, 0.345, 0.4);
	glFlush();
	cb.initiate();
	cb.setpieces();
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize (1000, 1000);
	glutInitWindowPosition (00, 00);
	glutCreateWindow ("CHESS");
	init2d();
	glutDisplayFunc(display);
	glutMouseFunc(click);
	glutMainLoop();
	return 0;
}
