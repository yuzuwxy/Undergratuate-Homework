#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid, pr;			// 是fork函数的返回值
	pid = fork();
	if (pid < 0){
		perror("fork failed");
		exit(1);
	}
	if (pid == 0){
		sleep(10);
		exit(0);
	}
	else {
		while(pr == 0) {
			pr = waitpid(pid, NULL, WNOHANG);		// 使用WNOHANG，不会在此等待
			if( pr == 0) {
				printf("The Child process is still running\n");
				sleep(1);								// 每一秒执行一次循环
			}
		}
		if(pid == pr) 
			printf("Succefully catched the chile process with PID of %d\n", pr);
		else
			printf("Some error occured\n");
	}
	return 0;
}


