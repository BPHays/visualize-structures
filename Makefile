all: visualize

visualize: visualize.cpp visualize.h main.cpp
	g++ -o visualize visualize.cpp main.cpp `pkg-config --cflags --libs gtkmm-3.0`

clean:
	rm *.o visualize
