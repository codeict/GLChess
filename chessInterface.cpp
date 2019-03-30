#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
static int menu_id ;
static int value;
static int window;
int screen_render = 0;
string CHESS[7] = {"empty","pawn","horse","bishop","rook","queen","king"};
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
	bool white, legal;

	chessSquare(){
		x=0;y=0;
		white = true;
		legal = false;
	}

	void drawPiece(){
		if(curr.pieceDef == 0){
			if(white){
				glColor3f(0.941,0.941,0.874);
			}else{
				glColor3f(0.247,0.345,0.4);
			}
			glRecti(x+10,y+10,x+90,y+90);
			return;
		}
		if(curr.white){
			switch (curr.pieceDef) {
				case 1:
						drawwP(x+10,y+10);
						break;
				case 2:
						drawwN(x+10,y+10);
						break;
				case 3:
						drawwB(x+10,y+10);
						break;
				case 4:
						drawwR(x+10,y+10);
						break;
				case 5:
						drawwQ(x+10,y+10);
						break;
				case 6:
						drawwK(x+10,y+10);
						break;
					}
		}else{
			switch (curr.pieceDef) {
				case 1:
						drawbP(x+10,y+10);
						break;
				case 2:
						drawbN(x+10,y+10);
						break;
				case 3:
						drawbB(x+10,y+10);
						break;
				case 4:
						drawbR(x+10,y+10);
						break;
				case 5:
						drawbQ(x+10,y+10);
						break;
				case 6:
						drawbK(x+10,y+10);
						break;
				}
		}
	}
	void setSquare(chessPiece cp){
		curr.white = cp.white;
		curr.pieceDef = cp.pieceDef;
	}

	void setAslegal(){
		glColor3f(0.7421,0.9196,0.62109);
		glRecti(x,y,x+100,y+100);
		drawPiece();
		legal = true;
		glFlush();
	}

	void setNormal(){
		legal = false;
		setclear();
		drawPiece();
		glFlush();
	}

	void setclear(){
		if(white){
			glColor3f(0.941,0.941,0.874);
		}else{
			glColor3f(0.247,0.345,0.4);
		}
		glRecti(x,y,x+100,y+100);
		glFlush();
	}
};

class chessboard{
public:
chessSquare board[8][8];
vector<pair<int,int> > move_stack;
bool lastWhite;
int lastx,lasty;
	void initiate(){
		lastWhite = false;
		bool white = true;
		int x = 100,y = 100;
		for(int i = 0 ; i <8;i++){
			for(int j = 0 ; j <8;j++){
					board[i][j].x = y;
					board[i][j].y = x;
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
		for(int i = 0 ; i < 8 ; i++){
			for(int j = 2 ; j < 6 ; j++){
					board[i][j].curr.pieceDef  = 0;
			}
		}
		for(int i = 0 ; i < 8 ; i++){
			for(int j = 0 ; j < 8 ; j++){
				board[i][j].drawPiece();
			}
			glFlush();
		}

	}

	void getlegal(int a , int b){
		resetLegal();
		vector<int> moves = legalMoves(a*8+b, lastWhite);
		for(int i = 0 ; i < moves.size() ; i++){
			board[moves[i]/8][moves[i]%8].setAslegal();
		}
		for (auto x : moves){
			cout<<x/8<<" "<<x%8<<endl;
		}
	}

	void resetLegal(){
		for(int i = 0 ; i < 8 ; i++){
			for(int j = 0 ; j < 8 ; j++){
				board[i][j].setNormal();
			}
		}
	}

	void move(int a , int b){
		resetLegal();
		move_stack.push_back({lastx*8 + lasty, a*8 + b});

		board[a][b].curr.pieceDef = board[lastx][lasty].curr.pieceDef;
		board[a][b].curr.white = board[lastx][lasty].curr.white;
		board[lastx][lasty].curr.pieceDef = 0;
		board[lastx][lasty].drawPiece();
		board[a][b].drawPiece();

		lastWhite = !lastWhite;
		//cout<<"Moved ("<<lastx<<","<<lasty<<") to ("<<a<<","<<b<<")"<<endl;
	}

 void click(int button, int state, int x, int y){
			if(button == GLUT_LEFT_BUTTON &&state == GLUT_DOWN){
			int a = x;
			int b = 1000 - y;
			cout << a << " " << b << endl;
			a = a/100;
			b = b/100;
			a--,b--;
			if(a>=0&&a<8&&b>=0&&b<8){
				if (board[a][b].legal == true){
					move(a,b);
				}
				else{
					char c = 'A' + b;
					cout << "squareSelected "<<c<<a<<endl;
					cout << "\tsquare color = "<<(board[a][b].white?"white":"black") << endl;
					cout << "\tselected piece = "<<CHESS[board[a][b].curr.pieceDef]<<endl;
					cout << "\tpiece color = "<<(board[a][b].curr.white?"white":"black") << endl;
					getlegal(a,b);
					lastx = a, lasty = b;
				}
			}

		}
	}


}cb;



void click(int button, int state, int x, int y){
	if(button != GLUT_RIGHT_BUTTON){
		cb.click(button,state,x,y);
	}

}

void init2d()//how to display
{
	glClearColor (1.0,1.0,1.0,0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0,1000.0, 0.0, 1000.0);//same like window size(xl,xh,yl,yh)
}

void display(void)
{
	if(value == 1){
    glutPostRedisplay();
		return;
  }
	if(screen_render == 0){
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 0.0, 0.0);
		glRecti(90,90,910,910);
		glColor3f(0.247, 0.345, 0.4);
		glFlush();
		cb.initiate();
		cb.setpieces();
		screen_render = 1;
		cout << "lets start " << endl;
	}


}
void menu(int num){
  if(num == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
		if(num == 1){
			screen_render = 0;
		}
  }
  glutPostRedisplay();
}

void createMenu(void){
		menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Restart", 1);
		glutAddMenuEntry("Undo", 2);
    glutAddMenuEntry("Quit", 0);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize (1000, 1000);
	glutInitWindowPosition (00, 00);
	window = glutCreateWindow ("CHESS");
	init2d();
	glutDisplayFunc(display);
	glutMouseFunc(click);
	createMenu();
	glutMainLoop();

	return 0;
}
