# include <iostream>
# include <stdlib.h>
# include <iomanip>
# include <mpi.h>
using namespace std;
int main(int argc, char ** argv) {
  int k,p,me,left,right,count = 1, tag = 1, nit = 10, grid_size = 20;
  float ul, ur, u = 1.0, alpha = 1.0, beta = 12.0;
  float u_arr [grid_size+1] = { };
  MPI_Status status;
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &p);
  MPI_Comm_rank (MPI_COMM_WORLD, &me);
  //cout << p <<endl;
  //cout << me <<endl;
  //cout << me % 2 << endl;
   
  left = me-1; right = me+1;
  if (me == 0) ul = alpha; if (me == p-1) ur = beta;
  for (k = 1; k <= nit; k ++) {
    if (me % 2 == 0) {
      if (me > 0)   MPI_Send (&u , count, MPI_FLOAT, left,  tag, MPI_COMM_WORLD);
      if (me < p-1) MPI_Send (&u , count, MPI_FLOAT, right, tag, MPI_COMM_WORLD);
      if (me < p-1) MPI_Recv (&ur, count, MPI_FLOAT, right, tag, MPI_COMM_WORLD, &status);
      if (me > 0)   MPI_Recv (&ul, count, MPI_FLOAT, left , tag, MPI_COMM_WORLD, &status);
    }
    else {
      if (me < p-1) MPI_Recv (&ur, count, MPI_FLOAT, right, tag, MPI_COMM_WORLD, &status);
                    MPI_Recv (&ul, count, MPI_FLOAT, left, tag, MPI_COMM_WORLD, &status);
                    MPI_Send (&u,  count, MPI_FLOAT, left, tag, MPI_COMM_WORLD);
      if (me < p-1) MPI_Send (&u,  count, MPI_FLOAT, right, tag, MPI_COMM_WORLD);
    }
    u = (ul+ur)/2.0;
    //cout <<  setw(3);
    //cout << me << setw(4);
    //cout << k << setw(15);
    //cout << u << endl; //setw (15);
    //cout << ul << setw(15);
    //cout << ur <<endl;
  }
  cout <<  setw(3);
  cout << me <<setw(15);
  cout << u <<endl;  
  MPI_Finalize ();
  //cout << ur <<endl;
  //cout << ul <<endl;
}
 
