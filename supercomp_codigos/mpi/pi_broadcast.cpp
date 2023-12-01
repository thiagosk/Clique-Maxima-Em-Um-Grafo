#include<iostream>  
#include <mpi.h>
using namespace std;
int main() {
    int i, nb_rec = 10000000;
    double x, h, sum = 0.0, pi = 0.0;
    int myRank, size, tag=10;
    int rects_por_proc = 0;
    int meu_inicio = 0, meu_fim = 0;
    double minha_soma = 0.0;
    MPI_Status status;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (myRank == 0) {
        rects_por_proc = nb_rec / size;
    }
    MPI_Bcast(&rects_por_proc, 1, MPI_INT, 0, MPI_COMM_WORLD);

    h = 1.0 / (rects_por_proc * size);

    meu_inicio = myRank * rects_por_proc;
    meu_fim = meu_inicio + rects_por_proc;
    for (i = meu_inicio; i < meu_fim; i++) {
        x = (i+0.5) * h;
        minha_soma += 4.0 / (1.0 + x*x);
    }

    minha_soma = h * minha_soma
    MPI_Reduce(&minha_soma, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD)

    if (myRank == 0) {
        cout << "O valor aproximado de PI é: " << pi << endl;
    }

    MPI_Finalize();
    return 0;
}