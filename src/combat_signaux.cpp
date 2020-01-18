#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "rsleep.h"
#include <csignal>
#include <time.h>
using namespace std;

void attaque(pid_t adversaire) {
	int compteur = 3;
	sigset_t setneg;
	sigdelset(&setneg, SIGINT);
	signal(SIGINT,
			[](int sig) {compteur--;cout<<"nombre de vie qui rest"<<compteur;});
	if (compteur == 0) {
		cout << "process is finished";
		exit(1);
	}

	if(kill(adversaire, SIGINT)==-1){
		exit(0);
	}
	randsleep();
}

void defense() {
		signal(SIGINT,SIG_IGN);
		randsleep();

}
void combat(pid_t adversaire) {

	while(1){
		defense();
		attaque(adversaire);
	}
}
void sig_hand(int sig){
	cout<<"coup pare"<<endl;
}
int main(int argc, char **argv) {
	pid_t vador ; //pere
	pid_t luke; //fils
	pid_t pid;

	vador=getpid();
	pid= fork();
	if(pid==0)
	{
		luke=getpid();
		//defense*******
		sigset_t sig_proc;
		struct sigaction action;
		sigemptyset(&sig_proc);
		action.sa_mask=sig_proc;
		action.sa_flags = 0;
		action.sa_handler = sig_hand;
		sigaction(SIGINT,&action,NULL);
		//masquer signal
		sigprocmask(SIG_SETMASK,&sig_proc,NULL);
		randsleep();
		sigsuspend(&sig_proc);
		//*********
		attaque(vador); //attaque
	}
	else{
		//waiting between 0.3 and 1 second
		randsleep();
		//finish wait
		combat(luke);
	}

	return 0;
}
