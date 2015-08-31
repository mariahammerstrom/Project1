// PROJECT 1
// Set of linear equations

#include <iostream>
#include <time.h>
#include <math.h>
#include <armadillo>

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

    // GAUSSIAN
    // …

    // LU DECOMP
    // …

    // ERROR
    // …


    // END CODE


    finish = clock(); // final time
    cout << ((finish - start)/CLOCKS_PER_SEC) << " seconds"; // print elapsed time

    return 0;
}

