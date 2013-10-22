/* calculate the value of pi using random numbers 
   and parallel programming */
   
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define sqr(x)   ((x)*(x))

float rand_float();



int main(int argc, char *argv[])
{
	int i, npoints = 10000;
	
	for (i=0; i<20; i++)
		dboard(npoints);
		
	return 0;
}

int dboard(int throws)
{
	int i, circle_count = 0;
	
	int seed = time(NULL);
	srand(seed);
	
	for (i=0; i<throws; i++)
	{
		float x = rand_float();
		float y = rand_float();
		if ((sqr(x) + sqr(y)) >=1)
			circle_count = circle_count + 1;
	}
	
	double pi = 4.0*(float)circle_count/(float)throws;
	
	printf("circle_count is %d.\n", circle_count);
	//printf("Pi is %d.\n", pi);
	
	return 1;
}

float rand_float()
{
  return /*-1+2**/((float)rand())/RAND_MAX;
}
