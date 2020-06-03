#ifndef CUBE_H_
#define CUBE_H_

#include <iostream>

template<class T>
class CubeSide
{
private:
	T length;
	T width;
	T height;
public:
	CubeSide() {}
	CubeSide(T x, T y, T z) : length(x), width(y), height(z)
	{}
	~CubeSide() {}

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
	CubeSide<T>* TopLeft = new CubeSide<T>;
	CubeSide<T>* BottomLeft = new CubeSide<T>;
	CubeSide<T>* TopRight = new CubeSide<T>;
	CubeSide<T>* BottomRight = new CubeSide<T>;
public:
	Cube() {}
	Cube(T x, T y, T z);
	~Cube() {}
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
