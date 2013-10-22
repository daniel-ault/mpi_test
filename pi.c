/* calculate the value of pi using random numbers 
   and parallel programming */
   
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define sqr(x)   ((x)*(x))

float rand_float();



int main(int argc, char *argv[])
{
	int taskid, numtasks, rc;
	int npoints = 100000;
	
	float pi,
		  pi_home,
		  pi_sum,
		  pi_average;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	
	/* This code generates a value of pi in every process */
	int seed = time(NULL);
	srand(seed);
	
	float pi_home = dboard(npoints);
	
	rc = MPI_Reduce(&pi_home, &pi_sum, 1, MPI_FLOAT, MPI_SUM, 
					0, MPI_COMM_WORLD);
	
	if (rc != MPI_SUCCESS)
		printf("%d: failure on mpi_reduce\n", taskid);
		
	/* Master computes average for all iterations */
	if (taskid == 0) 
	{
		pi = pi_sum/numtasks;
		printf("Average value of pi = %f\n", pi);
	}

	MPI_Finalize();
		
	return 0;
}

float dboard(int throws)
{
	int i, circle_count = 0;
	
	for (i=0; i<throws; i++)
	{
		float x = rand_float();
		float y = rand_float();
		if ((sqr(x) + sqr(y)) <= 1)
			circle_count = circle_count + 1;
	}
	
	float pi = 4.0*(float)circle_count/(float)throws;

	//printf("Pi is %f.\n", pi);
	
	return pi;
}

float rand_float()
{
  return /*-1+2**/((float)rand())/RAND_MAX;
}
