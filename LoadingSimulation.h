#ifndef LOADINGSIMULATION_H
#define LOADINGSIMULATION_H
#include "Cube.h"
#include "Cube.cpp"
#include <vector>
#include <cassert>
#include "Routines.h"

class LoadingSimulation
{
private:
	int LoadingPlaceLength = 0;
	int LoadingPlaceDepth = 0;
	int LoadingPlaceWidth = 0;

	int BoxLength = 0;
	int BoxWidth = 0;
	int BoxDepth = 0;
protected:
	std::vector< std::vector< std::vector< Cube<double> > > > LoadingPlace;
	std::vector< std::vector< std::vector< Cube<double> > > > Box;
public:
	LoadingSimulation() {}
	~LoadingSimulation() {}

	inline int getLoadingPlaceLength() { return LoadingPlaceLength; }
	inline int getLoadingPlaceWidth() { return LoadingPlaceWidth; }
	inline int getLoadingPlaceDepth() { return LoadingPlaceDepth; }

	inline int getLoadingPlace() { return LoadingPlace.size(); } // returns how many length left for loading
	inline int getLoadingPlaceWidth(int length) { return LoadingPlace[length].size(); } //returns width sizse of a length
	inline int getLoadingPlaceDepth(int length, int width) { return LoadingPlace[length][width].size(); } //returns height of current length and width

	inline int getBoxCoordLength() { return BoxLength; }
	inline int getBoxCoordWidth() { return BoxWidth; }
	inline int getBoxCoordDepth() { return BoxDepth; }

	void setBox(); //initializing 3D box vector with small cubes (1,1,1) according to box dimensions
	void setBox(double BoxLength, double BoxWidth, double BoxDepth); //set dimensions for box to int value
	void resetLoadingPlace(); //creating new loading cube
	void LoadBox(); //substracting (1,1,1) box cubes from carBack vector

	void setLoadingPlace(); //initializing 3D car back vector with small cubes (1,1,1) according to Loading place dimensions
	void setLoadingPlace(double Length, double Width, double Depth); //set dimensions for Loading place to int value

	void removeOccupiedSpace(); //erasing empty (1,1,1) cubes from car back

	bool IsLoadPossible(double BoxCubes, double LoadingPlace); //compares box cubes with car cubes
	bool isSpaceLeft();

};
#endif
