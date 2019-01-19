# CS3510 : OS1
performance comparison between multi-thread and multi-process program

MultiProcess Program - Assgn2-ProcStat-MA17BTECH11003.cpp, 
Multithreaded Program - Assgn2-ThStat-MA17BTECH11003.cpp

Both programs calculate 3 statistics - mean, standard deviation, and median for a given set of values.
Sample Input Files have been included. (in1000000.txt has 1000000 values, ... , in5000000.txt has 5000000 values)


A report on performance comparison between these programs has been included in Assgn2Report-MA17BTECH11003.pdf

## Running Instructions - 

Assgn2-ProcStat-MA17BTECH11003.cpp : 

Open the folder containing 'Assgn2-ProcStat-MA17BTECH11003.cpp' in the terminal.
Execute 'g++ Assgn2-ProcStat-MA17BTECH11003.cpp -lrt -o proc-stat' to compile the program.
If the input file is 'in.txt' and output is required in file 'proc_out.txt', then execute './proc-stat <in.txt >proc_out.txt'
Run 'time ./proc-stat <in.txt' to see the time taken.
The output has been stored in 'proc_out.txt'.

Assgn2-ThStat-MA17BTECH11003.cpp :

Open the folder containing 'Assgn2-ThStat-MA17BTECH11003.cpp' in the terminal.
Execute 'g++ Assgn2-ThStat-MA17BTECH11003.cpp -lpthread -o th-stat' to compile the program.
If the input file is 'in.txt' and output is required in the file 'th_out.txt', execute './th-stat <in.txt >th_out.txt'
Run 'time ./th-stat <in.txt' to see the time taken.
The output has been stored in 'th_out.txt'.
