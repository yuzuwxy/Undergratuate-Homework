#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

/*
 * 多线程，读者优先
 */

int n_writer, n_reader;// 读者数量与写者数量，需要用户输入
pthread_mutex_t mutex_write;// 一次只有一位写者进行写操作，设置互斥信号量
sem_t sem_read;// 实现对读者数量的互斥

int readerCnt = 0;// 读者数量，当读者数量为0时，写者才可以访问

void Toread() {
	printf("Read......\n");
	printf("readerCnt = %d\n", readerCnt); 
}

void Towrite() {
	printf("Write......\n");
	printf("readerCnt = %d\n", readerCnt);
}

void* writer() {
	while(1) {
		pthread_mutex_lock(&mutex_write);// 写进程加锁（为啥不是trylock?
	
		printf("Writing Process in(ID: %ld)\n",pthread_self());
		Towrite();// 进行写操作
		printf("Writing Process out(ID: %ld)\n\n",pthread_self());
	
		pthread_mutex_unlock(&mutex_write);
		sleep(1);
	}
}

void* reader() {
	while(1) {
		sem_wait(&sem_read);			// 对读者数量的互斥访问
		readerCnt++;
		if(readerCnt == 1) 				// 读者优先：只有当读者全部退出后才可以写
			pthread_mutex_lock(&mutex_write);
		sem_post(&sem_read);
	
		printf("Reading Process in(ID: %ld)\n", pthread_self());
		Toread();
		printf("Reading Process out(ID: %ld)\n\n", pthread_self());

		sem_wait(&sem_read);
		readerCnt--;
		if(readerCnt == 0)
			pthread_mutex_unlock(&mutex_write);
		sem_post(&sem_read);
		sleep(1);
	}
}

int main() {
	printf("Input n_writer = ");scanf("%d", &n_writer);
	printf("Input n_reader = ");scanf("%d", &n_reader);

	pthread_t writerid[n_writer];
	pthread_t readerid[n_reader];// 存储读者与写者的进程id

	pthread_mutex_init(&mutex_write, NULL);
	sem_init(&sem_read, 0, 1);// 初始化信号量
	// 创建读者进程
	for(int i = 0; i < n_writer; i ++)
		pthread_create(&writerid[i], NULL, writer, NULL);
	// 创建写者进程
	for(int i = 0; i < n_reader; i ++)
		pthread_create(&readerid[i], NULL, reader, NULL);

	for(int i = 0;i < n_writer; i ++)
		pthread_join(writerid[i], NULL);
	for(int i = 0;i < n_reader; i ++)
		pthread_join(readerid[i], NULL);
	sleep(1);
	return 0;
}
