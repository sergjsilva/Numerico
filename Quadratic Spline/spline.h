#pragma once
#include <vector>

const float PI=3.14159265;

struct Ponto2{
	    float x;
        float y;
        Ponto2();
        Ponto2(float x_, float y_);
        void desenha();
};

typedef std::vector<double> Coeficiente;
typedef std::vector<Ponto2> Pontos;

namespace Spline
{
    void splinePlotQuad(double ai, double bi, double ci,double xmin_, double xmax_);
    void quadSpline(Pontos P);
}
