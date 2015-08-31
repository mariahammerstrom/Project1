// PROJECT 1
// Set of linear equations

#include <iostream>
#include <time.h>
#include <math.h>
#include "lib.h"

using namespace std;
//using namespace arma;

// Functions
double u(double x)
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
    int n;
    double h = 1./(n+1);


    // Define a, b, c
    // ...


    // SIMPLE ALGORITHM
    // Forward substitution:
    btemp = b[1];
    u[1] = f[1]/btemp;
    for(i=2; i <= n; i++) {
        temp[i] = c[i-1]/btemp;
        btemp = b[i]-a[i]*temp[i];
        u[i] = (f[i] - a[i]*u[i-1])/btemp;
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
    // ...


    // END CODE


    finish = clock(); // final time
    cout << ((finish - start)/CLOCKS_PER_SEC) << " seconds"; // print elapsed time

    return 0;
}

