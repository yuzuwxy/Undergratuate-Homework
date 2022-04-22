#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	execl("./multixx.out","multixx.out","-l","-h",NULL);
	// execlp("/home/yuzu/桌面/Codefield/multixx.out","multixx.out","-l","-h",NULL);
	// char *argv[5] = {"multixx.out", "-l", "-h", NULL};
	// execv("./multixx.out",argv);
	// execv("/home/yuzu/桌面/Codefield/multixx.out", argv);
	perror("exec ps");
	exit(1);
	return 0;
}
