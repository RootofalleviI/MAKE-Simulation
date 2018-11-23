CXX=g++

CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror -MMD -g

OBJECTS=target.o makefile.o main.o

DEPENDS=${OBJECTS:.o=.d}

EXEC=MAKE

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

.PHONY: clean

