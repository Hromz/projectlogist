#ifndef BOX_H
#define BOX_H
#include <iostream>
#include "Routines.cpp"

class Box
{
private:
	double length;
	double width;
	double height;
	int quantity;
public:
	Box();
	Box(Box* box);
	~Box() {}
	void turnLeftSide(); //turn over box swaps width to length side
	void turnUpSide(); //turn over box swaps height to width
	void turnUpDownSide(); //turn over box swaps length to height

	void optimumLoading(double carLength, double carWidth, double carDepth);
	int tryLenght(double carLength); //check which box side is better to load on car length and returns box dimension code (i.e. 1 - box length, 2 - box width, 3 - box height)
	int tryWidth(double carWidth);//check which box side is better to load on car width and returns box dimension code (i.e. 1 - box length, 2 - box width, 3 - box height)
	int tryHeight(double carDepth); //check which box side is better to load on car height and returns box dimension code (i.e. 1 - box length, 2 - box width, 3 - box height)
	int optimumLoadingSide(double carLength, double carWidth, double carHeight); //compare and return most longer car side

	inline double getLength() { return this->length;}
	inline double getWidth() { return this->width;}
	inline double getHeight() { return this->height; }
	inline double getCube() { double temp = height * width * length * quantity; roundNum(temp);  return temp; } //return total boxes cube
	inline int getQuantity() { return this->quantity; }

	inline void setLength(double length) { this->length = length; }
	inline void setWidth(double width) { this->width = width; }
	inline void setHeight(double height) { this->height = height; }
	inline void setQuantity(int quantity) { this->quantity = quantity; }

	friend std::istream& operator>>(std::istream& is, Box& b);
};
#endif