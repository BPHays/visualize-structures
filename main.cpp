#include "visualize.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char ** argv) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "test");

	Gtk::Window win;
	win.set_title("Visualize");

	Visualize v;
	win.add(v);
	v.show();

	return app->run(win);
}
