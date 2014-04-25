CC=g++

INCLUDE =. 

CFLAGS =-g -Wall

OO = main.o invtree.o rectoverlap.o

HH = invtree.hpp rectoverlap.hpp

rec: main.o $(OO)   

	$(CC) $(OO) -o rec

main.o: main.cpp $(HH)  

	$(CC) -c -g -Wall main.cpp

invtree.o: invtree.cpp  $(HH)

	$(CC) -c -g -Wall invtree.cpp

rectoverlap.o: rectoverlap.cpp  $(HH)

	$(CC) -c -g -Wall rectoverlap.cpp