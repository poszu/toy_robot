OBJS =  main.o robot.o
CFLAGS = -Wall -g
CPP = g++

MAIN_TARGET = toy_robot
%.o: %.cpp
	$(CPP) ${CFLAGS} -c $< -o $@

${MAIN_TARGET}: ${OBJS}
	${CPP} ${CFLAGS} -o $@ ${OBJS}

clean:
	-rm -f *.o ${MAIN_TARGET}
