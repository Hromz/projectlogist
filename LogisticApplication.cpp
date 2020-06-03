#include "LogisticApplication.h"

//Simple function
//Asks user to input car and pallet size
//Print if loading is possible or not
void LogisticApplication::SingleOrder()
{
	using std::cout;
	using std::cin;

	Pallet pallets;
	Car car;

	cin >> car;
	car.setCubeM();

	cout << "\nYou entered\n";
	cout << car;

	cout << "Enter the size of pallets\n";
	cin >> pallets;
	pallets.setCubeMetr();

	cout << "\nYou entered\n";
	cout << pallets;

	if (pallets.getHeight() > car.getHeight())
	{
		cout << "Car cannot be loaded, pallet(s) are too high!";
		exit(1);
	}

	auto s = pallets.getArea();
	auto v = car.getCubeMetr();

	car.setWidthArea(pallets.getWidth());
	car.setPalletLengthRow(pallets.getQuanity());
	car.setOccupiedPalletLength(pallets.getLength());

	if ((v - s) <= 0)
		cout << "\nNot enough car size for order!\n";
	else if (car.loadWidth(pallets.getWidth()) && car.multiMachLoad() && pallets.getHeight() <= car.getHeight())
	{
		cout << "\nThe order is correct!\n";
		cout << (v - s) << " cubes left in a car!\n";
	}
	else
	{
		cout << "\nNot enough car size for order!\n";
		cout << (v - s) << " cubes left in a car!\n";
	}

}

//Loading several orders into car with pallets
void LogisticApplication::MultiOrder()
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::vector;
	using std::string;

	vector<Pallet> orders;
	Pallet tempPallet;
	Car car;

	string* q = new string;
	int row;

	cin >> car;
	car.setCubeM();

	cout << "\nYou entered\n";
	cout << car;
	double carlength = car.getLength();
	double lengthSum = 0;

	cout << "Enter 'p' to process entering the data, 'q' for stop\n";
	while (cin >> *q && * q != "q")
	{
		cin >> tempPallet;
		orders.push_back(tempPallet);
		if (tempPallet.getHeight() > car.getHeight())
		{
			cout << "Car cannot be loaded, pallet's exceeds car height!";
			break;
		}
		cout << "Enter 'p' to process entering the data, 'q' for stop\n";
	}
	if (tempPallet.getHeight() > car.getHeight())
	{
		exit(1);
	}

	for (auto it = orders.begin(); it != orders.end(); it++)
	{
		row = loadWidth(it->getWidth(), car.getWidth());
		lengthSum = (((it->getLength() * it->getQuanity())) / row);

		if (loadRow(lengthSum, carlength, row) == true) //checking if car can be loaded
			carlength -= lengthSum; //decreasing car length by length of loaded pallets
		else
		{
			cout << "Car can't be loaded" << endl;
			carlength -= lengthSum;
			break;
		}

	}
	if ((carlength) >= 0)
	{
		cout << "Car can be loaded!" << endl;
		cout << carlength << " length left in the car.";
	}
	else
	{
		cout << "Car can't be loaded!" << endl;
	}
	delete q;
}

