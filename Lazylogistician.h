#ifndef LazyLogistician_H
#define LazyLogistician_H

#include <iostream>
#include <string>
#include <vector>
#include "routines.cpp"

class Pallet
{
private:
	double p_length = 0;
	double p_width = 0;
	double p_height = 0;
	double p_cubeMetr = 0;
	int quanity = 0;
public:
	Pallet() { double l = 0; double w = 0; double c = 0; double h = 0; int q = 0; }
	Pallet(double l, double w, double c, double h, int q);
	Pallet(const Pallet& p);
	~Pallet() {};

	void setCubeMetr();

	//Return functions for direct request.
	int getQuanity() { return quanity; }; //returns quanity of pallet
	double getLength() { return p_length; }; //return length of pallet
	double getWidth() { return p_width; }; //return width of pallet
	double getHeight() { return p_height; } //return height of pallet

	double getArea() { return p_width * p_length * quanity; };//area of pallets
	double getLoadedArea(int loadedPallets) { return (p_width * p_length * loadedPallets); }
	double getPalSize() { return p_width * p_length; }; //Area of pallet
	double getWidthSize() { return p_width * 2; }; //Pallet loading in width

	//Input and output operators, to simplify console input
	friend std::istream& operator>>(std::istream& is, Pallet & s); 
	friend std::ostream& operator<<(std::ostream& os, const Pallet& s);
};

class Car 
{
private:
	double carCube = 0;
	double length = 0;
	double width = 0;
	double height = 0;
	int widthPalletRow = 2;
	double lengthPalletRow = 0;
	double occupiedPalletLength = 0; 
public:
	Car() {}
	Car(double l, double w, double m, double h);
	Car(const Car& c);
	~Car() {};

	double getLength() { return this->length; }; 
	double getWidth() { return this->width; }; 
	double getHeight() { return this->height; }
	double getCubeMetr() { return this->carCube; };
	double getLengthPalletRow() { return lengthPalletRow; };
	double getOccupiedPalletLength() { return occupiedPalletLength; };

	//Functions for calculating loading into a car
	void setCubeM();
	void setWidthArea(double palletWidth);
	void setPalletLengthRow(int palletQuantity);
	void setOccupiedPalletLength(double palletLength);
	void changeCubeMetr(double boxCube) { if (carCube >= boxCube) this->carCube -= boxCube; else carCube = -1; }

	bool loadWidth(double palletWidth);
	bool multiMachLoad();

	friend std::istream& operator>>(std::istream& is, Car& s);
	friend std::ostream& operator<<(std::ostream& os, const Car& s);
};
#endif
