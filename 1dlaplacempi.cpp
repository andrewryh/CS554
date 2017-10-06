# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <iomanip>
# include <mpi.h>

using namespace std;
int main(int argc, char ** argv) {
  int k,p,me,left,right,count = 1, tag = 1, nit = 10000;
  long N = 5120000;
  float ul, ur, u = 1.0, alpha = 1.0, beta = 12.0;

  MPI_Status status;
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &p);
  MPI_Comm_rank (MPI_COMM_WORLD, &me);

  //MPI_Barrier(MPI_COMM_WORLD);
  //double t1 = MPI_Wtime();   
  //printf ("Hello world from processor, rank %d out of %d processors\n", me, p);
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
  }
  //for (int m = 0; m <= me; m ++) {
  //  if (me == m) {
      //      printf ("From processor %d, only ", me);
  //   for(int j = 0; j < z; j++) { printf ("U[%d]=%f; ",j+me*z,u_arr[j]); }
  //       }
  //MPI_Barrier(MPI_COMM_WORLD);
  //double elapsedTime = MPI_Wtime() - t1;
  //double totalTime;
  // if (me == 0) { /* use time on master node */
  // printf("Runtime = %fsec\n", totalTime);
  //	   } 
  MPI_Finalize ();
}
