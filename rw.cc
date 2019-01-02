#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;
pthread_rwlock_t rwlock;
int book = 0;
int num = 10;

void* reader(void* arg)
{
    while(1){
        pthread_rwlock_rdlock(&rwlock);   //写阻塞
        cout << "Reader num: "<< (int)arg << "book read: " <<  book << endl; 
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
}

void* writer(void* arg)
{
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);   //读阻塞，写互斥
        book++;
        cout << "Writer num: "<< (int)arg << "book write: " << book << endl;
        pthread_rwlock_unlock(&rwlock);
        sleep(2);
    }
}
int main()
{
    pthread_rwlock_init(&rwlock,NULL);
    pthread_t tid[num];
    int i=0;
    for(i=0;i<8;i++){
        pthread_create(&tid[i],NULL,reader,(void*)i);
    }
    for(;i<num;i++){
        pthread_create(&tid[i],NULL,writer,(void*)i);
    }
    for(i=0;i<num;i++){
        pthread_join(tid[i],NULL);
    }
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
