#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

//these variables are shared by the threads
double avg=0,std_dev=0, median=0; int N;

void* calculate_avg(void *  param)
{
	double *nums = (double *) param;
	avg=0;
	for(int i=0;i<N;i++)
		avg+=nums[i];
	avg=(avg)/N;

	//cout<<"Calculated Mean\n";
	//cout<<"Mean is "<<avg<<"\n";

	pthread_exit(0);
}

void* calculate_std_dev(void * param)
{
	double *nums = (double *) param;
	//will calculate std deviation
	double mean=0;
	for(int i=0;i<N;i++)
		mean+=nums[i];
	mean=mean/N;
	//cout<<"\n Got mean as "<<mean<<"\n";
	double sum_of_square_dev_from_mean=0;
	for(int i=0;i<N;i++)
		sum_of_square_dev_from_mean +=(nums[i]-mean)*(nums[i]-mean);
	std_dev = pow((sum_of_square_dev_from_mean/(N)),0.5);
	//cout<<"Calculated Std Dev\n";

	pthread_exit(0);
}

void* calculate_median(void * param)
{
	double *nums = (double *) param;
	//will calculate median
	//double nums1[N];
	double *nums1 = (double *)malloc(sizeof(double)*N);
	for(int i=0;i<N;i++)
		nums1[i]=nums[i];

	sort(nums1, nums1+N);
	if (N%2==0)
		median = (nums1[(N/2)] + nums1[(N/2)-1])/2;
	else
		median = nums1[(N/2)];
	//cout<<"calculated median\n";

	pthread_exit(0);
}

int main()
{
	cin>>N;
	//cout<<N;
	//double nums[N];
	double *nums = (double *)malloc(sizeof(double)*N);
	for(int i=0;i<N;i++)
	{
		cin>>nums[i];
		//cout<<nums[i]<<" ";
	}

	pthread_t tid1, tid2, tid3;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, calculate_avg, nums);
	pthread_create(&tid2, &attr, calculate_std_dev, nums);
	pthread_create(&tid3, &attr, calculate_median, nums);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);



	cout<<"The average value is "<<avg<<"\n";
	cout<<"The standard deviation value is "<<std_dev<<"\n";
	cout<<"The median value is "<<median<<"\n";

	return 0;
}