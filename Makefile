all: visualize

visualize: visualize.o main.o list.o dlist.o array.o
	g++ -g -o visualize visualize.o main.o list.o dlist.o array.o `pkg-config --cflags --libs gtkmm-3.0` -pthread -std=c++11

visualize.o: visualize.cpp visualize.h
	g++ -g -c visualize.cpp `pkg-config --cflags --libs gtkmm-3.0`

main.o: main.cpp
	g++ -g -c main.cpp `pkg-config --cflags --libs gtkmm-3.0` -pthread -std=c++11

list.o: list.cpp list.h
	g++ -g -c list.cpp `pkg-config --cflags --libs gtkmm-3.0`

dlist.o: dlist.cpp dlist.h list.o
	g++ -g -c dlist.cpp `pkg-config --cflags --libs gtkmm-3.0`

array.o: array.cpp array.h
	g++ -g -c array.cpp `pkg-config --cflags --libs gtkmm-3.0`

clean:
	rm *.o visualize
