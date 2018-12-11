#include <signal.h>
#include <wait.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char i = '0';
char bin[32] = {'0'};

int l = 0;
int call = 0;
pid_t c_pid;
pid_t p1_pid;
pid_t p2_pid;

void sig_handler(int signo) {
    pid_t my_pid = getpid();
    
    if (my_pid == p2_pid) {
        //printf("It's in sig_handler && my_pid == p2_pid");
        if(signo == SIGUSR1)
       	    i = '0';
        if(signo == SIGUSR2)
            i = '1';
        get_mail();
    } else {
        //printf("It's in sig_handler && my_pid == p1_pid");
        l = 0;
    }
}

void int_2_bin(int n) {
    for(int j = 32; j > 0; j--) {
        if ((n & 0x1) == 1)
            bin[j] = '1';
        if ((n & 0x1) == 0)
            bin[j] = '0';
        n = n >> 1;
    }
}

void send_bin_with_signal() {
    for(int j = 0; j < 32; j++) {
        printf("j = %d\n", j);
        while(l);
        if(bin[j] == '0') {
            kill(p2_pid, SIGUSR1);
        } else {
            kill(p2_pid, SIGUSR2);
        }
        l = 1;
        
    }
}

void get_mail(){
    bin[call] = i;
    call++;
    
    kill(p1_pid, SIGUSR2);
    
}

int pow_2(int z) {
    int res = 1;
    if(z == 0) {
        return 1;
    } else {
         for(int j = 0; j < z; j++) {
		res *= 2;
	 }
         return res;
    }
}

int bin_to_int() {
    int k = 0;
    int tiv = 0;
    for(int j = 0; j < 32; j++) {
	if(bin[j] == '1'){
	   k = 1;
	} else {
	   k = 0;
	}
	//printf("k = %d\n", k);
	tiv = tiv + k * pow_2(31 - j);
    }
    return tiv;
}

int main() {

    (void) signal(SIGUSR1, sig_handler);
    (void) signal(SIGUSR2, sig_handler);
               	
        p2_pid = getpid();
        
        printf("insert pid p1\n p2 pid is %d\n", p2_pid);
        scanf("%d", &p1_pid);
        
        
        while (call != 32);
        printf("bin = %s \n", bin);
	//

//bin_to_int();
	int tiv = bin_to_int();
        printf("num = %d\n", tiv);
    
    return 0;
}


