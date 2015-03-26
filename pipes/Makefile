include ../Makefile.inc

GEN_EXE = simple_pipe change_case pipe_sync fifo_seqnum_server fifo_seqnum_client\
           popen_glob

LINUX_EXE =

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean :
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${LPLIB}		# True as a rough approximation

