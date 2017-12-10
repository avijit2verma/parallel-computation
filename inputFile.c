/* This program create the input file with 10000 random numbers. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	srand(time(NULL));
	FILE *fp;
	fp = fopen("input.txt","w");
	int n=10000;
	fprintf(fp, "%d\n",n);
	int k,i;
	for(i=0;i<n;i++)
	{
		k=rand()%100;
		fprintf(fp, "%d\n",k);
	}
	fclose(fp);
	return 0;
}