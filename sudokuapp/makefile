CC = g++
CFLAGS = -ansi

all: testCell testGen

testCell: testCell.o cell.o
	$(CC) -o testCell testCell.o cell.o
testGen: testGenerator.o generator.o
	$(CC) -o testGen testGenerator.o generator.o

testCell.o: cell.h

testGen.o: generator.o

cell.o: cell.h

generator.o: generator.h

clean:
	rm -f *.o

real_clean: clean
	rm -f testCell