//Asks user to enter pallet size, quantity and destination address
//Calculates how many car will need for an order
// i.e. 34 euro pallet OUTPUT ---> 1 EuroTrack and Porter
void LogisticApplication::CarCheck()
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::vector;
	using std::string;

	Pallet tempPallets;
	std::vector<std::unique_ptr<BaseCar>> CarCatalogue;
	CarCatalogue.emplace_back(new PorterCar());
	CarCatalogue.emplace_back(new MersedesCar());
	CarCatalogue.emplace_back(new GazelCar());
	CarCatalogue.emplace_back(new FiveTonCar());
	CarCatalogue.emplace_back(new TenTonCar());
	CarCatalogue.emplace_back(new EuroTrackCar());

	string* input = new string;
	string * tempAddress = new string;

	vector<Pallet> order;
	vector<string> adress;
	vector<std::unique_ptr<BaseCar>> CarOrder;

	cout << "Enter 'p' to process entering the data, 'q' for stop\n";
	while (cin >> *input && *input != "q")
	{
		cout << "Enter delivery adress or destination point\n";
		cin.get();
		getline(cin, *tempAddress);
		adress.push_back(*tempAddress);
		cin >> tempPallets;
		order.push_back(tempPallets);

		cout << "Enter 'p' to process entering the data, 'q' for stop\n";
	}

	auto its = adress.begin();
	auto itp = order.begin();
	auto catalogueIt = CarCatalogue.begin();
	int loadedPallets = 0;

	for (; its != adress.end(), itp != order.end(); itp++, its++)
	{
		double totalArea = itp->getArea();
		int tempQuan = itp->getQuanity();
		while (totalArea > 0 && tempQuan > 0)
		{
			if ((*catalogueIt)->isApplicaple(tempQuan))
			{
				CarOrder.emplace_back((*catalogueIt)->duplicate());
				loadedPallets = (int)((*catalogueIt)->getLength() / itp->getLength()) * (*catalogueIt)->getLoadWidth(itp->getWidth());
				tempQuan -= loadedPallets;
				totalArea -= itp->getLoadedArea(loadedPallets);
			}
			else if ((catalogueIt == CarCatalogue.end() - 1) && (!(*catalogueIt)->isApplicaple(tempQuan)))
			{
				CarOrder.emplace_back((*catalogueIt)->duplicate());
				loadedPallets = (int)((*catalogueIt)->getLength() / itp->getLength()) * (*catalogueIt)->getLoadWidth(itp->getWidth());
				tempQuan -= loadedPallets;
				totalArea -= itp->getLoadedArea(loadedPallets);
				catalogueIt = CarCatalogue.begin();
			}
			else
			{
				catalogueIt++;
			}		
		} catalogueIt++ = CarCatalogue.begin();

		std::cout << "For " << *(its) << endl;
		auto car = CarOrder.begin();
	for (; car != CarOrder.end(); car++)
	{
		cout << "One " << ((*car)->getCarName()) << endl;
	}
	CarOrder.clear();//Clearing vector for next order
	cout << "You need for an order\n." << endl;
	}
	delete input, tempAddress;
}

//Takes total length, car length and numbers of pallet loaded in width
//Returns if a car can be loaded
//Checking if length is suitable for an order
bool LogisticApplication::loadRow(double sum_of_length, double car_length, int rows)
{
	double temp = 0;
	temp = sum_of_length / (double)rows;

	if (temp <= car_length)
		return true;
	else
		return false;
}

//Take pallet width and car width as parameters
//Checking how many pallets will be loaded in width
//Returns pallet quantity that can be loaded in width
int LogisticApplication::loadWidth(double palletWidth, double carWidth)
{
	if (palletWidth == 0)
		return 0;
	else if (palletWidth * 3 > (carWidth + 0.2))
		return 2;
	else if (palletWidth * 2 > (carWidth + 0.2))
		return 1;
	else if (palletWidth * 3 <= (carWidth + 0.2))
		return 3;
	else
		return 2;
}

