#include "LogisticApplication.h"

//Simple function
//Asks user to input car and pallet size
//Print if loading is possible or not
void LogisticApplication::singleOrder()
{
	using std::cout; using std::cin;

	Pallet pallets; Car car;

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
void LogisticApplication::multiOrder()
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::vector;
	using std::string;

	vector<Pallet> orders;
	Pallet tempPallet;
	Car car;

	string q;
	int row;
	char inp;

	cin >> car;
	car.setCubeM();

	cout << "\nYou entered\n";
	cout << car;
	double carlength = car.getLength();
	double lengthSum = 0;

	while (cin >> tempPallet)
	{
		orders.push_back(tempPallet);
		if (tempPallet.getHeight() > car.getHeight())
		{
			cout << "Car cannot be loaded, pallet's exceeds car height!";
			break;
		}
		cout << "Continue input ? y or n: ";
		cin >> inp;
		if (inp == 'n')
			break;
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
		}

	}
	if ((carlength) > 0)
	{
		cout << "Car can be loaded!" << endl;
		cout << carlength << " length left in the car.";
	}
	else
	{
		cout << "Car can't be loaded!" << endl;
	}
}

//Asks user to enter pallet size, quantity and destination address
//Calculates how many car will need for an order
// i.e. 34 euro pallet OUTPUT ---> 1 EuroTrack and Porter
void LogisticApplication::carCheck() //redo code logic later and optimize algorithm!
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

	
	char inp;
	string tempAdress;

	vector<Pallet> order;
	vector<string> adress;
	vector<std::unique_ptr<BaseCar>> CarOrder;


	cout << "Enter delivery adress or destination point: ";
	while (getline(cin, tempAdress))
	{
		adress.push_back(tempAdress);
		cin >> tempPallets;
		order.push_back(tempPallets);

		cout << "Continue input ? y or n: ";
		cin >> inp;
		if (inp == 'n')
			break;

		cout << "Enter delivery adress or destination point: ";
		cin.get();
	}

	int loadedPallets = 0;
	auto its = adress.begin(); auto itp = order.begin();

	for (; its != adress.end(), itp != order.end(); itp++, ++its) //
	{
		auto catalogueIt = CarCatalogue.begin();
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
		} //catalogueIt++ = CarCatalogue.begin();

		std::cout << "For " << *its << endl;
		auto car = CarCatalogue.begin();
		auto itcar = CarOrder.begin();

		vector<string> tempCarName;
		for (; itcar  != CarOrder.end(); itcar++)
		{
			tempCarName.emplace_back((*itcar)->getCarName());
		}

	for (; car != CarCatalogue.end(); car++)
	{
		int carquan = 0;
		string ord = (*car)->getCarName();
		carquan = count(tempCarName.begin(), tempCarName.end(), ord); //checking and counts how many cars were ordered and which one

		if(carquan > 0)
		cout << carquan << " " << ((*car)->getCarName()) << endl;	
	}
	tempCarName.clear();//Clearing vector for next order
	CarOrder.clear();  //Clearing vector for next order
	cout << "You need for an order\n" << endl;
	}
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
//Checking if they can be loaded in a car
void LogisticApplication::boxloading()
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::vector;
	using std::string;

	LoadingSimulation load;
	char inp;
	double totalBoxCubes = 0;

	Car car;
	cin >> car;
	car.setCubeM();

	Box tempbox;
	std::vector<Box> BoxOrder;

	while (cin >> tempbox)
	{
		tempbox.optimumLoading(car.getLength(), car.getWidth(), car.getHeight());
		BoxOrder.push_back(tempbox);

		cout << "Continue input ? y or n: ";
		cin >> inp;
		if (inp == 'n')
			break;
	}

	//sorting box for loading, first begger one and after smaller ones
	std::sort(BoxOrder.begin(), BoxOrder.end(), [](Box& box1, Box& box2) {
		return (box1.getLength(), box1.getHeight(), box1.getWidth()) > (box2.getLength(), box2.getHeight(), box2.getWidth());
	});

	load.setLoadingPlace(car.getLength(), car.getWidth(), car.getHeight());
	load.setLoadingPlace();

	for (size_t j = 0; j < BoxOrder.size(); j++)
	{
		totalBoxCubes += BoxOrder[j].getCube();
	}

	if(load.IsLoadPossible(totalBoxCubes, car.getCubeMetr()))
	{ 
	for (size_t j = 0; j < BoxOrder.size(); j++)
	{
		load.setBox(BoxOrder[j].getLength(), BoxOrder[j].getWidth(), BoxOrder[j].getHeight());
		load.setBox();
		for (int i = 0; i < BoxOrder[j].getQuantity() - 1; i++)
		{
				load.LoadBox();
		}
		car.changeCubeMetr(BoxOrder[j].getCube());
	}
	}
	else
	{
		std::cout << "Car cannot be loaded!\nBoxes volume exceeds car volume!" << std::endl;
	}

	if (totalBoxCubes <= car.getCubeMetr())
		std::cout << "Car can be loaded! " << car.getCubeMetr() << " cubes left in the car." << std::endl;

}


