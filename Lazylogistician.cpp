#include "Lazylogistician.h"

Car::Car(double l, double w, double m, double h)
{
	carCube = m;
	length = l;
	width = w;
	height = h;
}

Car::Car(const Car& c)
{
	carCube = c.carCube;
	length = c.length;
	width = c.width;
	height = c.height;
}

//Return area of car, !cubeMetr = square meters!
void Car::setCubeM()
{
	this->carCube = (length * width * height);
}

//Return true or false if pallets can be loaded in width and detects which size
//i.e width = 0,8m euro standart, width = 1.2 USA standart
bool Car::loadWidth(double palletWidth)
{
	if ((palletWidth * 2) <= width)
		return true;
	else
		return false;
}

//Function identifies how many pallets can be loaded in width
//For example EU standart is 0,8 width, so it means 3 pallets(in width) will be loaded as 1 row
//USA standart is 1 or 2 therefore 2 pallets by width will be loaded as 1 row
void Car::setWidthArea(double palletWidth)
{
	if ((palletWidth * 2) > 1.20)
		widthPalletRow = 3;
	else if ((palletWidth * 2) <= 1.20)
		widthPalletRow = 2;
	else
		widthPalletRow = 2;
}

//returns how many rows of pallet will be according to pallet row
//check void Car::setWidthArea() for future implementation
void Car::setPalletLengthRow(int palletQuantity)
{
	lengthPalletRow = (palletQuantity / (double)widthPalletRow);
}

//return total pallet length by car side
void Car::setOccupiedPalletLength(double palletLength)
{
	occupiedPalletLength = lengthPalletRow * palletLength;
}

//checks if car has enough size for an order
//comprares order length of SloadQ and car length
bool Car::multiMachLoad()
{
	if (occupiedPalletLength <= getLength())
		return true;
	else
		return false;
}

//input operator for length, width, height
//has error cathces in case bad input for a user
std::istream& operator>>(std::istream& is, Car& s)
{
	try
	{ 
	std::cout << "Enter length of car in meters: ";
	is >> s.length;
	if (!is)
		throw(1);
	}
	catch (...)
	{
		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << '\a'; 
		std::cout << "Please enter length of car again: ";
		is >> s.length;
	}
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	try
	{ 
	std::cout << "Enter width of car in meters: ";
	is >> s.width;
	if (!is)
		throw(1);
	}
	catch (...)
	{
		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << '\a'; 
		std::cout << "Please enter width of car again: ";
		is >> s.width;
	}
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	try 
	{
	std::cout << "Enter height of car in meter: ";
	is >> s.height;
	if (!is)
		throw(1);
	}
	catch (...)
	{
		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << '\a';
		std::cout << "Please enter height of car again: ";
		is >> s.height;
	}
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return is;
}

//output operator for length, width, height
std::ostream& operator<<(std::ostream& os, const Car& s)
{
	os << "Length of car is " << s.length << "\t" << " Width of car is " << s.width << "\n";
	os << "Hieght of car is " << s.height << std::endl;
	os << "CubeMeters of car is " << s.length * s.width * s.height << "\n";
	return os;
}

//pallet constructor passing by value
Pallet::Pallet(double l, double w, double c, double h, int q)
{
	p_length = l;
	p_width = w;
	p_height = h;
	p_cubeMetr = c;
	quanity = q;
}

//pallet constructor
Pallet::Pallet(const Pallet& p)
{
	p_length = p.p_length;
	p_width = p.p_width;
	p_cubeMetr = p.p_cubeMetr;
	p_height = p.p_height;
	quanity = p.quanity;
}

//set cubic meters of pallet
void Pallet::setCubeMetr()
{
	p_cubeMetr = p_length * p_width * p_height;
}


//input operator for pallet
//has error cathces in case bad input for a user
std::istream& operator>>(std::istream& is, Pallet& s)
{
	try
	{
		std::cout << "Enter length of pallet in meters: ";
		is >> s.p_length;

		if (!is)
			throw 1;
	}
	catch (...)
	{
		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << '\a'; //in case of Breakfast!
		std::cout << "Please enter length of pallet again: ";
		is >> s.p_length;
	}
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	try
	{
		std::cout << "Enter width of pallet in meters: ";
		is >> s.p_width;

		if (!is)
			throw 2;
	}
	catch (...)
	{
		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << '\a'; //in case of Breakfast!
		std::cout << "Please enter width of pallet again: ";
		is >> s.p_width;
	}
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	try
	{
		std::cout << "Enter height of pallet in meters: ";
		is >> s.p_height;

		if (!is)
			throw 2;
	}
	catch (...)
	{
		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << '\a'; //in case of Breakfast!
		std::cout << "Please enter height of pallet again: ";
		is >> s.p_height;
	}
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	try
	{
		std::cout << "Enter how many pallet(s) do you wish to load: ";
		is >> s.quanity;

		if (!is)
			throw 3;
	}
	catch (...)
	{
		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << '\a'; //in case of Breakfast!
		std::cout << "Please enter numbers of pallet again: ";
		is >> s.quanity;
	}
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return is;
}

//output operator for pallet class
std::ostream& operator<<(std::ostream& os, const Pallet& s)
{
	os << "The length of pallet is " << s.p_length << "\n";
	os << "The width of pallet is " << s.p_width << "\n";
	os << "The height of pallet is " << s.p_height << "\n";
	os << "The quanity of pallet is " << s.quanity << "\n";
	os << "The cube metr of pallets is " << s.p_length * s.p_width * s.quanity << "\n";

	return os;
}