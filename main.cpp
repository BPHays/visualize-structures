#include "visualize.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>
#include <thread>
#include <iostream>
#include <gtkmm/adjustment.h>

void start(Visualize * v, const char * arg) {
	v->run(arg);
	std::cout << "exiting" << std::endl;
	return;
}

int main(int argc, char ** argv) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "test");

	Gtk::Window win;
	win.set_title("Visualize");

	Gtk::ScrolledWindow scroll;
	scroll.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);

	Visualize v;
	scroll.add(v);
	win.add(scroll);
	win.show_all_children();

	std::thread t1(start, &v, argv[1]);
	int res = app->run(win);
	t1.join();

	return res;
}
