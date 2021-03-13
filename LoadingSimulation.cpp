#include "LoadingSimulation.h"

void LoadingSimulation::setLoadingPlace()
{
	LoadingPlace.resize(LoadingPlaceLength);
	for (int i = 0; i < LoadingPlaceLength; i++)
	{
		LoadingPlace[i].resize(LoadingPlaceWidth);
		for (int j = 0; j < LoadingPlaceWidth; j++)
		{
			LoadingPlace[i][j].resize(LoadingPlaceDepth);
		}
	}

	int i = 0;
	int j = 0;
	int k = 0;

	for (; i < LoadingPlaceLength; i++)
	{
		LoadingPlace[i][j][k].setCube(1, 1, 1);
		for (int j = 0; j < LoadingPlaceWidth; j++)
		{
			LoadingPlace[i][j][k].setCube(1, 1, 1);
			for (int k = 0; k < LoadingPlaceDepth; k++)
			{
				LoadingPlace[i][j][k].setCube(1, 1, 1);
			}
		}
	}
}


void LoadingSimulation::setBox()
{
	Box.resize(BoxLength);
	for (int i = 0; i < BoxLength; i++)
	{
		Box[i].resize(BoxWidth);
		for (int j = 0; j < BoxWidth; j++)
		{
			Box[i][j].resize(BoxDepth);
		}
	}
	int i = 0;
	int j = 0;
	int k = 0;

	for (; i < BoxLength; i++)
	{
		Box[i][j][k].setCube(1, 1, 1);
		for (int j = 0; j < BoxWidth; j++)
		{
			Box[i][j][k].setCube(1, 1, 1);
			for (int k = 0; k < BoxDepth; k++)
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

	int loadingPlaceWidth = getLoadingPlaceWidth();
	int loadingPlaceLength = getLoadingPlaceLength();
	int loadingPlaceDepth = getLoadingPlaceDepth();

	int BoxWidth = getBoxCoordWidth();
	int BoxLength = getBoxCoordLength();
	int BoxDepth = getBoxCoordDepth();

	for (; i < loadingPlaceLength; i++)
	{
		BoxWidth = getBoxCoordWidth();
		j = 0;
		if (LoadingPlace[i].size() >= Box[0].size())
		{
			for (; j < loadingPlaceWidth; j++)
			{
				k = 0;
				if (LoadingPlace[i][j].size() >= Box[0][0].size())
				{
					for (; k < BoxDepth; k++)
					{
						LoadingPlace[i][j][k] -= Box[0][0][0];
					}
					BoxWidth--;

				}
				if (BoxWidth == 0) //jumping to next box length
				{
					j = loadingPlaceWidth;
					BoxLength--;
				}

			}
			if (BoxLength == 0) //exit the cycle when box is loaded
				i = loadingPlaceLength;
		}

	}
		removeOccupiedSpace();
}

void LoadingSimulation::removeOccupiedSpace()
{
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	int BoxLength = getBoxCoordLength();
	int BoxWidth = getBoxCoordWidth();
	int BoxDepth = getBoxCoordDepth();

	int loadingPlaceWidth = getLoadingPlaceWidth();
	int loadingPlaceLength = getLoadingPlaceLength();
	int loadingPlaceDepth = getLoadingPlaceDepth();

	//Erasing empty 3D vector elements
	for (; i < LoadingPlace.size(); i++)
	{
		j = 0;
		BoxWidth = getBoxCoordWidth();
		for (; j < LoadingPlace[i].size(); j++)
		{
			k = 0;
			for (; k < LoadingPlace[i][j].size(); k++)
			{
				if (LoadingPlace[i][j][k].isEmpty()) //checking if cube sides at VECTOR(i,j,k) is empty
				{

				LoadingPlace[i][j].erase(LoadingPlace[i][j].begin(), LoadingPlace[i][j].begin() + getBoxCoordDepth());//if VECTOR(i,j,k) vector is empty decreasing vector depth by box depth
				if (LoadingPlace[i][j].empty() || LoadingPlace[i][j].size() <= Box[0][0].size())
				{
					
					LoadingPlace[i][j].erase(LoadingPlace[i][j].begin(), LoadingPlace[i][j].end());

					if (LoadingPlace[i].empty() || LoadingPlace[i].size() <= Box[0].size())
					{
						LoadingPlace[i].erase(LoadingPlace[i].begin(), LoadingPlace[i].end());
					}

				}

				if (LoadingPlace[i][j].size() <= getBoxCoordDepth())
					LoadingPlace[i][j].erase(LoadingPlace[i][j].begin(), LoadingPlace[i][j].begin() + LoadingPlace[i][j].size());
				k = LoadingPlace[i][j].size(); //resets depth counter
				BoxWidth--;
				}
			}
			if (BoxWidth == 0) //jumping to next box length
			{
				j = loadingPlaceWidth;
				BoxLength--;
			}
			
		}
		if (BoxLength == 0) //exit the cycle when box is loaded
		{
			i = loadingPlaceLength;
		}

	}

}

void LoadingSimulation::setBox(double BoxLength, double BoxWidth, double BoxDepth)
{
	this->BoxLength = MakeInt((BoxLength + 0.001) * 10);
	this->BoxDepth = MakeInt((BoxDepth + 0.001) * 10);
	this->BoxWidth = MakeInt((BoxWidth + 0.001) * 10);
}

void LoadingSimulation::setLoadingPlace(double Length, double Width, double Depth)
{
	LoadingPlaceLength = MakeInt((Length + 0.001) * 10);
	LoadingPlaceDepth = MakeInt((Depth + 0.001) * 10);
	LoadingPlaceWidth = MakeInt((Width + 0.001) * 10);
}

bool LoadingSimulation::IsLoadPossible(double BoxCubes, double LoadCube)
{
	roundNum(BoxCubes);
	roundNum(LoadCube);
	return LoadCube >= BoxCubes ? 1 : 0;
}


void LoadingSimulation::resetLoadingPlace()
{
	setLoadingPlace();
}

bool LoadingSimulation::isSpaceLeft() 
{
	int i = getLoadingPlaceLength() - 1;
	int j = getLoadingPlaceWidth() - 1;

	if (LoadingPlace[i][j].size() <= Box[0][0].size())
		return false;
	else
		return true;

}