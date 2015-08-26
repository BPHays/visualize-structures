// abstract class for data structures

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <cairomm/context.h>

class Structure {
	// methods
	public:
		// draw the structure
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr)=0;
		//virtual void draw()=0;

	// member variables
	public:
		// used for all drawing operations
		Cairo::RefPtr<Cairo::Context> cr;
		int x;
		int y;
		int sWidth = 500;
		int sHeight = 500;
};

#endif // STRUCTURE_H
