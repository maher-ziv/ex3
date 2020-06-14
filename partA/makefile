CC = g++
OBJS = Intmatrix.o Auxiliaries.o
EXEC = partA
DEBUG_FLAG = -g
COMP_FLAG = -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG

$(EXEC):$(OBJS)
	$(CC) -std=c++11 $(DEBUG_FLAG) $(OBJS) -o $@  

Intmatrix.o: IntMatrix.cpp IntMatrix.h Auxiliaries.h
	$(CC) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.cpp
Auxiliaries.o: Auxiliaries.cpp Auxiliaries.h 
	$(CC) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)