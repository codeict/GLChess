#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

string CHESS[7] = {"empty","pawn","horse","bishop","rook","queen","king"};

bool select = false;
void selected(chessSquare scq){

}

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
};

class chessSquare{
public:
	int x , y;
	chessPiece curr;
	bool white;
	chessSquare(){
		x=0;y=0;
		white = true;
	}

	void clearSquare(){

	}

	void setSquare(chessPiece cp){
		
	}
};

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
 void click(int button, int state, int x, int y){
			if(state == GLUT_DOWN && !select){
			int a = x;
			int b = 1000 - y;
			a = a/100;
			b = b/100;
			if(a>0&&a<9&&b>0&&b<9){
				char c = 64 + b;
				cout << "squareSelected "<<c<<a<<endl;
				cout << "\tsquare color = "<<(board[--a][--b].white?"white":"black") << endl;
				cout << "\tselected piece = "<<CHESS[board[a][b].curr.pieceDef]<<endl;
				cout << "\tpiece color = "<<(board[a][b].curr.white?"white":"black") << endl;
				selected(board[i][j]);
			}

		}
	}

}cb;

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
