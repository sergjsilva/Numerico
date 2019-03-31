#include<GL/freeglut.h>
#include<cstdlib>
#include<cmath>
#include<string>
#include <sstream>
#include<vector>
#include<iostream>
#include "spline.h"


using namespace std;

const int LARGURA=800;
const int ALTURA=500;

Pontos nos; // Guarda os nos

bool usaQuadSpline=false;



void ordenaPts()
{
    for(int i=0;i<nos.size(); i++)
    {
        for(int j=i+1;j<nos.size();j++)
        {
            Ponto2 temp;
            if(nos[j].x<nos[i].x)
            {
                temp=nos[i];
                nos[i]=nos[j];
                nos[j]=temp;
            }
        }
    }
}

void teclado(unsigned char tcl,
					int x, int y) {
	switch (tcl)
	{
		case 27: //Esc
			exit(0); //Exit the program
        case 's':
            usaQuadSpline=true;
            break;

        case 32: // Barra de Espaco
            usaQuadSpline=false;
            break;

	}
    glutPostRedisplay();
}

void criaPts(int botao, int  status, int x, int y)
{
    int yc=ALTURA-y;

	if(botao==GLUT_LEFT_BUTTON)
		if(status==GLUT_DOWN)
		{
			Ponto2 P(x,yc);
			nos.push_back(P);
		}
    ordenaPts();
    glutPostRedisplay();
}

void desenha()
{
	glClearColor(0,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	for(int i=0; i< nos.size(); i++)
		nos[i].desenha();

    if(usaQuadSpline)
        Spline::quadSpline(nos);
	glutSwapBuffers();
}


int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(LARGURA,ALTURA);
	glutCreateWindow("Quadratic Spline - Numerico 2018/02 - UFR");


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0,LARGURA, 0, ALTURA);

	glutDisplayFunc(desenha);
	glutKeyboardFunc(teclado);
	glutMouseFunc(criaPts);

	glutMainLoop();

	return 0;
}

