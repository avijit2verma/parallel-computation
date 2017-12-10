# Demonstration of speedup in computation using Amdahl's law

This program was written for an assignment in the Operating Systems laboratory during my time at IIT Bhubaneswar. 

The aim is to count the occurrences of number “3” in the generated input file. Assuming that the user will provide number of threads as input through command line,  the number of threads is varied from 1 to 16 and the time taken by various sections of the code is recorded. Using Amdahl’s Law on the execution times for I/O and counting, the speedup respect to number of threads is plotted in Speedup.png.

<b>How to run the program?</b>

- Create the input file “input.txt” using the following commands: 

$  gcc –o  file  inputFile.c 

$ ./file 

- Run the multi-threaded program for calculating the speedup using the following commands: 

$  gcc –o  thread  thread.c 

$ ./thread  [Number of threads]  (command line input) 

- The program “thread.c” writes to the file “output.txt” in append mode in the format. 

#Number of threads <space> Speedup  

- The file “ouput.txt” is used for plotting the speedup graph using gnuplot. The plot is attached in the file “Speedup.png”. In the gnuplot terminal type: 

$ plot “output.txt” using 1:2 with lines 

Labels to the axes and title have also been set in the plot attached. 

Cheers.
