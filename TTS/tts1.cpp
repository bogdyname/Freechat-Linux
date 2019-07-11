#include <iostream>
#include <string>
#include <pthread.h>

using namespace std;

void *ThreadPongStatus(void *pong)
{
	cout << "T1: pong" << endl;

	pthread_exit(0);
}

void *ThreadPingStatus(void *ping)
{
	cout << "T2: ping" << endl;

	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	void *pong = NULL;
	void *ping = NULL;

	pthread_t T1;
	pthread_t T2;

	pthread_create(&T1, NULL, ThreadPongStatus, pong);
	pthread_create(&T2, NULL, ThreadPingStatus, ping);

	for(;;)
	{	
	pthread_join(T1, NULL);
	pthread_join(T2, NULL);
	}

	system("pause");
	return 0;
}
