OBJS =  test.o ../robot.o ../simulation.o
CFLAGS = -Wall -g
CPP = g++

MAIN_TARGET = ut
%.o: %.cpp
	$(CPP) ${CFLAGS} -c $< -o $@

${MAIN_TARGET}: ${OBJS}
	${CPP} ${CFLAGS} -o $@ ${OBJS}

clean:
	-rm -f *.o ${MAIN_TARGET}

run:
	./${MAIN_TARGET}
