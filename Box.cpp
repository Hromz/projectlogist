#include "Box.h"

Box::Box() : width(width), length(length), height(height)
{

}

Box::Box(Box* box) : width(this->width), length(this->length), height(this->height), quantity(this->quantity)
{

}

void Box::turnLeftSide()
{
	double temp;
	temp = width;
	width = length;
	length = temp;
}

void Box::turnUpDownSide()
{
	double temp;
	temp = height;
	height = length;
	length = temp;
	
}

void Box::turnUpSide()
{
	double temp;
	temp = height;
	height = width;
	width = temp;
}

void Box::optimumLoading(double carLength, double carWidth, double carDepth)
{
	int loadSide = optimumLoadingSide(carLength, carWidth, carDepth);
	int temp;

	if (loadSide == 1)
	{
		temp = tryLenght(carLength);
		if (temp == 2)
			turnLeftSide();
		else if (temp == 3)
			turnUpDownSide();
	}
	else if (loadSide == 2)
	{
		temp = tryWidth(carWidth);
		if (temp == 1)
			turnLeftSide();
		else if (temp == 3)
			turnUpSide();
	}
	else
	{
		temp = tryHeight(carDepth);
		if (temp == 1)
			turnUpDownSide();
		else if (temp == 2)
			turnUpSide();
	}
}

int Box::tryLenght(double carLength)
{
	if ((carLength / length) >= (carLength / width) && (carLength / length) >= (carLength / height))
		return 1;
	else if ((carLength / width) >= (carLength / length) && (carLength / width) >= (carLength / height))
		return 2;
	else
		return 3;
}

int Box::tryWidth(double carWidth)
{
	if ((carWidth / length) >= (carWidth / width) && (carWidth / length) >= (carWidth / height))
		return 1;
	else if ((carWidth / width) >= (carWidth / length) && (carWidth / width) >= (carWidth / height))
		return 2;
	else
		return 3;
}

int Box::optimumLoadingSide(double carLength, double carWidth, double carHeight)
{
	if (carLength >= carWidth && carLength >= carHeight)
		return 1;
	else if (carWidth >= carLength && carWidth >= carHeight)
		return 2;
	else
	return 3;
}

int Box::tryHeight(double carDepth)
{
	if ((carDepth / length) >= (carDepth / width) && (carDepth / length) >= (carDepth / height))
		return 1;
	else if ((carDepth / width) >= (carDepth / length) && (carDepth / width) >= (carDepth / height))
		return 2;
	else
		return 3;

}

std::istream& operator>>(std::istream& is, Box& b)
{
	try {
		std::cout << "Enter length, width and height of a box: ";
		is >> b.length >> b.width >> b.height;
		if (!is)
			throw(2);
	}
	catch (...)
	{
		ClearInput(is);
		std::cout << '\a';
		std::cout << "Incorrect input!" << std::endl;
		std::cout << "Please enter again! ";
		std::cout << "Enter length, width and height of a box: ";
		is >> b.length >> b.width >> b.height;
	}
	ClearInput(is);

	try {
		std::cout << "Enter quantity of boxes: ";
		is >> b.quantity;
		if (!is)
			throw(2);
	}
	catch (...)
	{
		ClearInput(is);
		std::cout << '\a';
		std::cout << "Incorrect input!" << std::endl;
		std::cout << "Please enter again! ";
		std::cout << "Enter quantity of boxes: ";
		is >> b.quantity;
	}
	ClearInput(is);

	return is;
}