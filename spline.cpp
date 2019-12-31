/*
# ______________________________________________________________________________________________________________
# Cubic Spline Interpolation
# ______________________________________________________________________________________________________________
# In general form, Cubic Spline Interpolation takes N points: (x0,y0), (x1, y1), (x2, y2)
# and calculate N-1 functions S0(x), S1(x).. with the following form:
# si(x) = ai + bi(x-xi) + ci(x-xi)^2 + di(x-xi)^3, for x in rage [xi,yi]
# in the program we will calculate the coefficients = [ a0,a1,a2..., b0,b1,b2..., c0, c1,c2... , d0,d1,d2...]
# 
# ______________________________________________________________________________________________________________
*/
#include <stdio.h>
#include <iostream>
#include <iomanip>

#define N 2 // Points - 1

// receives x,y (array of points), and return cubic spline coefficients A,B,C,D
void Spline(double x[N + 1], double y[N + 1],double A[N], double B[N], double C[N], double D[N])
{
    double h[N];                            // delta x
    double b[N];                            // delta y / delta x
    double ftt[N + 1];                      // f''(xi)

    // calc h & b
    for (int i = 0; i < N; i++)
    {
        h[i] = (x[i + 1] - x[i]);
        b[i] = (y[i + 1] - y[i]) / h[i];
    }

    // calc f''(xi)
    ftt[0] = 0; // f''(x0) = 0
    for (int i = 0; i < N - 1; i++)
        ftt[i + 1] = 3 * (b[i + 1] - b[i]) / (h[i + 1] + h[i]);
    ftt[N] = 0; // f''(xn) = 0

    // calc spline coefficients
    for (int i = 0; i < N; i++)
    {
        A[i] = (ftt[i + 1] - ftt[i]) / (6 * h[i]);
        B[i] = ftt[i] / 2;
        C[i] = b[i] - h[i] * (ftt[i + 1] + 2 * ftt[i]) / 6;
        D[i] = y[i];
    }
}

// receives points and Spline coefficients and print the functions
void PrintSpline(double x[N + 1],double A[N], double B[N], double C[N], double D[N]) 
{
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    for (int i = 0; i < N; i++)
    {
        std::cout << "[" << x[i] << "," << x[i+1] << "] f(x) = ";
        if (A[i])
            std::cout << A[i] << "(x-" << x[i] << ")^3 + ";
        if (B[i])
            std::cout << B[i] << "(x-" << x[i] << ")^2 + ";
        if (C[i])
            std::cout << C[i] << "(x-" << x[i] << ") + ";
        if (D[i])
            std::cout << D[i];
        
        std::cout << std::endl;
    }
}

int main()
{
    double x[N + 1] = {1, 2, 3};
    double y[N + 1] = {2, 3, 5};
    double A[N], B[N], C[N], D[N];
    Spline(x, y, A, B, C, D);
    PrintSpline(x, A, B, C, D);
    return 0;
}
