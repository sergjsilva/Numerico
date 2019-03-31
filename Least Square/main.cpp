#include <GL/freeglut.h>
#include <vector>
#include "ponto.h"
#include "leastSquare.h"

#include <iostream>

using namespace std;

int LARGURA=800;
int ALTURA=500;

std::vector<Ponto2> Pontos;
bool useLinear=false;
bool useQuad=false;
bool useCubic=false;

void idle();
void key(unsigned char key, int x, int y);
void display();
void ordenaPts(std::vector<Ponto2>& v);
void criaPts(int botao, int status, int x, int y);
void setcolor(float (&cor)[3], float r, float g, float b);


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(LARGURA, ALTURA);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutCreateWindow("Ajuste de Curvas - Mar 2019");
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0,LARGURA,0,ALTURA);

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
   // glutIdleFunc(idle);
    glutMouseFunc(criaPts);


    glutMainLoop();

    return EXIT_SUCCESS;
}

void criaPts(int botao, int status, int x, int y)
{
    int yc=ALTURA-y;

    if(botao==GLUT_LEFT_BUTTON)
        if(status==GLUT_DOWN)
        {
            Ponto2 P(x,yc);
            Pontos.push_back(P);
        }
    ordenaPts(Pontos);
    glutPostRedisplay();
}

void ordenaPts(std::vector<Ponto2>& v)
{
    for(unsigned i=0;i<v.size();i++)
    {
        for(unsigned j=i+1;j<v.size();j++)
        {
            Ponto2 temp;
            if(v[j].x<v[i].x)
            {
                temp=v[i];
                v[i]=v[j];
                v[j]=temp;
            }
        }
    }

}
void setcolor(float (&cor)[3],float r, float g, float b)
{
    cor[0]=r;
    cor[1]=g;
    cor[2]=b;
}
void display(void)
{
    float cor[3];

    glClearColor(0.5,0.5,0.5,1);
    glClear(GL_COLOR_BUFFER_BIT);

    for(unsigned i=0;i<Pontos.size();i++)
        Pontos[i].show();

    if(useLinear)
    {
        setcolor(cor,1,0,0);
        curveFit(Pontos,1,cor);
    }

    if(useQuad)
    {
        setcolor(cor,0,1,0);
        curveFit(Pontos,2,cor);
    }

    if(useCubic)
    {
        setcolor(cor,1,1,0);
        curveFit(Pontos,3,cor);
    }


    glutSwapBuffers();
}


void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
            exit(0);
            break;
        case 'l':
            useLinear=true;
            break;
        case 'q':
            useQuad=true;
            break;
        case 'c':
            useCubic=true;
            break;

        case 32 :
            useLinear=false;
            useQuad=false;
            useCubic=false;
            break;


    }

    glutPostRedisplay();
}

void idle(void)
{
    glutPostRedisplay();
}
