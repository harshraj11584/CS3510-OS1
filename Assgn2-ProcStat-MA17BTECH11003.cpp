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

struct statistics
{
	double avg=0, std_dev=0, median=0;
};
/*The required statistics have been shared between processes
as a struct.*/

int main()
{
	int status;
	//a variable for debugging
	/*When waiting for a child process to return, &status can
	be passed as second argument instead of NULL to see the status 
	of child process while exit*/
	int N; cin>>N;
	//cout<<N;
	//double nums[N];
	double *nums = (double *)malloc(sizeof(double)*N);
	for(int i=0;i<N;i++)
	{
		cin>>nums[i];
		//cout<<nums[i]<<" ";
	}

	const int SIZE = sizeof(struct statistics);
	//declaring struct to store statistics
	struct statistics stats;
	/* name of the shared memory object */
	const char *name = "OS";
	/* shared memory file descriptor */
	int fd;
	/* pointer to shared memory object */
	struct statistics *ptr;
	/* create the shared memory object */
	fd = shm_open(name,O_CREAT | O_RDWR,0666);
	/* configure the size of the shared memory object */
	ftruncate(fd, SIZE);
	/* memory map the shared memory object */
	ptr = (struct statistics *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	ptr->avg=0; ptr->median=0; ptr->std_dev=0;

	//Declaring process IDs and forking child processes
	pid_t pid,ppid;
	pid=fork();
	ppid=fork();

	if (pid<0 || ppid<0) //error occured while forking processes
		cout<<"Fork Failed\n";
	if (pid>0 && ppid>0) //parent process
	//waits for the children to finish their work
	{
		waitpid(pid, NULL, 0);
		waitpid(ppid, NULL, 0);
		cout<<"The average value is "<<ptr->avg<<"\n";
		cout<<"The standard deviation value is "<<ptr->std_dev<<"\n";
		cout<<"The median value is "<<ptr->median<<"\n";
	}
	if (pid>0 && ppid==0) //Worker process 1
	{
		//will calculate Average Value
		ptr->avg=0;
		for(int i=0;i<N;i++)
			ptr->avg+=nums[i];

		ptr->avg=(ptr->avg)/N;
		waitpid(pid,NULL,0);
		//cout<<"Calculated Mean\n";
		//cout<<"Mean is "<<ptr->avg<<"\n";
	}
	if (pid==0 && ppid>0) //Worker process 2
	{
		//will calculate std deviation
		double mean=0;
		for(int i=0;i<N;i++)
			mean+=nums[i];
		mean=mean/N;
		//cout<<"\n Got mean as "<<mean<<"\n";
		double sum_of_square_dev_from_mean=0;
		for(int i=0;i<N;i++)
			sum_of_square_dev_from_mean +=(nums[i]-mean)*(nums[i]-mean);
		ptr->std_dev = pow((sum_of_square_dev_from_mean/(N)),0.5);
		waitpid(ppid,NULL,0);
		//cout<<"Status is "<<status<<"\n";
		//cout<<"Calculated Std Dev\n";
	}
	if (pid==0 && ppid==0) //worker process 3
	{
		//will calculate median
		double median_ans=0;
		//cout<<"Starting N="<<N<<"\n";
		double *nums_arr = (double *)malloc(sizeof(double)*N);
		for(int i=0;i<N;i++)
			nums_arr[i]=nums[i];
		//cout<<"Copied\n";
		sort(nums_arr, nums_arr+N);
		if (N%2==0)
			median_ans = ( nums_arr[(N/2)] + nums_arr[(N/2)-1] )/2;
		else
			median_ans = nums_arr[((N-1)/2)];
		//cout<<"Median is "<<ptr->median<<"\n";
		//cout<<"calculated median\n";
		ptr->median = median_ans;
	}


	return 0;
}