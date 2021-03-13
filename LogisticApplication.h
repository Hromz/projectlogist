#ifndef LogisticApplication_H
#define LogisticApplication_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <string>
#include "Lazylogistician.h"
#include "cars.h"
#include <stdlib.h>
#include "LoadingSimulation.h"
#include "Box.h"

class LogisticApplication
{
private:
	double length = 0;
	double height = 0;
	double width = 0;
public:
	LogisticApplication() {}
	~LogisticApplication() {}
	//void getCar(int quantity, double totalLength, double palletLength, double palletWidth);
	void setBoxSize(double BoxCubes, int Quantity, Box& b);

	double CarCube(double cLenght, double cWidth, double cHeight); //returns cubic of car
	int QunLoadBoxWidth(double carLength, double boxWidth); //returns how many boxes will be loaded in a row of width
	int QunLoadBoxlength(double carLength, double boxLength); //returns how many boxes will be loaded in a row of length
	int QunLoadBoxHeigth(double carHeight, double boxHeight); //returns how many boxes will be loaded in a row of height
	double CubOneBox(int quanity, double cube); //returns total cubes of boxes

	double cubeBox(double bLength, double bWidth, double bHeight); //returns cubic meters of a box
	//int CarBoxLoad(int quanity, int rowWidth, int rowHeight, int rowLength);

	//Console choices
	void singleOrder();
	void multiOrder();
	void carCheck();
	void boxloading();
	void cubeBoxloading();
	void boxesIntoPallet();
	void boxesIntoCarViaCatalogue();

	void chooseCar(int size_v, std::vector<Box> boxRef);

	//int CarQuanOrder(double l, double h, double w, double cl, double ch, double cw);
	bool loadRow(double ls, double c, int r);
	int loadWidth(double it, double w);

};
#endif