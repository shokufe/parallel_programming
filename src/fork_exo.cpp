#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>

using namespace std;
int main() {

	int nbfils = 0;
	const int N = 3;
	cout << "main pid=" << getpid() << endl;

	for (int i = 1, j = N; i <= N && j == N; i++) {
		if (fork() != 0) {
			nbfils++;


			break;
		} else {
			nbfils=0;
			cout << " i:j " << i << ":" << j << endl;

			for (int k = 1; k <= i && j == N; k++) {
				if (fork() == 0) {
					nbfils=0;
					j = 0;
					cout << " k:j " << k << ":" << j << endl;
				}
				else{
					nbfils++;
				}
			}
		}
	}

	for (int i = 0; i < nbfils; i++) {
		int pid = wait(nullptr);
		cout<<"fin fils "<<(i+1)<<" de pid "<< pid << endl;
	}

	return 0;
}
