#ifndef ROUTINES_H
#define ROUTINES_H
#include <iostream>
#include <limits>
#undef max

//Changes double to float value
inline float MakeFloat(double x)
{
	return static_cast<float>(x);
}

//Changes double to int value
inline int MakeInt(double x)
{
	return static_cast<int>(x);
}

//Clearing bad input from user
//i.e. >> 1,aksfjsajdi12
//Input buffer will get 1
inline void EatLine()
{
	using std::cin;
	cin.clear();
	cin.ignore(100, '\n');
}

inline void clearInput(std::istream & is)
{
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Round double value
inline void roundNum(double & x)
{
	x = (int)(x * 10000.0) / 10000.0;
}


//Transform negative avalue to positive

inline void makePositive(double & x)
{
	using std::cout;
	using std::endl;

	cout << "Value cannot be negative, changing it to positive!" << endl;
	x = abs(x);
}

inline void makePositive(int & x)
{
	using std::cout;
	using std::endl;

	cout << "Value cannot be negative, changing it to positive!" << endl;
	x = abs(x);
}

#endif