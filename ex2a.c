/* File: ex2a.c
    program to check if son can randomize numbers in set times
  =============================================================
  Writen by: Yehu Raccah, id = 315346726, login = yehura
 
    the program will fork to create a son process and using 
    SIGALRM will find out if it takes it 1 second, 2 seconds, or more
    to randomize 100000 numbers
    if it finished in under 1 second it will print 1
    more than 1 second and under 2 it will print 2
    else will print 0
*/

//-------------------------include--------------------------
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

//-------------------------prototypes--------------------------[
void catch_alarm(int sig_num);
void do_child();


int alarmstatus = 1;//global variable to check if didnt finish under 1sec

int main(){

    pid_t status;
    int how;
    

    srand(17);

    status = fork();

    if(status < 0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if(status == 0){   
        do_child();
    }
    else{

        wait(&how);
        //prints the value according to son exit value
        if(WIFEXITED(how)){
            int exit_status  = WEXITSTATUS(how);
            if(exit_status == 1){
                printf("1\n");
            }
            else if(exit_status == 2){
                printf("2\n");
            }
            else{
                printf("0\n");
            }
        }
        
    }
    return EXIT_SUCCESS;

}

void do_child(){
    signal(SIGALRM, catch_alarm);
    alarm(1);//set alarm for a second
    int i, range = pow(10, 5) * 2;
    int x;

    while(1){
        for(i = 0; i < 100000; i++){
             x = rand() % range;
        }
        if(alarmstatus == 1){
            exit(1);
        }
        else{ //if global variable hasbeen increased
            exit(2);
        }
    }
}

void catch_alarm(int sig_num){
    //we reached here after the first timer but program hasnt finished
    if(alarmstatus == 1){
        alarmstatus++;
        alarm(1);
        return;
    }
    //has been more than two seconds
    exit(3);
}
