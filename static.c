//The full program, say static.c, would look like this: 
//This code create look up table in C base on Fs and block size

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define N 200 
#define pi 3.14159265358979323846

int main (void) 
{ 
	float t[N], f[N];
	int i;
	float freq = 12000;

	for (i = 0; i < N; i++)
	{ 
		t[i] = (float)(i) / (((float)(N) - 1.0)*1000);
		f[i] = sin(2 * pi * freq * t[i]);
		//printf("The value t[%d] %f\n",i,t[i]);
		printf("The value f[%d] %f\n",i,f[i]);
	}

	return EXIT_SUCCESS; 
}
