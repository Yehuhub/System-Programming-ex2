# System Programming - EX2
## An exercise done as part of system programming course to learn the use of signals

File: ex2a.c
  program to check if son can randomize numbers in set times
  =============================================================
  Writen by: Yehu Raccah
 
    the program will fork to create a son process and using 
    SIGALRM will find out if it takes it 1 second, 2 seconds, or more
    to randomize 100000 numbers
    if it finished in under 1 second it will print 1
    more than 1 second and under 2 it will print 2
    else will print 0
  
  Compile: gcc ex2a.c -Wall -o ex2a  
  Run: ./ex2a  
  input: no input  
  output: 1 if finished under 1 sec,
          2 if finished under 2 sec,
          0 if finished over 2 sec.


  File: ex2b.c
  =============================================================
  Writen by: Yehu Raccah
 
    the program will fork to create a son process.
    both father and son will run in an infinite loop until they either
    send 7 signals to the other, or received 5 signals from the other.

    race conditions:
    worst race condition in the program is the option for the father to win,
    in that case the son will continue running until it sent 7 signals
  
  Compile: gcc ex2b.c -Wall -o ex2b  
  Run: ./ex2b  
  input: no input  
  output: process <pid> win. for the process that finishes first,
          process <pid> surrender. for the process that didnt  
