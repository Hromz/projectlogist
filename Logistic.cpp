#include "LogisticApplication.h"

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
		cout << "\t0) Exit\n";

		cout << "Enter your choice: ";
		cin >> c;
		switch (c)
		{
		case '1':
			application.SingleOrder();
			break;
		case '2':
			application.MultiOrder();
			break;
		case '3':
			application.CarCheck();
			break;
		case '4':
			application.boxloading();
			break;
		case '5':
			application.CubeBoxloading();
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