//Asks user to input car dimensions
//Asks for total cubes and quantity of boxes
//Calculates approximate box dimensions and check if it can be loaded to car
void LogisticApplication::cubeBoxloading()
{
	using std::cout; using std::endl; using std::cin; using std::string; using std::vector;

	//Box dimension is unknown so first we are storing pseudo sides to temp variable and after that assign to box class
	//double tempLength, tempWidth, tempHeight, totalCubes;
	double totalCubes;
	int tempQuantity = 0;
	char inp;
	double totalBoxCubes = 0;

	Car car;
	cin >> car;
	car.setCubeM();

	Box tempBox;
	std::vector<Box> BoxOrder;
	LoadingSimulation load;

	cout << "Enter quantity: ";
	while (cin >> tempQuantity)
	{
		EatLine();
		cout << "Enter total cube of boxes: ";
		cin >> totalCubes;
		EatLine();

		totalBoxCubes += totalCubes;	//Summarizing cubes from orders and check if load is possible according to car cubes
		setBoxSize(totalCubes, tempQuantity, tempBox); //calculates each side of a box
		cout << "Cube is " << totalCubes << endl;
		BoxOrder.push_back(tempBox);

		cout << "Continue input ? y or n: ";
		cin >> inp;
		if (inp == 'n')
			break;
		else
			cout << "Enter quantity: ";
	}

	if (load.IsLoadPossible(totalBoxCubes, car.getCubeMetr()))
	{
		std::sort(BoxOrder.begin(), BoxOrder.end(), [](Box& box1, Box& box2) {
			return (box1.getLength(), box1.getHeight(), box1.getWidth()) > (box2.getLength(), box2.getHeight(), box2.getWidth());
			}
		);

		load.setLoadingPlace(car.getLength(), car.getWidth(), car.getHeight());
		load.setLoadingPlace();

		for (size_t j = 0; j < BoxOrder.size(); j++)
		{
			load.setBox(BoxOrder[j].getLength(), BoxOrder[j].getWidth(), BoxOrder[j].getHeight());
			load.setBox();
			for (int i = 0; i < BoxOrder[j].getQuantity() - 1; i++)
			{
				load.LoadBox();
			}
			car.changeCubeMetr(BoxOrder[j].getCube());

		}
		if (car.getCubeMetr() >= 0 && car.getCubeMetr() <= totalBoxCubes)
			std::cout << "Car can be loaded! " << car.getCubeMetr() << " cubes left in the car." << std::endl;
	}
	else
		std::cout << "Car cannot be loaded!\nBoxes volume exceeds car volume!" << std::endl;

}

void LogisticApplication::boxesIntoPallet() {
	using std::cout;
	using std::cin;
	using std::endl;
	using std::vector;

	char inp;

	int palletQuantity = 0;
	double palletLength, palletWidth, palletHeight;
	std::cout << "Enter size of a pallet: ";
	cin >> palletLength >> palletWidth >> palletHeight;

	Box tempbox;
	vector<Box> order;

	
	while (cin >> tempbox)
	{
		tempbox.optimumLoading(palletLength, palletWidth, palletHeight);
		order.push_back(tempbox);
		cout << "Continue input ? y or n: ";
		cin >> inp;
		if (inp == 'n')
			break;
	}

	for (int i = 0; i < (int)order.size(); i++)
	{
		palletQuantity += order[i].getLoadingQuantity(palletLength, palletWidth, palletHeight);
	}

	if(palletQuantity == 0)
	cout << palletQuantity + 1 << " pallet you need for this quantity!" << endl;
	else
		cout << palletQuantity << " pallet you need for this quantity!" << endl;
}

