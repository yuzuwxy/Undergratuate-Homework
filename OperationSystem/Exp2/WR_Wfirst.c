#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/*
 * 多线程，写者优先
 */

int n_writer, n_reader;
pthread_mutex_t mutex_write;
pthread_mutex_t readable;
sem_t sem_read,  sem_write;

int readerCnt = 0, writerCnt = 0;

void Toread() {
	printf("Reading......\n");
	printf("writerCnt = %d\n", writerCnt);
	printf("readerCnt = %d\n", readerCnt);
}

void Towrite() {
	printf("Writing......\n");
	printf("writerCnt = %d\n", writerCnt);
	printf("readerCnt = %d\n", readerCnt);
}

void* writer() {
	while(1) {
		sem_wait(&sem_write);	// 互斥访问写者数量
		writerCnt ++;
		if(writerCnt == 1) 
			pthread_mutex_lock(&readable);// 有写者，为读进程加锁
		sem_post(&sem_write);

		pthread_mutex_lock(&mutex_write);
		printf("Writing Process in(ID: %ld)\n", pthread_self());
		Towrite();
		printf("Writing Process out(ID: %ld)\n\n", pthread_self());
		pthread_mutex_unlock(&mutex_write);

		sem_wait(&sem_write);
		writerCnt --;
		if(writerCnt == 0)
			pthread_mutex_unlock(&readable);
		sem_post(&sem_write);

		sleep(1);
	}
}

void* reader() {
	while(1) {
		pthread_mutex_lock(&readable);
		sem_wait(&sem_read);
		// 如果是第一个读者，占用数据区
		if(readerCnt == 0) pthread_mutex_lock(&mutex_write);
		readerCnt ++;
		sem_post(&sem_read);
		pthread_mutex_unlock(&readable);

		printf("Reading process in(ID: %ld)\n", pthread_self());
		Toread();
		printf("Reading process out(ID: %ld)\n\n", pthread_self());
	
		sem_wait(&sem_read);
		readerCnt --;
		if(readerCnt == 0) pthread_mutex_unlock(&mutex_write);
		sem_post(&sem_read);
		
		sleep(1);
	}
}

int main() {
	printf("Input n_writer = ");scanf("%d", &n_writer);
	printf("Input n_reader = ");scanf("%d", &n_reader);

	pthread_t writerid[n_writer];
	pthread_t readerid[n_reader];

	pthread_mutex_init(&mutex_write, NULL);
	pthread_mutex_init(&readable, NULL);
	sem_init(&sem_read, 0, 1);
	sem_init(&sem_write, 0, 1);

	for(int i = 0; i < n_writer; i ++)
		pthread_create(&writerid[i], NULL, writer, NULL);
	for(int i = 0; i < n_reader; i ++)
		pthread_create(&readerid[i], NULL, reader, NULL);

	for(int i = 0; i < n_writer; i ++)
		pthread_join(writerid[i], NULL);
	for(int i = 0; i < n_reader; i ++)
		pthread_join(readerid[i], NULL);

	sleep(1);
	return 0;
}
