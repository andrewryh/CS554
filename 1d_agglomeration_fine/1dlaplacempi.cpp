# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <iomanip>
# include <mpi.h>

using namespace std;
int main(int argc, char ** argv) {
  int k,p,me,left,right,count = 1, tag = 1, nit = 1000, N = 16;
  float ul, ur, u = 1.0, alpha = 1.0, beta = 12.0;
    
  MPI_Status status;
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &p);
  MPI_Comm_rank (MPI_COMM_WORLD, &me);
  printf ("Hello world from processor, rank %d"
	  " out of %d processors\n", me, p);
  int z = N/p;
  float u_arr[z] = { };
  left = me-1; right = me+1;
  
  for (k = 1; k <= nit; k ++) {
    //if (me % 2 == 0) {
      if (me > 0)   MPI_Send (&u_arr[0] , count, MPI_FLOAT, left,  tag, MPI_COMM_WORLD);
      if (me < p-1) MPI_Send (&u_arr[z-1], count, MPI_FLOAT, right, tag, MPI_COMM_WORLD);
      if (me < p-1) MPI_Recv (&ur, count, MPI_FLOAT, right, tag, MPI_COMM_WORLD, &status); //z-1
      if (me > 0)   MPI_Recv (&ul, count, MPI_FLOAT, left , tag, MPI_COMM_WORLD, &status);
      //}
      //else {
      //if (me < p-1) MPI_Recv (&ur, count, MPI_FLOAT, right, tag, MPI_COMM_WORLD, &status);
      //              MPI_Recv (&ul, count, MPI_FLOAT, left, tag, MPI_COMM_WORLD, &status);
      //              MPI_Send (&u,  count, MPI_FLOAT, left, tag, MPI_COMM_WORLD);
      // if (me < p-1) MPI_Send (&u,  count, MPI_FLOAT, right, tag, MPI_COMM_WORLD);
      //}
      if (me == 0) u_arr[0] = alpha;      else  u_arr[0]   =  (ul+u_arr[1])/2.0;
      if (me == p-1) u_arr[z - 1] = beta; else  u_arr[z-1] = (u_arr[z-2]+ur)/2.0;;
      for (int i=1; i < z-1; i ++) {	
      u_arr[i] = (u_arr[i-1]+u_arr[i+1])/2.0;
      }

    //cout <<  setw(3);
    //cout << me << setw(4);
    //cout << k << setw(15);
    //cout << ul << setw(15);
    //cout << ur <<endl;
  }
  //cout <<  setw(3);
  //cout << me <<setw(15);
  //cout << u <<endl;
  //if (me == 0) printf ("Hello world, %d process only %d\n",me,u);
  for (int m = 0; m <= me; m ++) {
    if (me == m) {
      //      printf ("From processor %d, only ", me);
      for(int j = 0; j < z; j++) { printf ("U[%d]=%f; ",j+me*z,u_arr[j]); }
           }


  }
          printf ("\n");
  
  MPI_Finalize ();




//printf("U[1]=%f, U[1]=%f, U[2]=%f, U[3]=%f, U[4]=%f, U[5]=%f, %d\n", alpha, u_arr[0], u_arr[1],u_arr[2],u_arr[3], beta, me);
}


