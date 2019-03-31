#include "ponto.h"
#include <GL/freeglut.h>
#include "matriz.h"
#include "leastSquare.h"
#include <cmath>

void curveFit(std::vector<Ponto2>& p, unsigned grau, float cor[3])
{
    int n=p.size();
    Mat A=Mat(p.size(),grau+1,0);
    Mat b=Mat(p.size(),1);
    for(unsigned i=0;i<A.row;i++)
    {
        b.mat[i][0]=p[i].y;
        for(unsigned j=0;j<A.col;j++)
           A.mat[i][j]=pow(p[i].x,j);
    }

    Mat At=A.transp();
    Mat M=std::mult(At,A);

    Mat N=std::mult(At,b);
    Mat Inversa=std::inv(M);

    Mat result=std::mult(Inversa,N);
    std::vector<double> coeficientes;
    for(unsigned i=0;i<result.row;i++)
        coeficientes.push_back(result.mat[i][0]);

    if(grau==1)
        drawLine(coeficientes,p[0].x,p[n-1].x,cor);
    else
        drawHiperplane(coeficientes,p[0].x,p[n-1].x,cor);
}


double calcula(std::vector<double> w, double x)
{
    double result=0;
    for(unsigned i=0;i<w.size();i++)
        result+=w[i]*pow(x,i);
    return result;
}
// draw y=a+bx
void drawLine(std::vector<double> w,double xmin, double xmax, float cor[3])
{
    double y1=calcula(w,xmin);
    double y2=calcula(w,xmax);
    glColor3fv(cor);
    glBegin(GL_LINES);
        glVertex2d(xmin,y1);
        glVertex2d(xmax,y2);
    glEnd();
}

void drawHiperplane(std::vector<double> w,double xmin, double xmax, float cor[3])
{
    double x,y;
	int n=100;
	int nSubIntervalos=n-1;

	double incr=(xmax-xmin)/nSubIntervalos;

	glLineWidth(3.0);
	glLineStipple(2, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glColor3fv(cor);
	glBegin(GL_LINE_STRIP);
	x=xmin;

	for(int i=1; i<=n; i++)
	{
		y=calcula(w,x);
		glVertex2f(x,y);
		x+=incr;
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

