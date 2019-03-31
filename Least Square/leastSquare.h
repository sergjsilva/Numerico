#pragma once
#include <vector>
#include "ponto.h"

void curveFit(std::vector<Ponto2>& p, unsigned grau,float cor[3]);
double calcula(std::vector<double> w, double x);
void drawLine(std::vector<double> w,double xmin, double xmax,float cor[3]);
void drawHiperplane(std::vector<double> w,double xmin, double xmax,float cor[3]);
