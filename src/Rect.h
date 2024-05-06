#ifndef RECT_H
#define RECT_H

struct Rect
{
	int x;
	int y;
	int w;
	int h;
	
	bool contains(int x_, int y_)
	{
		return x <= x_ && x_ < (x + w)
			&& y <= y_ && y_ < (y + h);
	}
};


#endif 

