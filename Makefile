GXX = g++ -g -std=c++11

all: visualize

visualize: visualize.o main.o graph.o list.o dlist.o array.o tree.o
	$(GXX) -o visualize visualize.o main.o graph.o list.o dlist.o  tree.o array.o `pkg-config --cflags --libs gtkmm-3.0` -pthread

visualize.o: visualize.cpp visualize.h
	$(GXX) -c visualize.cpp `pkg-config --cflags --libs gtkmm-3.0`

main.o: main.cpp
	$(GXX) -c main.cpp `pkg-config --cflags --libs gtkmm-3.0` -pthread

graph.o: graph.cpp graph.h
	$(GXX) -c graph.cpp `pkg-config --cflags --libs gtkmm-3.0`

list.o: list.cpp list.h graph.o
	$(GXX) -c list.cpp `pkg-config --cflags --libs gtkmm-3.0`

dlist.o: dlist.cpp dlist.h list.o
	$(GXX) -c dlist.cpp `pkg-config --cflags --libs gtkmm-3.0`

tree.o: tree.cpp tree.h graph.o
	$(GXX) -c tree.cpp `pkg-config --cflags --libs gtkmm-3.0` -lm

array.o: array.cpp array.h
	$(GXX) -c array.cpp `pkg-config --cflags --libs gtkmm-3.0`

clean:
	rm *.o visualize
