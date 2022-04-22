#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

/*
 * ���̣߳���������
 */

int n_writer, n_reader;// ����������д����������Ҫ�û�����
pthread_mutex_t mutex_write;// һ��ֻ��һλд�߽���д���������û����ź���
sem_t sem_read;// ʵ�ֶԶ��������Ļ���

int readerCnt = 0;// ��������������������Ϊ0ʱ��д�߲ſ��Է���

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
		pthread_mutex_lock(&mutex_write);// д���̼�����Ϊɶ����trylock?
	
		printf("Writing Process in(ID: %ld)\n",pthread_self());
		Towrite();// ����д����
		printf("Writing Process out(ID: %ld)\n\n",pthread_self());
	
		pthread_mutex_unlock(&mutex_write);
		sleep(1);
	}
}

void* reader() {
	while(1) {
		sem_wait(&sem_read);			// �Զ��������Ļ������
		readerCnt++;
		if(readerCnt == 1) 				// �������ȣ�ֻ�е�����ȫ���˳���ſ���д
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
	pthread_t readerid[n_reader];// �洢������д�ߵĽ���id

	pthread_mutex_init(&mutex_write, NULL);
	sem_init(&sem_read, 0, 1);// ��ʼ���ź���
	// �������߽���
	for(int i = 0; i < n_writer; i ++)
		pthread_create(&writerid[i], NULL, writer, NULL);
	// ����д�߽���
	for(int i = 0; i < n_reader; i ++)
		pthread_create(&readerid[i], NULL, reader, NULL);

	for(int i = 0;i < n_writer; i ++)
		pthread_join(writerid[i], NULL);
	for(int i = 0;i < n_reader; i ++)
		pthread_join(readerid[i], NULL);
	sleep(1);
	return 0;
}
