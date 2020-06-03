#include "LoadingSimulation.h"

void LoadingSimulation::setCarBack()
{
	carBack.resize(CarCoordinateLength);
	for (int i = 0; i < CarCoordinateLength; i++)
	{
		carBack[i].resize(CarCoordinateWidth);
		for (int j = 0; j < CarCoordinateWidth; j++)
		{
			carBack[i][j].resize(CarCoordinateDepth);
		}
	}

	int i = 0;
	int j = 0;
	int k = 0;

	for (; i < CarCoordinateLength; i++)
	{
		carBack[i][j][k].setCube(1, 1, 1);
		for (int j = 0; j < CarCoordinateWidth; j++)
		{
			carBack[i][j][k].setCube(1, 1, 1);
			for (int k = 0; k < CarCoordinateDepth; k++)
			{
				carBack[i][j][k].setCube(1, 1, 1);
			}
		}
	}
}


void LoadingSimulation::setBox()
{
	Box.resize(BoxCoordinateLength);
	for (int i = 0; i < BoxCoordinateLength; i++)
	{
		Box[i].resize(BoxCoordinateWidth);
		for (int j = 0; j < BoxCoordinateWidth; j++)
		{
			Box[i][j].resize(BoxCoordinateDepth);
		}
	}
	int i = 0;
	int j = 0;
	int k = 0;

	for (; i < BoxCoordinateLength; i++)
	{
		Box[i][j][k].setCube(1, 1, 1);
		for (int j = 0; j < BoxCoordinateWidth; j++)
		{
			Box[i][j][k].setCube(1, 1, 1);
			for (int k = 0; k < BoxCoordinateDepth; k++)
			{
				Box[i][j][k].setCube(1, 1, 1);
			}
		}
	}
}


void LoadingSimulation::LoadBox()
{
	int i = 0;
	int j = 0;
	int k = 0;

	int CarWidth = getCarCoordWidth();
	int CarLength = getCarCoordLength();
	int CarDepth = getCarCoordDepth();

	int BoxWidth = getBoxCoordWidth();
	int BoxLength = getBoxCoordLength();
	int BoxDepth = getBoxCoordDepth();

			for (; i < CarLength; i++)
			{
				BoxWidth = getBoxCoordWidth();
				j = 0;
				if (carBack[i].size() >= Box[0].size())
				{ 
				for (; j < CarWidth; j++)
				{
					k = 0;
					if (carBack[i][j].size() >= Box[0][0].size())
					{ 
						for (; k < BoxDepth; k++)
						{
							carBack[i][j][k] -= Box[0][0][0];
						}
						BoxWidth--;

					}
					if (BoxWidth == 0)
					{
						j = CarWidth;
						BoxLength--;
					}
					else if (BoxWidth > 0 && j == CarWidth - 1)
					{
						j = 0;
						i++;
						BoxWidth--;
					}

					
				}
				if (BoxLength == 0)
					i = CarLength;
				}
				
			}
			if (BoxLength > 0)
			{
				std::cout << "Car is full!" << std::endl;
			}
			else
				removeOccupiedSpace();
}

void LoadingSimulation::removeOccupiedSpace()
{
	int i = 0;
	int j = 0;
	int k = 0;
	int BoxLength = getBoxCoordLength();
	int BoxWidth = getBoxCoordWidth();
	int BoxDepth = getBoxCoordDepth();

	int CarWidth = getCarCoordWidth();
	int CarLength = getCarCoordLength();
	int CarDepth = getCarCoordDepth();

	//Erasing empty 3D vector elements
	for (; i < carBack.size(); i++)
	{
		j = 0;
		BoxWidth = getBoxCoordWidth();
		for (; j < carBack[i].size(); j++)
		{
			k = 0;
			for (; k < carBack[i][j].size(); k++)
			{
				if (carBack[i][j][k].isEmpty()) //checking if cube sides at VECTOR(i,j,k) is empty
				{

					carBack[i][j].erase(carBack[i][j].begin(), carBack[i][j].begin() + getBoxCoordDepth());//if VECTOR(i,j,k) vector is empty decreasing vector depth by box depth
					if (carBack[i][j].empty())
						carBack[i].erase(carBack[i].begin(), carBack[i].begin() + getBoxCoordWidth());//if VECTOR(i,j) is empty decreasing vector width by box width
					if (carBack[i].empty())
						carBack.erase(carBack.begin()); //if VECTOR(i) is empty erasing length(i) element of vector
					k = carBack[i][j].size(); //resets depth counter
					BoxWidth--;
				}

			}
			if (BoxWidth == 0)
			{
				j = CarWidth;
				BoxLength--;
			}
			
		}
		if (BoxLength == 0)
			i = CarLength;
		
	}
}

void LoadingSimulation::setBoxCoordinate(double BoxLength, double BoxWidth, double BoxDepth)
{
	BoxCoordinateLength = MakeInt((BoxLength + 0.001) * 10);
	BoxCoordinateDepth = MakeInt((BoxDepth + 0.001) * 10);
	BoxCoordinateWidth = MakeInt((BoxWidth + 0.001) * 10);
}

void LoadingSimulation::setCarCoordinate(double CarLength, double CarWidth, double CarDepth)
{
	CarCoordinateLength = MakeInt((CarLength + 0.001) * 10);
	CarCoordinateDepth = MakeInt((CarDepth + 0.001) * 10);
	CarCoordinateWidth = MakeInt((CarWidth + 0.001) * 10);
}

bool LoadingSimulation::IsLoadPossible(double BoxCubes, double CarCube)
{
	roundNum(BoxCubes);
	roundNum(CarCube);
	return CarCube >= BoxCubes ? 1 : 0;
}
