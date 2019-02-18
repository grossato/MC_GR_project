CXX = g++
CFLAGS = -std=c++11 -Wall -Wextra 
IFLAGS = -I include
#DFLAGS = -D debug

all: main_tree time_test/time_test $(EXE_TEST)

src/tree.o:  src/tree.cpp 
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS)

time_test/time_test: time_test/time_test.o src/tree.o 
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)

time_test/time_test.o: time_test/time_test.cpp 
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS)

main_tree: main_tree.o src/tree.o 
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS) $(DFLAGS)

main_tree.o: main_tree.cpp 
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS) $(DFLAGS)





#main_tree.o: src/tree.o

#src/tree.o: include/tree.h

#time_tree.o: src/tree.o

doc: Doxygen/Doxy
	doxygen $^

clean:
	@rm -rf *~ *.o src/*.o test/*.o html latex main_tree test/test_time

.PHONY: clean