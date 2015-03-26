#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi.h"

int main(int argc, char *argv[])
{
    char *src, *dst;
    int fdSrc, fdDst;
    struct stat sb;

    if (argc != 3)
        usageErr("%s source-file dest-file\n", argv[0]);

    fdSrc = open(argv[1], O_RDONLY);
    if (fdSrc == -1)
        errExit("open");

    if (fstat(fdSrc, &sb) == -1)
        errExit("fstat");

    if (sb.st_size == 0)
        exit(EXIT_SUCCESS);

    src = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fdSrc, 0);
    if (src == MAP_FAILED)
        errExit("mmap");

    fdDst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fdDst == -1)
        errExit("open");

    if (ftruncate(fdDst, sb.st_size) == -1)
        errExit("ftruncate");

    dst = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdDst, 0);
    if (dst == MAP_FAILED)
        errExit("mmap");

    memcpy(dst, src, sb.st_size);
    if (msync(dst, sb.st_size, MS_SYNC) == -1)
        errExit("msync");

    exit(EXIT_SUCCESS);
}




