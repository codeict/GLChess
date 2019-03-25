#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

string CHESS[7] = {"empty","pawn","horse","bishop","rook","queen","king"};
int hdx = { 1, 2, 2, 1,-1,-2,-2,-1};
int hdy = { 2, 1,-1,-2,-2,-1, 1, 2};

bool isSelected = false;

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
}selectedCQ;

void selected(chessSquare scq){
	selectedCQ = scq;
	isSelected = true;
}

class chessboard{
chessSquare board[8][8];
public:
	void initiate(){
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
			board[i][1].curr.pieceDef = 1;
			board[i][1].curr.white = true;
			board[i][0].curr.white = true;
			board[i][0].curr.pieceDef = order[i];
			board[i][6].curr.pieceDef = 1;
			board[i][6].curr.white = false;
			board[i][7].curr.white = false;
			board[i][7].curr.pieceDef = order[i];
		}

	}

	void resetLegal(){
		for(int i = 0 ; i < 8 ; i++){
			for(int j = 0 ; j < 8 ; j++){
				board[i][j].legal = false;
			}
		}
	}

	void move(chessSquare cs){
		if(cs.legal || 1){
			resetLegal();
			cs.curr = selectedCQ.curr;
			selectedCQ.clearSquare();
			isSelected = false;
		}
	}

 void click(int button, int state, int x, int y){
			if(state == GLUT_DOWN){
			int a = x;
			int b = 1000 - y;
			a = a/100;
			b = b/100;
			if(a>0&&a<9&&b>0&&b<9){
				if(!isSelected){
					char c = 64 + b;
					cout << "squareSelected "<<c<<a<<endl;
					cout << "\tsquare color = "<<(board[--a][--b].white?"white":"black") << endl;
					cout << "\tselected piece = "<<CHESS[board[a][b].curr.pieceDef]<<endl;
					cout << "\tpiece color = "<<(board[a][b].curr.white?"white":"black") << endl;

					selected(board[a][b]);
				}else{
					move(board[a][b]);
				}

			}

		}
	}

}cb;

bool legalState(bool lastWhite){
	int a,b;
	for (int i =0 ; i<8; i++){
		for (int j = 0; j<8; j++){
			if (cb.board[i][j].chessPiece.pieceDef == 6 && cb.board[i][j].chessPiece.white == lastWhite)
				a = i,b=j;
		}
	}

	for (int i = 0; i<8; i++){												//check if horse is attacking
		int x = a+hdx[i], y = b+hdy[i];
		
	}
}

vector<int> legalMoves(int pos){
	int a = pos/8,b = pos%8;
	int piece = cb.board[a][b].chessPiece.pieceDef;
	bool pieceWhite = cb.board[a][b].chessPiece.white;
	if (piece == 1){														//piece is a pawn

		if 
	}
	else if (piece == 2){													//piece is a horse

	}
	else if (piece == 3){													//piece is a bishop

	}
	else if (piece == 4){													//piece is a rook

	}
	else if (piece == 5){													//piece is a queen

	}
	else {																	//piece is a king

	}

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
