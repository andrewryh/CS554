EXECS=laplacempi
MPICC?=mpicc

all: ${EXECS}

mpi_hello_world: laplacempi.cpp
	${MPICC} -o laplacempi laplacempi.cpp

clean:
	rm -f ${EXECS}
