#ifndef CUBE_H_
#define CUBE_H_

#include <iostream>
#include <memory>
template<class T>
class CubeSide
{
private:
	T length;
	T width;
	T height;
public:
	CubeSide() {};
	CubeSide(T x, T y, T z) : length(x), width(y), height(z) {};
	~CubeSide() {};

	void setSide(T x, T y, T z);
	void printCubeSide();
	bool currentCubeSide();

	CubeSide<T> operator-(const CubeSide& side);
	CubeSide<T> operator+(const CubeSide& side);
	CubeSide<T> operator-=(const CubeSide& side);
	CubeSide<T> operator+=(const CubeSide& side);
	CubeSide<T> operator>(const CubeSide& side);
	CubeSide<T> operator<(const CubeSide& side);
	CubeSide<T> operator*=(int x);
};


template<class T>
class Cube : public CubeSide<T>
{
private:
	CubeSide<T> TopLeft;
	CubeSide<T> BottomLeft;
	CubeSide<T> TopRight;
	CubeSide<T> BottomRight;

public:
	Cube() {};
	Cube(T x, T y, T z);
	~Cube() 
	{
		//delete TopLeft; delete TopRight; delete BottomLeft; delete BottomRight;
	}
	void setCube(T x, T y, T z);
	bool currentCube();

	Cube<T> operator-(const Cube& cube);
	Cube<T> operator+(const Cube& cube);
	Cube<T> operator-=(const Cube& cube);
	Cube<T> operator+=(const Cube& cube);
	Cube<T> operator*=(int x);

	bool operator>(const Cube& cube);
	bool operator<(const Cube& cube);
	bool isEmpty();

	void showCube();
	void printSide(int i);

};
#endif
