include ../Makefile.inc

GEN_EXE = simple_thread detached_attrib thread_incr thread_incr_mutex\
		  thread_multijoin prod_condvar prod_no_condvar one_time_init

EXE = ${GEN_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

CFLAGS = ${IMPL_CFLAGS} ${IMPL_THREAD_FLAGS}
LDLIBS = ${IMPL_LDLIBS} ${IMPL_THREAD_FLAGS}

clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${LPLIB}		# True as a rough approximation

