CFLAGS=-std=c++14 -Wall -O2

build: hardstuck

hardstuck: main.cpp state.o appear.o moves.o search.o
	g++ $^ -o $@ $(CFLAGS)

moves.o: moves.cpp
	g++ $^ -c -o $@ $(CFLAGS)

appear.o: appear.cpp
	g++ $^ -c -o $@ $(CFLAGS)

state.o: state.cpp
	g++ $^ -c -o $@ $(CFLAGS)

search.o: search.cpp
	g++ $^ -c -o $@ $(CFLAGS)

run:
	./hardstuck

test: hardstuck
	xboard -debug -fcp ./hardstuck 

clean:
	rm hardstuck *.o	
	rm *.txt
	rm xboard.debug
