/* File: ex2b.c

  =============================================================
  Writen by: Yehu Raccah, id = 315346726, login = yehura
 
    the program will fork to create a son process.
    both father and son will run in an infinite loop until they either
    send 7 signals to the other, or received 5 signals from the other.

    race conditions:
    worst race condition in the program is the option for the father to win,
    in that case the son will continue running until it sent 7 signals

*/

//-------------------------include--------------------------
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//-------------------------prototypes--------------------------
void catch_usr(int sig_num);
void catch_term(int sig_num);
bool is_prime(int num);
bool is_bigger_than_dividers(int num);
void do_work(const pid_t other_pid);

//-------------------------global variables--------------------------
static int usr1 = 0, usr2 = 0;
static pid_t father_pid, son_pid;

int main(){
    pid_t status;

    signal(SIGUSR1, catch_usr);
    signal(SIGUSR2, catch_usr);
    signal(SIGTERM, catch_term);

    status = fork();
    if(status < 0 ){
        perror("cannot fork");
        exit(EXIT_FAILURE);
    }
    else if( status == 0 ){
        son_pid = getpid();
        father_pid = getppid();
        srand(18);
        do_work(father_pid);
    }
    else{
        son_pid = status;
        father_pid = getpid();
        srand(17); 
        do_work(son_pid);
    }


    return EXIT_SUCCESS;
}

//need other_pid to know who to send sigusr to
void do_work(const pid_t other_pid){
    int random_num, prime_sent = 0, divider_sent = 0;

    while(1){
        sleep(rand()%3);
        random_num = rand() % 1000;

        if(random_num <= 100){
            exit(EXIT_SUCCESS);
        }
        else if(is_prime(random_num)){
            kill(other_pid, SIGUSR1);
            divider_sent++;
        }
        else if(is_bigger_than_dividers(random_num)){
            kill(other_pid, SIGUSR2);
            prime_sent++;
        }
        if(prime_sent == 7 || divider_sent == 7){
            printf("you probably ended\n");
            exit(EXIT_SUCCESS);
        }

    }
}
//catch SIGUSR1 and SIGUSR2
void catch_usr(int sig_num){
    if(sig_num == SIGUSR1){
        usr1++;
    }
    else{
        usr2++;
    }

    if(usr1 >= 5 || usr2 >= 5){
        printf("process %d surrender\n", (int)getpid());
        if(getpid() == father_pid){
            kill(son_pid, SIGTERM);
        }
        else if(getpid() == son_pid){
            kill(father_pid, SIGTERM);
        }
    }
}
//catch SIGTERM
void catch_term(int sig_num){
    printf("process %d win\n", getpid());
    exit(EXIT_SUCCESS);
}

//check for prime numbers
bool is_prime(int num){
    int i, sqrtnum = (int)sqrt(num);

    if(num <= 1){
        return false;
    }

    for(i = 2; i < sqrtnum; i++){
        if(num % i == 0){
            return false;
        }
    }
    return true;
}
//check sum of the dividers
bool is_bigger_than_dividers(int num){
    int sum = 0, i;

    for(i = 1; i < num/2 ; i++){
        if(num % i == 0){
            sum += i;
        }
    }

    if(sum >= num){
        return true;
    }
    return false;
}