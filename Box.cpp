#include "Box.h"

Box::Box()
{ }

Box::Box(const Box & box) : width(box.width), length(box.length), height(box.height), quantity(box.quantity) { }

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

int Box::tryLenght(double loadingLength)
{
	if ((loadingLength / length) >= (loadingLength / width) && (loadingLength / length) >= (loadingLength / height))
		return 1;
	else if ((loadingLength / width) >= (loadingLength / length) && (loadingLength / width) >= (loadingLength / height))
		return 2;
	else
		return 3;
}

int Box::tryWidth(double loadingWidth)
{
	if ((loadingWidth / length) >= (loadingWidth / width) && (loadingWidth / length) >= (loadingWidth / height))
		return 1;
	else if ((loadingWidth / width) >= (loadingWidth / length) && (loadingWidth / width) >= (loadingWidth / height))
		return 2;
	else
		return 3;
}

int Box::optimumLoadingSide(double loadingLength, double loadingWidth, double loadingHeight)
{
	if (loadingLength >= loadingWidth && loadingLength >= loadingHeight)
		return 1;
	else if (loadingWidth >= loadingLength && loadingWidth >= loadingHeight)
		return 2;
	else
	return 3;
}

int Box::tryHeight(double loadingDepth)
{
	if ((loadingDepth / length) >= (loadingDepth / width) && (loadingDepth / length) >= (loadingDepth / height))
		return 1;
	else if ((loadingDepth / width) >= (loadingDepth / length) && (loadingDepth / width) >= (loadingDepth / height))
		return 2;
	else
		return 3;

}

std::istream& operator>>(std::istream& is, Box& b)
{
	try {
		std::cout << "Enter length, width and height of a box in meters!: ";
		is >> b.length >> b.width >> b.height;
		if (!is)
			throw(std::runtime_error("Input error"));
	}
	catch (...)
	{
		clearInput(is);
		std::cout << '\a';
		std::cout << "Incorrect input!" << std::endl;
		std::cout << "Please enter again! ";
		std::cout << "Enter length, width and height of a box in meters!: ";
		try {
			is >> b.length >> b.width >> b.height;
			if (!is)
				throw(std::runtime_error("Input error"));
		}
		catch (...)
		{
			std::cout << "Input is incorrect again! Terminating program";
			exit(EXIT_FAILURE);
		}

	}
	EatLine();

	try {
		std::cout << "Enter quantity of boxes: ";
		is >> b.quantity;
		if (!is || b.quantity <= 0)
			throw(std::runtime_error("Input error"));
	}
	catch (...)
	{
		clearInput(is);
		std::cout << '\a';
		std::cout << "Incorrect input!" << std::endl;
		std::cout << "Please enter again! ";
		std::cout << "Enter quantity of boxes: ";
		try {
			is >> b.quantity;
			if (!is || b.quantity <= 0)
				throw(std::runtime_error("Input error"));
		}
		catch(...)
		{
			std::cout << "Input is incorrect again! Terminating program";
			exit(EXIT_FAILURE);
		}

	}
	EatLine();
	return is;
}


int Box::getLoadingQuantity(double loadingLength, double loadingWidth, double loadingHeight)
{
	int loadByLength, loadByWidth, loadByDepth;
	optimumLoading(loadingLength, loadingWidth, loadingHeight);

	loadByLength = MakeInt(loadingLength / length);
	loadByWidth = MakeInt(loadingWidth / width);
	loadByDepth = MakeInt(loadingHeight / height);

	double totalPallet = (getQuantity() / (loadByDepth * loadByLength * loadByWidth) + 0.5);

	return MakeInt(totalPallet);
}