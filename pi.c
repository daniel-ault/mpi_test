/* calculate the value of pi using random numbers 
   and parallel programming */
   
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int rand_lim(int limit);



int main(int argc, char *argv[])
{
	int i, npoints = 1000;
	int circle_count = 0;
	/*
	for (i=0; i<npoints; i++)
	{
		double x = random();
		double y = random();
	}
	*/
	
	for (i=0; i<100; i++)
		printf("%d\n", random);
}


double random()
{
	return ( (double)rand() / (double)RAND_MAX )*2 - 1;
}