//Loading car with boxes
//Asking user to input size of boxes and quantity
//Checking if them can be loaded in a car
void LogisticApplication::boxloading()
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::vector;
	using std::string;

	LoadingSimulation load;
	string * input = new string;
	double totalBoxCubes = 0;

	Car car;
	cin >> car;
	car.setCubeM();

	Box tempbox;
	std::vector<Box> BoxOrder;

	cout << "Enter 'p' to process entering the data, 'q' for stop\n";
	while (cin >> *input && *input != "q")
	{
		cin >> tempbox;
		tempbox.optimumLoading(car.getLength(), car.getWidth(), car.getHeight());
		BoxOrder.push_back(tempbox);
		cout << "Enter 'p' to process entering the data, 'q' for stop\n";
	}
	std::sort(BoxOrder.begin(), BoxOrder.end(), [](Box& box1, Box& box2) {
		return (box1.getLength(), box1.getHeight(), box1.getWidth()) > (box2.getLength(), box2.getHeight(), box2.getWidth());
		}
		);

	load.setCarCoordinate(car.getLength(), car.getWidth(), car.getHeight());
	load.setCarBack();

	for (int j = 0; j < BoxOrder.size(); j++)
	{
		totalBoxCubes += BoxOrder[j].getCube();
	}

	if(load.IsLoadPossible(totalBoxCubes, car.getCubeMetr()))
	{ 
	for (int j = 0; j < BoxOrder.size(); j++)
	{
		load.setBoxCoordinate(BoxOrder[j].getLength(), BoxOrder[j].getWidth(), BoxOrder[j].getHeight());
		for (int i = 0; i < BoxOrder[j].getQuantity() - 1; i++)
		{
				load.setBox();
				load.LoadBox();
				load.checkCarBack();
		}
		car.changeCubeMetr(BoxOrder[j].getCube());
	}
	}
	else
	{
		std::cout << "Car cannot be loaded!\nBoxes volume exceeds car volume!" << std::endl;
	}

	if (car.getCubeMetr() >= 0)
		std::cout << "Car can be loaded! " << car.getCubeMetr() << " cubes left in the car." << std::endl;

	delete input;
}


//Asks user to input car dimensions
//Asks for total cubes and quantity of boxes
//Calculates approximate box dimensions and check if it can be loaded to car
void LogisticApplication::CubeBoxloading()
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::string;
	using std::vector;

	double* tempLength = new double;
	double* tempWidth = new double;
	double* tempHeight = new double;
	double* totalCubes = new double;
	int* tempQuantity = new int;
	string* input = new string;
	double totalBoxCubes = 0;

	Car car;
	cin >> car;
	car.setCubeM();

	Box tempBox;
	std::vector<Box> BoxOrder;
	LoadingSimulation load;

	cout << "Enter 'p' to process entering the data, 'q' for stop\n";
	while (cin >> *input && *input != "q")
	{
		cout << "Enter quanity: ";
		cin >> *tempQuantity;
		EatLine();

		cout << "Enter cubes of boxes: ";
		cin >> *totalCubes; 
		EatLine();

		totalBoxCubes += *totalCubes;	//Summarizing cubes from orders and check if load is possible according to car cubes
		setBoxSize(*totalCubes, *tempQuantity, tempBox); //calculates each side of a box
		cout << "Cube is " << *totalCubes << endl;
		BoxOrder.push_back(tempBox);

		cout << "Enter 'p' to process entering the data, 'q' for stop\n";
	}

	if (load.IsLoadPossible(totalBoxCubes, car.getCubeMetr()))
	{
		std::sort(BoxOrder.begin(), BoxOrder.end(), [](Box& box1, Box& box2) {
			return (box1.getLength(), box1.getHeight(), box1.getWidth()) > (box2.getLength(), box2.getHeight(), box2.getWidth());
			}
		);

		load.setCarCoordinate(car.getLength(), car.getWidth(), car.getHeight());
		load.setCarBack();

		for (int j = 0; j < BoxOrder.size(); j++)
		{
			load.setBoxCoordinate(BoxOrder[j].getLength(), BoxOrder[j].getWidth(), BoxOrder[j].getHeight());
			for (int i = 0; i < BoxOrder[j].getQuantity() - 1; i++)
			{
				load.setBox();
				load.LoadBox();
				load.checkCarBack();
			}
			car.changeCubeMetr(BoxOrder[j].getCube());

		}
		if (car.getCubeMetr() >= 0)
			std::cout << "Car can be loaded! " << car.getCubeMetr() << " cubes left in the car." << std::endl;
	}
	else
		std::cout << "Car cannot be loaded!\nBoxes volume exceeds car volume!" << std::endl;

	delete tempHeight, tempLength, tempWidth, input, tempQuantity, totalCubes;
}


