
#include "tlpi_hdr.h"

#ifdef NOSYSCALL
static int myfunc() { return 1; }
#endif

int
main(int argc, char *argv[])
{
    int numCalls, j, s;

    numCalls = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-calls") : 10000000;

#ifdef NOSYSCALL
        printf("Calling normal function\n");
#else
        printf("Calling getppid()\n");
#endif

    for (j = 0; j < numCalls; j++)
#ifdef NOSYSCALL
        s = myfunc();
#else
        s = getppid();
#endif

    exit(EXIT_SUCCESS);
}



