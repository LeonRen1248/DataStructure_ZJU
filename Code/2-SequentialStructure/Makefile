
CC = g++
CFLAGS = -std=c++11

all: list_tester.out
	./list_tester.out

test_list: list_tester.out
	./list_tester.out

list_tester.out: SequentialList.h SequentialListTest.cpp
	$(CC) $(CFLAGS) -o list_tester.out SequentialListTest.cpp

clean:
	rm -rf *.o *.out list_test
