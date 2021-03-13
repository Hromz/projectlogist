#include "LogisticApplication.h"
 #ifdef _WIN32
#include <Windows.h>
 #endif

int main()
{
	using std::cout;
	using std::cin;
	LogisticApplication application;

	char c;
	cout << "Data should be in meters!";
	cout << "\nExample:  ""Enter length of pallet: 1.35;\t  Enter width of pallet: 0.85\n";

	do
	{
		cout << "\n\t            Enter which calculation do you wish to do:\n";
		cout << "\n\t1) For SingleOrder\n" << "\t2) For MultiOrder\n" << "\t3) Check which car you need for order\n";
		cout << "\t4) For box loading\n" << "\t5) Calculation according to cubes and quanity only\n";
		cout << "\t6) Load boxes into pallet, after that returns how many pallets do you need\n";
		cout << "\t7) How many cars do you need for an order\n";
		cout << "\t0) Exit\n";

		cout << "Enter your choice: ";
		cin >> c;
		EatLine();
		switch (c)
		{
		case '1':
			application.singleOrder();
			break;
		case '2':
			application.multiOrder();
			break;
		case '3':
			application.carCheck();
			break;
		case '4':
			application.boxloading();
			break;
		case '5':
			application.cubeBoxloading();
			break;
		case '6':
			application.boxesIntoPallet();
			break;
		case '7':
			application.boxesIntoCarViaCatalogue();
			break;
		case '0':
			exit(1);
		default:
			break;
		}
	} while (c != '0');


	system("pause");
	return 0;
}