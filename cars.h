#include <iostream>
#ifndef LAZY_LOGISTICIAN_CARS_H
#define LAZY_LOGISTICIAN_CARS_H

class BaseCar
{
protected:
	double length = 0;
	double width = 0;
	double area = 0;
	double height = 0;
	int carQuantity = 0;
	std::string name = "BaseCar";
public:

	inline BaseCar(double length, double width, double height, std::string name)
		: length(length), width(width), area(length* width), height(height), name(name)
	{
	}
	inline ~BaseCar() {}

	inline bool checkLength(double totalLength) const{ return this->length <= totalLength; }
	inline double getLength() const { return this->length; }
	inline double getWidth() const { return this->width; }
	inline double getHeight() const { return this->height; }
	inline bool isOrdered() { return this->carQuantity > 0;}
	inline void orderCar() { carQuantity++;}
	inline int quantityCar() const{ return this->carQuantity; }
	inline std::string getCarName() const { return this->name; }
	inline void print() const { std::cout << "Size of " << name << std::endl; std::cout << length << " " << width << " " << height << std::endl; }

	virtual BaseCar * duplicate() = 0;
	virtual bool isApplicaple(int palletQuantity) = 0; //Check if this quantity pallets can be loaded in car
	virtual int getLoadWidth(double palletWidth) = 0; 
};

class PorterCar : public BaseCar
{
protected:

public:
	PorterCar();
	bool isApplicaple(int quantity);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};

class GazelCar : public BaseCar
{
protected:

public:
	GazelCar();
	bool isApplicaple(int q);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};

class MersedesCar : public BaseCar
{
protected:
public:
	MersedesCar();
	bool isApplicaple(int palletQuantity);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};

class FiveTonCar : public BaseCar
{
protected:

public:
	FiveTonCar();
	bool isApplicaple(int palletQuantity);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};

class TenTonCar : public BaseCar
{
protected:

public:
	TenTonCar();
	bool isApplicaple(int palletQuantity);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};

class EuroTrackCar : public BaseCar
{
protected:

public:
	EuroTrackCar();
	bool isApplicaple(int palletQuantity);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};
#endif