#ifndef ROUTINES_H
#define ROUTINES_H
#include <iostream>

//Changes double to float value
inline float MakeFloat(double x)
{
	float a;
	return  (a = static_cast<float>(x));
}

//Changes double to int value
inline int MakeInt(double x)
{
	int a;
	return  (a = static_cast<double>(x));
}

//Clearing bad input from user
//i.e. >> 1,aksfjsajdi12
//Input buffer will get 1
inline void EatLine()
{
	using std::cin;
	cin.clear();
	cin.ignore(255, '\n');
}

inline void ClearInput(std::istream & is)
{
	is.clear();
	std::cin.ignore();
}

//Round double value
inline void roundNum(double & x)
{
	x = (int)(x * 10000.0) / 10000.0;
}

#endif