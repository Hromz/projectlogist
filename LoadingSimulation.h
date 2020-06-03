#ifndef LOADINGSIMULATION_H
#define LOADINGSIMULATION_H
#include "Cube.h"
#include "Cube.cpp"
#include <vector>
#include <cassert>
#include "Routines.cpp"

class LoadingSimulation
{
private:
	int CarCoordinateLength = 0;
	int CarCoordinateDepth = 0;
	int CarCoordinateWidth = 0;

	int BoxCoordinateLength = 0;
	int BoxCoordinateWidth = 0;
	int BoxCoordinateDepth = 0;
protected:
	std::vector< std::vector< std::vector< Cube<double> > > > carBack;
	std::vector< std::vector< std::vector< Cube<double> > > > Box;
public:
	LoadingSimulation() {}
	~LoadingSimulation() {}

	inline int getCarCoordLength() { return CarCoordinateLength; }
	inline int getCarCoordWidth() { return CarCoordinateWidth; }
	inline int getCarCoordDepth() { return CarCoordinateDepth; }

	inline int getBoxCoordLength() { return BoxCoordinateLength; }
	inline int getBoxCoordWidth() { return BoxCoordinateWidth; }
	inline int getBoxCoordDepth() { return BoxCoordinateDepth; }

	void setBox(); //initializing 3D box vector with small cubes (1,1,1) according to box dimensions
	void setBoxCoordinate(double BoxLength, double BoxWidth, double BoxDepth); //changes double value to int for vector 3d size
	void LoadBox(); //substracting (1,1,1) box cubes from carBack vector

	void setCarBack(); //initializing 3D car back vector with small cubes (1,1,1) according to car dimensions
	void setCarCoordinate(double CarLength, double CarWidth, double CarDepth); //changes double value to int for vector 3d size

	void removeOccupiedSpace(); //erasing empty (1,1,1) cubes from car back
	void checkCarBack() { carBack; }

	bool IsLoadPossible(double BoxCubes, double CarCube); //compares box cubes with car cubes
};
#endif
