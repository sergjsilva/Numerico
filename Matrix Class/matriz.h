#ifndef MAT_H
#define MAT_H

#include<vector>

using std::vector;

const double PI=3.14159265359;

class Mat
{
private:
    double RandomDouble();
    double RandomDouble(double a, double b);


    public:
        vector<vector<double>> mat;
        unsigned row;
        unsigned col;
        Mat(unsigned _row, unsigned _col, double inicial);
        Mat(const Mat& rhs);
        Mat(unsigned _row, unsigned _col);// random entre [0-1]
        Mat(unsigned _row, unsigned _col, double a, double b);//random entre [a,b]
        void print();
        void byUser();
        // Operacoes
        Mat transp();
        void soma(Mat M);
        void sub(Mat M);// A-M subtrai M da matriz original
        Mat mult(Mat M);
        void multby(Mat M); // fica multiplicada por M
        void multN(double n);
        void divRowby(unsigned row_,double num);
        void changeRow(unsigned i, unsigned j);
        void changeCol(unsigned i, unsigned j);
        void splitMat(Mat& A, Mat& B);
        bool isIdentity();

    protected:

    private:
};

namespace std
{
        Mat soma(Mat A, Mat B);
        Mat mult(Mat A, Mat B);
        Mat rotation(double theta);
        Mat idMat(unsigned n);
        Mat mergeMat(Mat A, Mat B);
        Mat rref(Mat M);
        Mat inv(Mat M);
        bool areEqual(double a, double b);
}




#endif // MAT_H
