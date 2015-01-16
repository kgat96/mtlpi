#include <ctype.h>
#include "tlpi.h"

#define BUF_SIZE 100

int main(int argc, char *argv[])
{
    char buf[BUF_SIZE];
    int outbound[2];
    int inbound[2];

    int j;
    ssize_t cnt;

    if(pipe(outbound) == -1)
        errExit("pipe");
    if (pipe(inbound) == -1)
        errExit("pipe");

    switch (fork()) {
    case -1:
        errExit("fork");
        break;
    case 0:
        printf("%d %d child\n", getpid(), __LINE__);

        /* child process */
        if (close(outbound[1] == -1))  // close out-write
            errExit("close");

        if (close(inbound[0]) == -1)   // close in-read
            errExit("close");

        /* Read data from "outbound" pipe, convert to uppercase,
           and send back to parent on inbound pipe */
        while ((cnt = read(outbound[0], buf, BUF_SIZE)) > 0) {
            for (j = 0; j < cnt; j++)
                buf[j] = toupper((unsigned char) buf[j]);

            if (write(inbound[1], buf, cnt) == -1)
                errExit("write");
        }

        if (cnt == -1)
            errExit("read");
        _exit(EXIT_SUCCESS);

    default:
        printf("%d %d father\n", getpid(), __LINE__);

        if(close(outbound[0]) == -1)
            errExit("close");
        if (close(inbound[1]) == -1)
            errExit("close");

        /* Read data from stdin, send to the child via the
           outbound pipe, read the results back from the child
           on the inbound pipe, and print them on stdout */
        while((cnt = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
            if (write(outbound[1], buf, cnt) == -1)
                errExit("write");

            cnt = read(inbound[0], buf, BUF_SIZE);
            if (cnt == -1)
                errExit("read");
            if (cnt > 0)
                if (write(STDOUT_FILENO, buf, cnt) == -1)
                    errExit("write");
        }

        if (cnt == -1)
            errExit("read");

        exit(EXIT_SUCCESS);
    }
}
