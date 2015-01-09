#include <stdio.h>
#include <sys/wait.h>
#include "tlpi.h"

#define BUF_SIZE 10

int main(int argc, char *argv[])
{
    int pfd[2];
    char buf[BUF_SIZE];
    ssize_t numRead;

    if (argc != 2 || strcmp(argv[1], "-- help") == 0) {
        printf("help help .......\n");
        exit(EXIT_FAILURE);
    }

    if (pipe(pfd) == -1) {
        printf("pipe error %s\n", strerror(errno));
        return -1;
    }

    switch (fork()) {
    case -1:
        exit(EXIT_FAILURE);
        break;
    case 0:
        if (close(pfd[1]) == -1) {
            printf("clode fd error !");
            exit(EXIT_FAILURE);
        }
        for (;;) {
            numRead = read(pfd[0], buf, BUF_SIZE);
            if (numRead == -1) {
                printf("%d\n", __LINE__);
                exit(EXIT_FAILURE);
            }

            if (numRead == 0) /* eof for file */
                break;

            if (write(STDOUT_FILENO, buf, numRead) != numRead)
                printf("child -- partial/failed write");
        }

        write(STDOUT_FILENO, "\n", 1);
        if (close(pfd[0]) == -1)
            printf("close pfd[0] err\n");
        _exit(EXIT_SUCCESS);

    default:
        if (close(pfd[0]) == -1) {
            printf("close pfd[0] err\n");
            exit(EXIT_FAILURE);
        }

        if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
            fatal("parent - parial/failed write\n");

        if (close(pfd[1] == -1))
            errExit("close");
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}

