#include<iostream>
#include<omp.h>
#include <math.h>
using namespace std;

int fib (int n) {
    int x, y;
    if(n<2) return n;
    if (n < 20) {
        return fib(n-1) + fib(n-2);
    } else {
    #pragma omp task shared(x) 
    x = fib(n-1);     
    #pragma omp task shared(y)
    y = fib(n-2);
    #pragma omp taskwait
    return x+y;
    }    
}

int main() {
    int NW = 50;
    float time;
    time = omp_get_wtime();
    #pragma omp parallel 
    {   
        #pragma omp single
        fib(NW);
    }
    time = omp_get_wtime() - time;
    cout << "Tempo em segundos : " << time << endl;
}






