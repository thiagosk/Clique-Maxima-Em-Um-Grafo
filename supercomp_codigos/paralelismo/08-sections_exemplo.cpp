#include<iostream>
#include<omp.h>
#include <unistd.h>
using namespace std;


int main() {
    long int i1, i2, imax = 1e9;
    double sum1 = 0, sum2 = 0;

    #pragma omp parallel sections num_threads(3)
    {
        #pragma omp section 
        {
            for(i1 = 0; i1 < imax; i1++) 
                sum1 +=  i1;
            cout << "Task 1 - Done." << endl; 
        }

        #pragma omp section 
        {
            for(i2 = 0; i2 < imax; i2++)
                sum2 -= i2;
            cout << "Task 2 - Done." << endl;

        }

        #pragma omp section
        {
            for(;i1<imax && i2<imax;){
                sleep(1);
                cout << "Task 3 - i1 = " << i1 << " i2 = " << i2 << endl;
            }
        }
   
    }
    
        
    return 0;
}



