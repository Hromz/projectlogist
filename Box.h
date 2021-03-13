#ifndef BOX_H
#define BOX_H
#include <iostream>
#include "Routines.h"

class Box
{
private:
	double length;
	double width;
	double height;
	int quantity;
public:
	Box();
	Box(const Box & box);
	~Box() {}
	void turnLeftSide(); //turn over box swaps width to length side
	void turnUpSide(); //turn over box swaps height to width
	void turnUpDownSide(); //turn over box swaps length to height

	//turn over box for optimal loading into a car
	void optimumLoading(double loadingLength, double loadingWidth, double loadingDepth); 
	int tryLenght(double loadingLength); //check which box side is better to load in by length, returns box dimension code (i.e. 1 - box length, 2 - box width, 3 - box height)
	int tryWidth(double loadingWidth);//check which box side is better to load in by width, returns box dimension code (i.e. 1 - box length, 2 - box width, 3 - box height)
	int tryHeight(double loadingDepth); //check which box side is better to load in by height, returns box dimension code (i.e. 1 - box length, 2 - box width, 3 - box height)
	int optimumLoadingSide(double loadingLength, double loadingWidth, double loadingHeight); //compare and return most longer car side
	int getLoadingQuantity(double loadingLength, double LoadingWidth, double LoadingHeight);

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