#ifndef RECTANGLE_H_DEFINED
#define RECTANGLE_H_DEFINED

struct Rectangle
{
	int x{};
	int y{};
	int w{};
	int h{};

	Rectangle();
	Rectangle(const Rectangle& rhs);
	Rectangle(int x, int y, int w, int h);

	void SetBounds(int x, int y, int w, int h);
};
#endif
