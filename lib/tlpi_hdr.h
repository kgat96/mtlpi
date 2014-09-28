#ifndef __TLPI_HDR_H__
#define __TLPI_HDR_H__

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "get_num.h"

#include "error_functions.h"

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALES
#undef FALES
#endif

typedef enum {FALSE, TRUE} bool;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif

