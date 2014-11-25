#ifndef __SFUNCTIONS_H__
#define __SFUNCTIONS_H__

#include <signal.h>
#include "tlpi_hdr.h"

int printSigMask(FILE *of, const char *msg);

int printPendingSigs(FILE *of, const char *msg);

void printSigset(FILE *of, const char *ldr, const sigset_t *mask);

#endif

