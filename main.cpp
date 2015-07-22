#include "visualize.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <thread>
#include <iostream>

void start(Visualize * v) {
	v->run();
	std::cout << "exiting" << std::endl;
	return;
}

int main(int argc, char ** argv) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "test");

	Gtk::Window win;
	win.set_title("Visualize");

	Visualize v;
	win.add(v);
	v.show();

	std::thread t1(start, &v);
	int res = app->run(win);
	t1.join();

	return res;
}
