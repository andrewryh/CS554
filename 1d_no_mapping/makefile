EXECS=1dlaplacempi
MPICC?=mpicc

all: ${EXECS}

mpi_hello_world: 1dlaplacempi.cpp
	${MPICC} -o 1dlaplacempi 1dlaplacempi.cpp

clean:
	rm -f ${EXECS}
