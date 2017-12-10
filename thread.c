/*
	OS Lab Assignment 4
	Submitted by - Avijit Verma
				   14CS01043
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/sem.h>
#include <time.h>
#include <sys/time.h>

int counter=0;
int arr[10000],intval,num,num_thread;
pthread_mutex_t lock;

struct timeval startread, startcalc, finish, readtime, calctime, overalltime;

/* Thread Function */
void *compute(void *arg)
{
	int c = (int *)arg;
	//printf("%d\n",c);
	int i;
	
	if (c==num_thread)       //for counting 3's in the last interval
	{
		for(i=(c-1)*intval;i<num;i++)
		{
			if(arr[i]==3)
			{
				pthread_mutex_lock(&lock);     /* Lock is used while incrementing the value 
												  global counter variable. */
				counter++;
				pthread_mutex_unlock(&lock);
			}
		}
	}
	else
	{
		for(i=(c-1)*intval;i<c*(intval);i++)  //for counting 3's in all the other intervals
		{
			if(arr[i]==3)
			{
				pthread_mutex_lock(&lock);
				counter++;
				pthread_mutex_unlock(&lock);
			}
		}
	}
	
	pthread_exit(NULL);

}



int main(int argc, char *argv[])
{
	int i,j,check;
	pthread_t thread[20];
	//printf("Enter the number of threads\n");
	//scanf("%d",&num_thread);
	if(argc!=2)
	{
		printf("\nEnter in format: ./thread [Number of threads]\n\n");
		exit(1);
	}
	num_thread = atoi(argv[1]);
	pthread_mutex_init(&lock,NULL);
	FILE *out;
	FILE *fp;
	char *line = NULL;
	size_t len=0;
	ssize_t read;
	
	gettimeofday(&startread,NULL); //start time of reading
	
	fp=fopen("input.txt","r");
	read=getline(&line,&len,fp);   //read the first line of input file containing number of numbers
	
	num=atoi(line);
	
	printf("%d\n",num);
	
	
    intval=num/num_thread;
	
	i=0;
	//Transfer all the numbers into an array from the file
	while(read=getline(&line,&len,fp) != -1)
	{
		check=atoi(line);
		arr[i]=check;
		i++;
	}
	free(line);
	
	gettimeofday(&startcalc,NULL); //start time of calculation
	
	for (i=0;i<num_thread;i++)
	{
		pthread_create(&thread[i],NULL,compute,(void *)(i+1));
	}
	for (j=0;j<num_thread;j++)
	{
		pthread_join(thread[j],NULL);
	}
	
	gettimeofday(&finish,NULL); //finish time 
	
	fclose(fp);
	
	timersub(&startcalc,&startread,&readtime);
	timersub(&finish,&startcalc,&calctime);
	timersub(&finish,&startread,&overalltime);
	
	printf("Number of 3's = %d\n",counter);
	
	//printf("%d\t%ld.%ld\n",num_thread,calctime.tv_sec,calctime.tv_usec);
	double P,speedup;
	double x=calctime.tv_sec*1000000 + calctime.tv_usec;
	double y=overalltime.tv_sec*1000000 + overalltime.tv_usec;

	//printf("%lf\n",x);
	//printf("%lf\n",y);
	
	// Calculating the parallelization of the program
	P = x/y;
	printf("Parallelization factor = %lf\n",P);

	// Calculating the speedup of the program using Amdahl's Law
	speedup = 1/((1-P)+(P/num_thread));
	printf("Speedup of the program = %lf times that of single core execution.\n\n",speedup);
	
	// Write the speedup to "output.txt" for plotting
	out=fopen("output.txt","a");
	fprintf(out,"%d %lf\n",num_thread,speedup);
	fclose(out);
	
	return 0;
} 
