#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

int main(){
	pid_t pid;			// 是fork函数的返回值
	string message;
	int n;
	int count=0;
	pid = fork();
	if (pid < 0){
		perror("fork failed");
		exit(1);
	}
	if (pid == 0){
		message = "This is the child\n";
		n = 6;
		// cout << "I am the child process, my process id is " << getpid() << '\n';
		// count ++;
	}
	else {
		message = "This is the parent\n";
		n = 3;
		// cout << "I am the parent process, my process id is " << getpid() << '\n';
		// count ++;
	}
	for(; n > 0; n--) {
	  	cout<<message;
	    sleep(1);
	}
	// cout << "count: " << count << '\n';
	return 0;
}