#include "tlpi.h"

int main(int argc, char *argv[])
{
    int pfd[2];
    int j, dummy;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s sleep-time .. \n", argv[0]);

    setbuf(stdout, NULL);

    printf("Parent started\n");

    if (pipe(pfd) == -1)
        errExit("pipe");

    for (j = 1; j < argc; j++) {
        switch (fork()) {
        case -1:
            errExit("fork %d", j);
            break;
        case 0:
            if (close(pfd[0]) == -1)
                errExit("close");

            /* Child does some work, and lets parent know it's done */

            sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
            printf("Child %d (PID=%ld) closing pipe\n", j, (long) getpid());

            if (close(pfd[1]) == -1)
                errExit("close");

            /* Child now carries on to do other things... */

            _exit(EXIT_SUCCESS);
        default:
            break;
        }
    }

    /* Parent comes here; close write end of pipe so we can see EOF */

    if (close(pfd[1]) == -1)
        errExit("close");

    /* Parent may do other work, then synchronizes with children */

    if (read(pfd[0], &dummy, 1) != 0)
        fatal("parent didn't get EOF");
    printf("Parent ready to go\n");

    exit(EXIT_SUCCESS);
}
