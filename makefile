EXECS=1dlaplacempi
MPICC?=mpicxx

all: ${EXECS}

1dlaplacempi: 1dlaplacempi.cpp
	${MPICC} -o 1dlaplacempi 1dlaplacempi.cpp

clean:
	rm -f ${EXECS}