void LogisticApplication::boxesIntoCarViaCatalogue() {
	using std::cout;
	using std::endl;
	using std::cin;
	using std::vector;
	using std::string;

	Box tempbox;
	std::vector<Box> order;
	LoadingSimulation loadingplace;
	char inp;
	string tempAdress;

	vector<string> adress;
	vector<std::unique_ptr<BaseCar>> CarOrder;

	cout << "Enter delivery adress or destination point: ";
	while (getline(cin, tempAdress))
	{
		adress.push_back(tempAdress);
		while (cin >> tempbox)
		{
			order.push_back(tempbox);

			cout << "Continue box input ? y or n: ";
			cin >> inp;
			if (inp == 'n')
				break;
		}

		std::sort(order.begin(), order.end(), [](Box& box1, Box& box2) {
			return (box1.getLength(), box1.getHeight(), box1.getWidth()) > (box2.getLength(), box2.getHeight(), box2.getWidth());
			});

		cout << tempAdress;
		chooseCar(order.size(), order);


		cout << "Continue order input ? y or n: ";
		cin >> inp;
		if (inp == 'n')
			break;

		cout << "Enter delivery adress or destination point: ";
		cin.get();
	}



}


void LogisticApplication::chooseCar(int size_v, std::vector<Box> boxRef)
{
	char carchoice;
	double sumOfCubes = 0;
	int sumOfBoxes = 0;
	LoadingSimulation load;

	auto b = boxRef.begin();

	std::vector<std::unique_ptr<BaseCar>> CarCatalogue;
	std::cout << "Choose which type of car you want to use for an order.\n";
	std::cout << "1 for less that 10 cubes.\n" << "2 for less that 20 cubes\n" << "3 for euro track\n";
	std::cout << "0 for exit\n";

    std::cin >> carchoice;

	switch (carchoice)
	{
	case '1':
	{
		CarCatalogue.emplace_back(new PorterCar());
		CarCatalogue.emplace_back(new MersedesCar());
		CarCatalogue.emplace_back(new GazelCar());
		break;
	}
	case '2':
	{
		CarCatalogue.emplace_back(new FiveTonCar());
		CarCatalogue.emplace_back(new TenTonCar());
		break;
	}
	case '3':
	{
		CarCatalogue.emplace_back(new EuroTrackCar());
		break;
	}
	default:
		std::cout << "Incorrect choice!\n" << "Please enter again!\n";
		break;
	};


	/*std::vector< std::unique_ptr< YourClass >> pointers;
for( auto&& pointer : pointers ) {
    pointer->functionOfYourClass();
}
	*/
	/*for (auto&& catalogueIt : CarCatalogue)
	{
		if (sumOfCubes <= (catalogueIt)->getCarCube())
			break;
	}*/

	auto && catalogueIt = CarCatalogue.begin();
	b->optimumLoading((*catalogueIt)->getLength(), (*catalogueIt)->getWidth(), (*catalogueIt)->getHeight());
	load.setLoadingPlace((*catalogueIt)->getLength(), (*catalogueIt)->getWidth(), (*catalogueIt)->getHeight());
	load.setLoadingPlace();

	int tempBoxQuan = 0;
	int carQuan = 1;

	for (; b != boxRef.end(); b++)
	{
		load.setBox(b->getLength(), b->getWidth(), b->getHeight());
		load.setBox();
		tempBoxQuan = b->getQuantity();
		while(tempBoxQuan > 0)
		{
			if(load.isSpaceLeft())
					load.LoadBox();
				else
				{
					load.setLoadingPlace((*catalogueIt)->getLength(), (*catalogueIt)->getWidth(), (*catalogueIt)->getHeight());
					load.setLoadingPlace();
					load.LoadBox();
					carQuan++;
				}
			tempBoxQuan--;
		}
	}

	if (carQuan == 0)
		std::cout << (carQuan + 1) << " " << (*catalogueIt)->getCarName() << " you need for an order.\n" << std::endl;
	else
		std::cout << carQuan << " " << (*catalogueIt)->getCarName() << " you need for an order\n";
	CarCatalogue.clear();
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
	return MakeInt((carLength / boxWidth));
}

//Returns how many boxes will be loaded by placing them in length around car length
//One staight line
int LogisticApplication::QunLoadBoxlength(double carLength, double boxLength)
{
	return MakeInt((carLength / boxLength));
}

//Returns how many boxes will be loaded by placing them in height, placing on each others
int LogisticApplication::QunLoadBoxHeigth(double carHeight, double boxHeight)
{
	return MakeInt((carHeight / boxHeight));
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
void LogisticApplication::setBoxSize(double BoxCubes, int Quantity, Box & box)
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