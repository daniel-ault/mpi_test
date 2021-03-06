/* calculate the value of pi using random numbers 
   and parallel programming */
   
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define sqr(x)   ((x)*(x))
#define NUM_POINTS  80000000

float rand_float();
void calculate_pi_serial();
void calculate_pi_parallel(int, int);
float dboard(int);

int main(int argc, char *argv[])
{	
	float diff1, diff2;
	clock_t t1, t2;
	int rc;
	int npoints;
	
	float pi,
		  pi_home,
		  pi_sum,
		  pi_average;
		 
	int taskid, numtasks;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	
	t1 = clock();
	npoints = NUM_POINTS/numtasks;
	
	/* This code generates a value of pi in every process */
	int seed = time(NULL);
	srand(seed);
	
	pi_home = dboard(npoints);
	
	rc = MPI_Reduce(&pi_home, &pi_sum, 1, MPI_FLOAT, MPI_SUM, 
					0, MPI_COMM_WORLD);
	
	if (rc != MPI_SUCCESS)
		printf("%d: failure on mpi_reduce\n", taskid);
		
	/* Master computes average for all iterations */
	if (taskid == 0) 
	{
		pi = pi_sum/numtasks;
		printf("Pi calculated using parallel programming is %f.", pi);
		//printf("Average value of pi = %f\n", pi);
	}
	
	MPI_Finalize();
	
	t2 = clock();
	diff2 = (((float)t2 - (float)t1) / 1000000.0F ) * 1000;
	if (taskid == 0)
		printf("Calculating pi parallel took %f milliseconds.\n", diff2);
		
	return 0;
}

void calculate_pi_serial()
{
	float pi = dboard(NUM_POINTS);
	
	printf("Pi calculated serially is %f.\n", pi);
}

void calculate_pi_parallel(int taskid, int numtasks)
{
	int rc;
	int npoints;
	
	float pi,
		  pi_home,
		  pi_sum,
		  pi_average;
	
	npoints = NUM_POINTS/numtasks;
	
	/* This code generates a value of pi in every process */
	int seed = time(NULL);
	srand(seed);
	
	pi_home = dboard(npoints);
	
	rc = MPI_Reduce(&pi_home, &pi_sum, 1, MPI_FLOAT, MPI_SUM, 
					0, MPI_COMM_WORLD);
	
	if (rc != MPI_SUCCESS)
		printf("%d: failure on mpi_reduce\n", taskid);
		
	/* Master computes average for all iterations */
	if (taskid == 0) 
	{
		pi = pi_sum/numtasks;
		printf("Pi calculated using parallel programming is %f.", pi);
		//printf("Average value of pi = %f\n", pi);
	}
	
	MPI_Finalize();
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
