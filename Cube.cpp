#include "Cube.h"

template <typename T>
void Cube<T>::setCube(T x, T y, T z)
{
	TopLeft.setSide(x, y, z);
	BottomLeft.setSide(x, y, z);
	TopRight.setSide(x, y, z);
	BottomRight.setSide(x, y, z);
}

template <typename T>
Cube<T>::Cube(T x, T y, T z)
{
	TopLeft.setSide(x, y, z);
	BottomLeft.setSide(x, y, z);
	TopRight.setSide(x, y, z);
	BottomRight.setSide(x, y, z);
}

template<class T>
Cube<T> Cube<T>::operator-(const Cube& cube)
{
	Cube<T>* c = new Cube<T>;
	*(c->BottomLeft) = *(this->BottomLeft) - *(cube.BottomLeft);
	*(c->TopRight) = *(this->TopRight) - *(cube.TopRight);
	*(c->BottomRight) = *(this->BottomRight) - *(cube.BottomRight);
	*(c->TopLeft) = *(this->TopLeft) - *(cube.TopLeft);

	return *c;
}

template<class T>
Cube<T> Cube<T>::operator+(const Cube& cube)
{
	Cube<T>* c = new Cube<T>;
	*(c->BottomLeft) = *(this->BottomLeft) + *(cube.BottomLeft);
	*(c->TopRight) = *(this->TopRight) + *(cube.TopRight);
	*(c->BottomRight) = *(this->BottomRight) + *(cube.BottomRight);
	*(c->TopLeft) = *(this->TopLeft) + *(cube.TopLeft);

	return *c;
}

template<class T>
Cube<T> Cube<T>::operator-=(const Cube& cube)
{
	this->BottomLeft -= cube.BottomLeft;
	this->TopRight -= cube.TopRight;
	this->BottomRight -= cube.BottomRight;
	this->TopLeft -= cube.TopLeft;

	return *this;
}

template<class T>
Cube<T> Cube<T>::operator+=(const Cube& cube)
{
	this->BottomLeft += (cube.BottomLeft);
	this->TopRight += (cube.TopRight);
	this->BottomRight += (cube.BottomRight);
	(this->TopLeft) += (cube.TopLeft);

	return *this;
}

template<class T>
bool Cube<T>::operator>(const Cube& cube)
{
	if (this->BottomLeft > cube.BottomLeft && this->BottomRight > cube.BottomRight && this->TopLeft > cube.TopLeft && this->TopRight > cube.TopRight)
		return true;
	else false;
}

template<class T>
bool Cube<T>::operator<(const Cube& cube)
{
	if (this->BottomLeft < cube.BottomLeft && this->BottomRight < cube.BottomRight && this->TopLeft < cube.TopLeft && this->TopRight < cube.TopRight)
		return true;
	else false;
}

template<class T>
Cube<T> Cube<T>::operator*=(int x)
{
	(this->BottomLeft) *= x;
	(this->TopRight) *= x;
	(this->BottomRight) *= x;
	(this->TopLeft) *= x;

	return *this;
}

template<class T>
void Cube<T>::printSide(int i)
{
	if (i == 0)
	{
		std::cout << "TopLeft Side" << std::endl;
		TopLeft->printCubeSide();
	}
	else if (i == 1)
	{
		std::cout << "BottomLeft Side" << std::endl;
		BottomLeft->printCubeSide();
	}
	else if (i == 2)
	{
		std::cout << "TopRight Side" << std::endl;
		TopRight->printCubeSide();
	}
	else if (i == 3)
	{
		std::cout << "TopBottom Side" << std::endl;
		BottomRight->printCubeSide();
	}
}

template<class T>
void Cube<T>::showCube()
{
	for (int i = 0; i < 4; i++)
	{
		printSide(i);
	}

}

template<class T>
bool Cube<T>::isEmpty()
{
	if (!TopLeft.currentCubeSide() && !TopRight.currentCubeSide() && !BottomLeft.currentCubeSide() && !BottomRight.currentCubeSide())
		return true;
	else
		return false;
}

template<class T>
bool Cube<T>::currentCube()
{
	if (TopLeft->currentCubeSide() && BottomLeft->currentCubeSide() && TopRight->currentCubeSide() && BottomRight->currentCubeSide())
		return true;
	else
		return false;
}


template<class T>
CubeSide<T> CubeSide<T>::operator-(const CubeSide& side)
{
	CubeSide<T> s;
	s.length = length - side.length;
	s.width = width - side.width;
	s.height = height - side.height;

	return s;
}

template<class T>
CubeSide<T> CubeSide<T>::operator+(const CubeSide& side)
{
	CubeSide<T> s;
	s.length = length + side.length;
	s.width = width + side.width;
	s.height = height + side.height;

	return s;
}

template<class T>
CubeSide<T> CubeSide<T>::operator-=(const CubeSide& side)
{
	length -= side.length;
	width -= side.width;
	height -= side.height;

	return *this;
}

template<class T>
CubeSide<T> CubeSide<T>::operator+=(const CubeSide& side)
{
	length += side.length;
	width += side.width;
	height += side.height;

	return *this;
}

template<class T>
void CubeSide<T>::setSide(T x, T y, T z)
{
	length = x;
	width = y;
	height = z;
}

template<class T>
CubeSide<T> CubeSide<T>::operator>(const CubeSide& side)
{
	if (length > side.length && width > side.width && height > side.height)
		return true;
	else
		return false;
}

template<class T>
CubeSide<T> CubeSide<T>::operator<(const CubeSide& side)
{
	if (length < side.length && width < side.width && height < side.height)
		return true;
	else
		return false;
}

template<class T>
void CubeSide<T>::printCubeSide()
{
	std::cout << "X side " << length << std::endl;
	std::cout << "Y side " << width << std::endl;
	std::cout << "Z side " << height << std::endl;
}

template<class T>
CubeSide<T> CubeSide<T>::operator*=(int x)
{
	length *= x;
	width *= x;
	height *= x;

	return *this;
}


template<class T>
bool CubeSide<T>::currentCubeSide()
{
	if (length > 0 && width > 0 && height > 0)
		return true;
	else if (length == 0 && width == 0 && height == 0)
		return false;
	else
		return false;
}
