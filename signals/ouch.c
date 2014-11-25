#include <signal.h>
#include "tlpi_hdr.h"

static void sigHandler(int sig)
{
    printf("Ouch !\n");
}

int main(int argc, char *argv[])
{
    int j;

    if (signal(SIGINT, sigHandler) == SIG_ERR)
        errExit("signal");

    for (j = 0;; j++) {
        printf("%daaaaaaaaaaaaaaaaaaaaaaaaaa\n", j);
        sleep(2);
    }

    return 0;
}



