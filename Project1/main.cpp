// PROJECT 1
// Set of linear equations

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include "lib.h"
//#include <armadillo>

using namespace std;
//using namespace arma;

// Functions
double u_sol(double x)
{
    return 1 - (1 - exp(-10))*x - exp(-10*x);
}

double f(double x)
{
    return 100*exp(-10*x);
}


// Main program
int main()
{
    clock_t start, finish; // declare start and final time
    start = clock();

    // START CODE
    int n,i,j;
    double h = 1./(n+1);


    // Define a, b, c
    // ...


    //n = 10;
    int A[n][n];
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

    // SIMPLE ALGORITHM
    // Forward substitution:
    btemp = b[1];
    u[1] = h^2*f[1]/btemp;
    for(i=2; i <= n; i++) {
        temp[i] = c[i-1]/btemp;
        btemp = b[i]-a[i]*temp[i];
        u[i] = (h^2*f[i] - a[i]*u[i-1])/btemp;
    }

    // Backward substitution:
    for(i=n-1; i >= 1; i--) {
        u[i] -= temp[i+1]*u[i+1];
    }



    // GAUSSIAN
    // ...

    // LU DECOMP: use lib.cpp function: void ludcmp(double **a, int n, int *indx, double *d)
    // Solve linear equation using LU decomposition with function: void lubksb(double **a, int n, int *indx, double *b)
    // ...

    // ERROR
    // double e[], err[];
    //for (i=1 ; i < n ; i++){
    //  e[i] = (v[i]-u[i])./u[i];
    //  err[i] = log10(abs(e[i]));
    //}


    // END CODE


    finish = clock(); // final time
    cout << ((finish - start)/CLOCKS_PER_SEC) << " seconds"; // print elapsed time

    return 0;
}

