CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = flood
CONS = -lX11
OBJECTS = main.o cell.o grid.o textdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${CONS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
