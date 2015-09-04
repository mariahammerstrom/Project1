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

//typedef double* arraypoint;


// Main program
int main()
{
    clock_t start, finish; // declare start and final time
    start = clock();

    // START CODE
    int n,i,j;
    n = 10;
    double h = 1./(n+1);


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
    ofstream file_analytic("Project1_analytic_solution.txt");

    double x[n],u_analytic[n],f[n];

    for(i=0 ; i<n ; i++){
        x[i] = i*h;
        u_analytic[i] = u_solution(x[i]);
        f[i] = f_func(x[i]);
        file_analytic << x[i] << "\t" << u_analytic[i] << "\t" << n << endl;
    }
    file_analytic.close();


    // SIMPLE ALGORITHM
    ofstream file_simple("Project1_simple_algorithm.txt");

    // Forward substitution:
    double u[n],temp[n];
    u[0] = 0;

    double btemp = b[1];
    u[1] = h*h*f[1]/btemp;

    for(i=2 ; i <= n-1 ; i++){
        temp[i] = c[i-1]/btemp;
        btemp = b[i]-a[i]*temp[i];
        u[i] = (h*h*f[i] - a[i]*u[i-1])/btemp;
    }

    // Backward substitution:
    for(i=n-1 ; i >= 0 ; i--){
        u[i] -= temp[i+1]*u[i+1];
        file_simple << x[i] << "\t" << u[i] << "\t" << n << endl;
    }

    file_simple.close();

    // ERROR
    double e[n], err[n], max=0.0;
    for(i=1 ; i < n ; i++){
      e[i] = (u[n-i]-u_analytic[i])/u_analytic[i];
      err[i] = log10(fabs(e[i]));
      if (err[i]>max)
          max = fabs(e[i]);
    }

    cout << "Max relative error: "<< max << endl;

    double ** A;
    A = new double*[n];
    for (i = 0; i < n; i++)
        A[i] = new double[n];

    /*
    arraypoint *A = new arraypoint[n];
    for(i=0 ; i<n ; i++)
        A[i] = new double[n];
    */

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


    // LU DECOMP: use lib.cpp function: void ludcmp(double **a, int n, int *indx, double *d)
    // Solve linear equation using LU decomposition with function: void lubksb(double **a, int n, int *indx, double *b)

    double d;
    int *indx = new int[n];
    ludcmp(A, n, indx, &d); // changes A to LU decomposition

    lubksb(A, n, indx, f); // is this correct? How to make a plot?


    finish = clock(); // final time
    cout << ((finish - start)/CLOCKS_PER_SEC) << " seconds"; // print elapsed time

     for (i=0; i<n ; i++)
         delete [] A[i];
     delete [] A;

    return 0;
}
