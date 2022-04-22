#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;			// 是fork函数的返回值
	pid = fork();
	if (pid < 0){
		perror("fork failed");
		exit(1);
	}
	if (pid == 0){
		printf("This is the child precess with pid of %d\n", getpid());
		exit(3);		// 子进程返回3,非正常退出
	}
	else {
		int status;
		pid_t pr = wait(&status);
		if(WIFEXITED(status)){// 如果WIFEXITED返回非零值
			printf("the child process %d exit normally\n", pr);
			printf("the return code id %d\n", WEXITSTATUS(status));
		}else{			// 如果WIFEXITED返回0
			printf("the child process %d exit abnormally\n", pr);
		}
	}
	return 0;
}
