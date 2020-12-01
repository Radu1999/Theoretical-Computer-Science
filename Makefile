CC = g++
CFLAGS = -Wall -Wextra -O2
LDLIBS = -lm

build: algo1_test.o algo2_test.o

algo1.o: algo1.cpp
	g++ algo1.cpp algo1.h -c $(CFLAGS)

algo2.o: algo2.cpp
	 g++ algo2.cpp -c $(CFLAGS)

algo1_test.o: algo1_test.cpp algo1.o
	g++ algo1_test.cpp -o test1 $(CFLAGS)

algo2_test.o: algo2_test.cpp algo2.o
	g++ algo2.o algo2_test.cpp -o test2 $(CFLAGS)



.PHONY: clean
clean:
	rm -rf *.o test1 test2
