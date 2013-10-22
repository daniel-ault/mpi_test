/* calculate the value of pi using random numbers 
   and parallel programming */
   
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

float rand_float();



int main(int argc, char *argv[])
{
	int i, npoints = 1000;
	int circle_count = 0;
	
	int seed = time(NULL);
	srand(seed);
	
	for (i=0; i<npoints; i++)
	{
		double x = random();
		double y = random();
		if ((sqr(x) + sqr(y)) >=1)
			circle_count = circle_count + 1;
	}
	
	double pi = 4.0*circle_count/npoints;
	
	printf("Pi is %d.\n", pi);
	
}


float rand_float()
{
	return -1+2*((float)rand())/RAND_MAX;
}
