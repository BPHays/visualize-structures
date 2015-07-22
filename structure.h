// abstract class for data structures

#ifndef STRUCTURE_H
#define STRUCTURE_H

class Structure {
	public:
		virtual void draw(const Cairo::RefPtr<Cairo::Context> & cr)=0;
};

#endif // STRUCTURE_H
