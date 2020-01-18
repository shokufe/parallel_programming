#define _POSIX_SOURCE 1
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "rsleep.h"
#include <csignal>
#include <time.h>
#include <stdlib.h>
using namespace std;


int wait_till_pidsig(pid_t pid, int sec){
	clock_t begin = clock();
	if((begin-sec>=0)&&!WIFEXITED(pid))
		{
		signal(SIGALRM);
		}
	else if(WIFEXITED(pid)||WIFSIGNALED (pid)){
		signal(SIGCHLD);
	}
	else{
		return -1;
	}
}
int wait_till_pid(pid_t pid, int sec){
	pid_t pid_pro;
	pid_pro= wait(pid);
	clock_t begin = clock();

	if((begin-sec>=0)&&!WIFEXITED(pid))
	{
		return 0;
	}
	else
	   if(WIFEXITED(pid)||WIFSIGNALED (pid)){
		return getpid();
	}
	else {
		return -1;
	}
}
int main3(int argc, char **argv){
	pid_t pid_fils;
		int status;
		int const N;
		sigset_t setneg;
		clock_t sec=2;
		for (int i=0;i<N;i++){
			if (fork()==0){
				cout<<"fils pid:"<<getpid()<<" "<<"ppid"<< getppid();
			}
			else{
			//avec wait
				for(int i=0;i<N;i++){
					int result=wait_till_pid(status,sec);
					if(result==-1){
						cout<<"error in child ";
					}
					if(result==0){
						cout<<"time expire";

					}
					else{
						cout<<"finish normaly";
					}
					}

				}
			//avec signal
				for(int i=0;i<N;i++)
				{
					wait_till_pidsig(getpid(), sec);
					sigsuspend(&setneg);

				}
		}

return 0;
}
