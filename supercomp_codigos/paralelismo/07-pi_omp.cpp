#include<iostream>
#include<omp.h>
#include <iomanip>
#define NUM_THREADS 4
using namespace std;

int main(){

   long num_steps = 10000000;

   double step;

   int i, nthreads;
   double x, pi, sum[NUM_THREADS];
   double tdata = omp_get_wtime();
   step = 1.0/(double) num_steps;
   omp_set_num_threads(NUM_THREADS);
   #pragma omp parallel
   {
       int id;
       
       id = omp_get_thread_num();
       nthreads = omp_get_num_threads();
       for (i = id, sum[id] = 0.0; i < num_steps; i = i + nthreads) {
           x = (i+0.5)*step;
           sum[id] += 4.0/(1.0 + x*x);
       }
   }
   for(i = 0, pi = 0.0; i < nthreads; i++) {
     pi += sum[i] * step;
   }
   tdata = omp_get_wtime() - tdata;
   cout << "valor de PI aproximado: " << pi << endl;
   cout << "tempo em segundos: " << setprecision(10) << tdata << endl;

    return 0;
}