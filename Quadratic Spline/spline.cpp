#include "spline.h"
#include<GL/freeglut.h>
#include<vector>
#include<iostream>


static Coeficiente a,b,c;


#include<GL/freeglut.h>
#include<cmath>

Ponto2::Ponto2(){}
Ponto2::Ponto2(float x_, float y_)
{
    x=x_;
    y=y_;
}

void Ponto2::desenha()
{
    float incr=0.1;
    float raio=5.0;
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        for(float angulo=0;angulo<2*PI;angulo+=incr)
        {
            float xc=x+raio*cos(angulo);
            float yc=y+raio*sin(angulo);
            glVertex2f(xc,yc);
        }
    glEnd();
}

void Spline::splinePlotQuad(double ai, double bi, double ci,double xmin_, double xmax_)
{
	double x,y;
	double xi=xmax_;
	int n=10;
	int nSubIntervalos=n-1;

	double incr=(xmax_-xmin_)/nSubIntervalos;

	glLineWidth(3.0);
	glLineStipple(2, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glColor3f(1,0.6,0);
	glBegin(GL_LINE_STRIP);
	x=xmin_;

	for(int i=1; i<=n; i++)
	{
		y=ai*(x-xi)*(x-xi)+bi*(x-xi)+ci;
		glVertex2f(x,y);
		x+=incr;
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}


void Spline::quadSpline(Pontos P)
{
	std::vector<double>h;
	int nPts=P.size();// numero de Pontos
	h.clear();
	a.clear();
	b.clear();
	c.clear();

	for(int i=1;i<nPts;i++)
		h.push_back(P[i].x-P[i-1].x);

    a.push_back(0);//a1=0
	double valor=(P[1].y-P[0].y)/h[0];
	b.push_back(valor); // b1

	// Calcula c[i]
	for(int i=1;i<nPts;i++)
		c.push_back(P[i].y);

	// Calcula b[i]
	for(int i=1;i<nPts;i++)
	{
		valor=2/h[i]*(P[i+1].y-P[i].y)-b[i-1];
		b.push_back(valor);
	}
	// Calcula a[i]
	for(int i=1;i<nPts-1;i++)
	{
		valor=(b[i]-b[i-1])/(2*h[i]);
		a.push_back(valor);
	}

	for(int i=0;i<a.size();i++)
	{
		splinePlotQuad(a[i],b[i],c[i],P[i].x,P[i+1].x);

	}

}



