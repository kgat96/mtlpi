#include <time.h>
#include <pthread.h>
#include "tlpi_hdr.h"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static int avail;

static void *threadFunc(void *reg)
{
	int cnt = atoi((char *)reg);
	int s, j;

	for (j = 0; j < cnt; j++) {
		sleep(1);

		s = pthread_mutex_lock(&mtx);
		if (s != 0)
			errExitEN(s, "pthreaf_mutex_lock");
		avail ++;

		s = pthread_mutex_unlock(&mtx);
		if (s != 0)
			errExitEN(s, "pthreag_mutex_unlock");
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t tid;
	int s, j;
	int totRequired;
	int numConsumed;
	bool done;

	time_t t;

	t = time(NULL);
	totRequired = 0;
	for (j = 0; j < argc; j++) {
		totRequired += atoi(argv[j]);
		s = pthread_create(&tid, NULL, threadFunc, argv[j]);
		if (s != 0)
			errExitEN(s, "pthread_create");
	}

	numConsumed = 0;
	done = FALSE;

	for (;;) {
		s = pthread_mutex_lock(&mtx);
		if (s != 0)
			errExitEN(s, "pthread_mutex_lock");

		while( avail > 0) {
			numConsumed ++;
			avail --;
			printf("T=%ld: numConsumed=%d\n", (long) (time(NULL) - t),
					numConsumed);
			done = numConsumed >= totRequired;
		}

		s = pthread_mutex_unlock(&mtx);
		if (s != 0)
			errExitEN(s, "pthreaf_mutex_unlock");

		if (done)
			break;
	}

	exit(EXIT_SUCCESS);
}

