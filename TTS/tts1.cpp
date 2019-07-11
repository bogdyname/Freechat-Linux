#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

inline void *ThreadStatus(void *someArg)
{
	int loc_id = * (int *) someArg;
	for(unsigned int i = 0; i < 2; i++)
	{
		cout << "T" << i  << ":"  << loc_id  << endl;
		sleep(1);
	}
}

int main(int argc, char *argv[])
{
	int T1 = 1;
	int T2 = 2;
	int result;

	pthread_t threadOne;
	pthread_t threadTwo;

	result = pthread_create(&threadOne, NULL, ThreadStatus, &T1);

	if(result != 0)
	{
		perror("T1: pong");
		return EXIT_FAILURE;
	}
	else
	{
		/*clear code*/
	}


	result = pthread_create(&threadTwo, NULL, ThreadStatus, &T2);

	if(result != 0)
	{
		perror("T2: ping");
		return EXIT_FAILURE;
	}
	else
	{
		/*clear code*/
	}

	sleep(2);
	cout << "Loading..." << endl;

	result = pthread_join(threadOne, NULL);
	if(result != 0)
	{
		perror("Wait first torrent");
		return EXIT_FAILURE;
	}
	else
	{
		/*clear code*/
	}

	result = pthread_join(threadTwo, NULL);
       if(result != 0)
       {
       		perror("Wait second torrent");
		return EXIT_FAILURE;
       }	       
       else
       {
       		/*clear code*/
       }

	cout << "Loading..." << endl;
	cout << "Exit" << endl;
	return EXIT_SUCCESS;

	system("pause");
	return 0;
}
