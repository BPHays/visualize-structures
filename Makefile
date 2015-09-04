GXX = g++ -g -std=c++11

all: visualize

visualize: visualize.o main.o graph.o list.o dlist.o array.o tree.o rbtree.o heap.o stack.o queue.o
	$(GXX) -o visualize visualize.o main.o node.o graph.o list.o dlist.o  tree.o rbtree.o array.o stack.o queue.o heap.o `pkg-config --cflags --libs gtkmm-3.0` -pthread

visualize.o: visualize.cpp visualize.h
	$(GXX) -c visualize.cpp `pkg-config --cflags --libs gtkmm-3.0`

main.o: main.cpp
	$(GXX) -c main.cpp `pkg-config --cflags --libs gtkmm-3.0` -pthread

node.o: node.cpp node.h
	$(GXX) -c node.cpp `pkg-config --cflags --libs gtkmm-3.0`

graph.o: graph.cpp graph.h node.o
	$(GXX) -c graph.cpp `pkg-config --cflags --libs gtkmm-3.0`

list.o: list.cpp list.h graph.o
	$(GXX) -c list.cpp `pkg-config --cflags --libs gtkmm-3.0`

dlist.o: dlist.cpp dlist.h list.o
	$(GXX) -c dlist.cpp `pkg-config --cflags --libs gtkmm-3.0`

tree.o: tree.cpp tree.h graph.o
	$(GXX) -c tree.cpp `pkg-config --cflags --libs gtkmm-3.0` -lm

rbtree.o: rbtree.cpp rbtree.h tree.o
	$(GXX) -c rbtree.cpp `pkg-config --cflags --libs gtkmm-3.0`

array.o: array.cpp array.h
	$(GXX) -c array.cpp `pkg-config --cflags --libs gtkmm-3.0`

stack.o: stack.cpp stack.h array.o
	$(GXX) -c stack.cpp `pkg-config --cflags --libs gtkmm-3.0`

queue.o: queue.cpp queue.h array.o
	$(GXX) -c queue.cpp `pkg-config --cflags --libs gtkmm-3.0`

heap.o: heap.cpp heap.h array.o
	$(GXX) -c heap.cpp `pkg-config --cflags --libs gtkmm-3.0`

clean:
	rm *.o visualize
