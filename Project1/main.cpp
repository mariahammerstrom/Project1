// PROJECT 1
// Set of linear equations

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <fstream>
//#include <armadillo>
#include "lib.h"

using namespace std;
//using namespace arma;

// Functions
double u_solution(double x){
    return 1 - (1 - exp(-10))*x - exp(-10*x);
}

double f_func(double x){
    return 100*exp(-10*x);
}


// Main program
int main()
{
    clock_t start, finish; // declare start and final time, tridiagonal algorithm
    start = clock();

    // START CODE
    int n,i,j;
    n = 10000;
    double h = 1./(n+1);
    cout << "n = " << n << endl;

    // Define a, b, c
    double a[n],b[n],c[n];
    a[0] = 0;
    b[0] = 2;
    for(i=1; i<n; i++){
        a[i] = -1;
        b[i] = 2;
        c[i-1] = -1;
    }
    c[n] = 0;


    // ANALYTICAL SOLUTION
    ofstream file_analytic("Project1_analytic_solution_n" + to_string(n) + ".txt");

    double x[n],u_analytic[n],B[n];

    for(i=0 ; i<n ; i++){
        x[i] = i*h;
        u_analytic[i] = u_solution(x[i]);
        B[i] = h*h*f_func(x[i]);
        file_analytic << x[i] << "\t" << u_analytic[i] << endl;
    }
    file_analytic.close();


    // SIMPLE ALGORITHM
    ofstream file_simple("Project1_simple_algorithm_n" + to_string(n) + ".txt");

    // Forward substitution:
    double u[n],temp[n];
    u[0] = 0;

    double btemp = b[1];
    u[1] = B[1]/btemp;

    for(i=2 ; i <= n-1 ; i++){
        temp[i] = c[i-1]/btemp;
        btemp = b[i]-a[i]*temp[i];
        u[i] = (B[i] - a[i]*u[i-1])/btemp;
    }

    // Backward substitution:
    for(i=n-1 ; i >= 0 ; i--){
        u[i] -= temp[i+1]*u[i+1];
        file_simple << x[i] << "\t" << u[i] << endl;
    }

    file_simple.close();

    finish = clock(); // final time
    cout << "Time (tridiagonal): " << "\t" << ((finish - start)/CLOCKS_PER_SEC) << " seconds" << endl; // print elapsed time


    // ERROR
    double e[n], err[n], max=0.0;
    for(i=1 ; i < n ; i++){
      e[i] = (u[n-i]-u_analytic[i])/u_analytic[i];
      err[i] = log10(fabs(e[i]));
      if (err[i]>max)
          max = fabs(e[i]);
    }

    cout << "Max relative error: "<< max << endl;


    // LU DECOMPOSITION
    clock_t start_LU, finish_LU; // declare start and final time, LU decomposition
    start_LU = clock();

    double ** A;
    A = new double*[n];
    for (i = 0; i < n; i++)
        A[i] = new double[n];

    for(i=0 ; i<n ; i++){
        for(j=0 ; j<n ; j++){
            if(j==i)
                A[i][j] = 2;
            else if(j == i+1 || j == i-1)
                A[i][j] = -1;
            else
                A[i][j] = 0;
        }
    }

    // LU decomp: use lib.cpp function: void ludcmp(double **a, int n, int *indx, double *d)
    // Solve linear equation using LU decomposition with function: void lubksb(double **a, int n, int *indx, double *b)

    double d;
    int *indx = new int[n];
    ludcmp(A, n, indx, &d); // changes A to LU decomposition
    lubksb(A, n, indx, B); // is this correct? How to make a plot?

    finish_LU = clock(); // final time
    cout << "Time (LU decomp):" << "\t" << ((finish_LU - start_LU)/CLOCKS_PER_SEC) << " seconds" << endl; // print elapsed time

    ofstream file_LUdecomp("Project1_LU_decomp_n" + to_string(n) + ".txt");

    for(i=0 ; i<n ; i++){
        file_LUdecomp << x[i] << "\t" << B[i] << endl;
    }

    file_LUdecomp.close();


     for (i=0; i<n ; i++)
         delete [] A[i];
     delete [] A;


     // FLOPS
     // Double check these formulas! Also, need proportionality constants.

     double FLOPS_tridiagonal = 8*n;
     double FLOPS_Gaussian = (3./2)*n*n*n + n*n;
     double FLOPS_LUdecomp = n*n*n;

     cout << endl << "FLOPS" << endl;
     cout << "Tridiagonal: " << "\t" << FLOPS_tridiagonal << endl;
     cout << "Gaussian: " << "\t" << FLOPS_Gaussian << endl;
     cout << "LU decomp: " << "\t" << FLOPS_LUdecomp << endl;

    return 0;
}
