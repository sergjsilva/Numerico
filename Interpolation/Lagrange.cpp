#include<glut.h>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include"plot.h"
#include<string>
#include <sstream>

//#include<vector>

// -lglut32 -lglu32 -lopengl32

using namespace std;

float xmin=-5;
float xmax=5;
float ymin=-1.5;
float ymax=1.5;

int nPts=5;
Pontos Pts; // Guarda os nos
int contador=0;
int sentido=1;
const float FPS=2;
std::string funcText[]={"f(x)=1.0/(1.0+x*x)", "f(x)=cos(x)", "f(x)=sin(2*x)","f(x)=cos((x*x)/(1+x*x))", "f(x)=cos(sin(3.0*x))"};

string intToString(int number){

	//this function has a number input and string output
	std::stringstream ss;
	ss << number;
	return ss.str();
}

float fx1(float x)
{
	//funcText="f(x)=1.0/(1.0+x*x)";
	return 1.0/(1.0+x*x);
}
	
float fx2(float x)
{
	//funcText="f(x)=cos(x)"; 	
	return cos(x);
}

float fx3(float x)
{
	//funcText="f(x)=sin(2*x)"; 	
	return sin(2*x);
}
/*
float fx4(float t)
	
	float a=t*t;
	float b=1+t*t;
	float temp=cos(a/b);
	return temp;
}
*/

float fx4(float x)
{
	float a=x*x;
	float b=1+x*x;
	return cos(a/b);
}


float fx5(float x)
{
	return cos(sin(3.0*x));
}

void teclado(unsigned char tcl, //guarda a tecla pressionada
					int x, int y) {    //Coordenadas do Mouse 
	switch (tcl) {
		case 27: //Escape key
			exit(0); //Exit the program			
	}
}

TipoFunction functions[]={fx1, fx2, fx3, fx4, fx5};
int numFunctions=(sizeof(functions)/sizeof(*functions));
int index=0;
int contafunc=0;

void criaPts(int botao, int status, int x, int y)
{
	if(botao==GLUT_LEFT_BUTTON)
		if(status==GLUT_DOWN)
			if(nPts<20)
				nPts++;
	
	if(botao==GLUT_RIGHT_BUTTON)
		if(status==GLUT_DOWN)
			if(nPts>5)
				nPts--;
	
	glutPostRedisplay();	
}

void criar_Pontos(TipoFunction f, int n, Pontos& P, float xmin, float xmax)
{
	int nSubIntervalos=n-1;
	float x=xmin;
	float y=f(x);
	float incr=(xmax-xmin)/nSubIntervalos;
	
	P.clear();
	for(int i=0; i<n; i++)
	{
		Ponto2 p(x,y);
		//Pts.push_back(p);
		P.push_back(p);
		x+=incr;
		y=f(x);			
	}					
}
 


float L(int i,float x)
{
	float num=1.0;
	float denom=1.0;
	
	for(int j=0;j<nPts;j++)
		if(j!=i)
		{
			num=num*(x-Pts[j].x);
			denom=denom*(Pts[i].x-Pts[j].x);
		}	
	return num/denom;
}

float Lagrange(float x)
{
	float soma=0.0;
	for(int i=0;i<nPts;i++)
		soma=soma+L(i,x)*Pts[i].y;
	
	return soma;
}


void desenha()
{
	
	index=contafunc%numFunctions;
	MyRGB backcolor(1,1,1);
	glClearColor(backcolor.R,backcolor.G,backcolor.B,0); // ajusta a cor 
	glClear(GL_COLOR_BUFFER_BIT);// limpa com a cor ajustada	
	
	MyRGB corEixo(0,0,1);
	desenha_Eixos(xmin,xmax,ymin,ymax, corEixo);
	//criar_Pontos(&fx,nPts,Pts,xmin,xmax);
	criar_Pontos(functions[index],nPts,Pts,xmin,xmax);
	//cgCriarPontos(f,nos,npts);
	MyRGB corPts(1.0,0,0);// Pts Vermelhos
	plotPoints(Pts, corPts);
	
	
	myplotaxis(xmin-0.2,xmax+0.2,ymin-0.2, ymax+0.2, corEixo);
	
	
	
	// Desenha Função
	MyRGB corFuncao(0.8,0.0,0.2);
	glLineWidth(2.0);
	//myplot(fx, xmin, xmax,corFuncao);
	myplot(functions[index], xmin, xmax,corFuncao);
	// Desenha Interpolação
	glLineStipple(2, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);  
	MyRGB corLagrange(0,0.8,0.2);
	glLineWidth(2.0);
	myplot(Lagrange, xmin, xmax,corLagrange);
	glDisable(GL_LINE_STIPPLE);
	
	// Imprime os Textos na Tela
	std::string grauText = "Grau "+ intToString(nPts);
	myText(funcText[index],0.5, ymax);
	myText(grauText,0.5, ymin);
	//glFlush();
	glutSwapBuffers();
}


void idle(int)
{
	nPts+=sentido;
	
	if(nPts>49)
		sentido=sentido*(-1);
	if(nPts<6)
	{
		sentido=sentido*(-1);
		contafunc++;
	}
	
	glutPostRedisplay();
	glutTimerFunc(1000/FPS,idle,0);
}



int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(1024,700);
	glutCreateWindow("Lagrange");
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(xmin-0.5,xmax+0.5,ymin-0.5, ymax+0.5);
	
	glutDisplayFunc(desenha);
	glutKeyboardFunc(teclado);
	glutMouseFunc(criaPts);
	glutTimerFunc(1000/FPS,idle,0);
	glutMainLoop();
		
	return 0;
}