//Takes car length, width and height
//Returns cube of the car
double LogisticApplication::CarCube(double cLenght, double cWidth, double cHeight)
{
	return cLenght * cWidth * cHeight;
}

//Returns how many boxes will be loaded by placing them in width around car length
//One staight line
int LogisticApplication::QunLoadBoxWidth(double carLength, double boxWidth)
{
	return (carLength / boxWidth);
}

//Returns how many boxes will be loaded by placing them in length around car length
//One staight line
int LogisticApplication::QunLoadBoxlength(double carLength, double boxLength)
{
	return (carLength / boxLength);
}

//Returns how many boxes will be loaded by placing them in height, placing on each others
int LogisticApplication::QunLoadBoxHeigth(double carHeight, double boxHeight)
{
	return (carHeight / boxHeight);
}

//Returns cubes of a box
double LogisticApplication::cubeBox(double bLength, double bWidth, double bHeight)
{
	return bLength * bWidth * bHeight;
}



//Takes quantity of boxes and total cube
//Returns cubes of a box
double LogisticApplication::CubOneBox(int quanity, double cube)
{
	return cube / quanity;
}

//Function evaluating length, width and height untill (total cubes > n)
//The code will be reworked at the beginning of April
void LogisticApplication::setBoxSize(double BoxCubes, double Quantity, Box & box)
{
	using std::cout;
	using std::endl;

	double BoxCube = (BoxCubes / Quantity);
	double tempLength = 0;
	double tempWidth = 0;
	double tempHeight = 0;

	while ((tempLength * tempWidth * tempHeight) < BoxCube)
	{
		tempLength += 0.01;
		tempWidth += 0.01;
		tempHeight += 0.01;
	}
	box.setQuantity(Quantity);
	box.setLength(tempLength); box.setWidth(tempWidth); box.setHeight(tempHeight);

	cout << "Length of one box ~" << tempLength << endl;
	cout << "Width of one box ~" << tempWidth << endl;
	cout << "Height of one box ~" << tempHeight << endl;
}


//Check which car is needed for an order
//Receives data from pallets class
//Prints quantity and car type needed for an order
/*void LogisticApplication::getCar(int quantity, double totalLength, double palletLength, double palletWidth)
{
	using std::vector;
	using std::endl;
	using std::cout;

	//Car catalogue
	vector<std::unique_ptr<BaseCar>> CarCatalogue;
	CarCatalogue.emplace_back(new PorterCar());
	CarCatalogue.emplace_back(new MersedesCar());
	CarCatalogue.emplace_back(new GazelCar());
	CarCatalogue.emplace_back(new FiveTonCar());
	CarCatalogue.emplace_back(new TenTonCar());
	CarCatalogue.emplace_back(new EuroTrackCar());

	//Storing ordered cars
	vector<std::unique_ptr<BaseCar>> order;

	auto car = CarCatalogue.begin();

	while (totalLength > 0 && quantity > 0)
	{
		if ((*car)->isApplicaple(quantity))
		{
			order.emplace_back((*car)->duplicate());
			quantity -= (int)((*car)->getLength() / palletLength) * (*car)->getLoadWidth(palletWidth);
			totalLength = ((totalLength / (*car)->getLoadWidth(palletWidth)) - (*car)->getLength());
		}
		else if ((car == CarCatalogue.end() - 1) && (!(*car)->isApplicaple(quantity)))
		{
			order.emplace_back((*car)->duplicate());
			quantity -= (int)((*car)->getLength() / palletLength) * (*car)->getLoadWidth(palletWidth);
			totalLength = (((totalLength / (*car)->getLoadWidth(palletWidth)) + 0.1) - (*car)->getLength());
			car = CarCatalogue.begin();
		}
		else
			car++;
	}

	car = order.begin();
	for (; car != order.end(); car++)
	{
		cout << "One " << (*car)->getCarName() << endl;
	}
	cout << "You need for an order!" << endl;
}*/