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

	 BaseCar(double length, double width, double height, std::string name)
		: length(length), width(width), area(length* width), height(height), name(name) { }
	 BaseCar(const BaseCar& car) : length(car.length), width(car.width), area(car.length * car.width), height(car.height), name(car.name) {}
	 ~BaseCar() {}


	double getLength() const { return this->length; }
	double getWidth() const { return this->width; }
	double getHeight() const { return this->height; }
	double getCarCube() const { return this->length * this->width * this->height; }

	bool checkLength(double totalLength) const { return this->length <= totalLength; }
	bool isOrdered() { return this->carQuantity > 0;}

	void orderCar() { carQuantity++; }
	void print() const { std::cout << "Size of " << name << std::endl; std::cout << length << " " << width << " " << height << std::endl; }

	int quantityCar() const{ return this->carQuantity; }
	std::string getCarName() const { return this->name; }


	virtual BaseCar * duplicate() = 0;
	virtual bool isApplicaple(int palletQuantity) = 0; //Checks if this quantity pallets can be loaded in car
	virtual int getLoadWidth(double palletWidth) = 0; 
};

class PorterCar : public BaseCar
{
protected:

public:
	PorterCar();
	PorterCar(const PorterCar & car) : BaseCar(car) {}
	bool isApplicaple(int quantity);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};

class GazelCar : public BaseCar
{
protected:

public:
	GazelCar();
	GazelCar(const GazelCar & car) : BaseCar(car) {}
	bool isApplicaple(int q);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};

class MersedesCar : public BaseCar
{
protected:
public:
	MersedesCar();
	MersedesCar(const MersedesCar & car) : BaseCar(car) {}
	bool isApplicaple(int palletQuantity);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};

class FiveTonCar : public BaseCar
{
protected:

public:
	FiveTonCar();
	FiveTonCar(const FiveTonCar & car) : BaseCar(car) {}
	bool isApplicaple(int palletQuantity);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};

class TenTonCar : public BaseCar
{
protected:

public:
	TenTonCar();
	TenTonCar(const TenTonCar & car) : BaseCar(car) {}
	bool isApplicaple(int palletQuantity);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};

class EuroTrackCar : public BaseCar
{
protected:

public:
	EuroTrackCar();
	EuroTrackCar(const EuroTrackCar & car) : BaseCar(car) {}
	bool isApplicaple(int palletQuantity);
	BaseCar* duplicate();
	int getLoadWidth(double palletWidth);
};
#endif