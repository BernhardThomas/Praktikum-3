/*
Author: Kat Bergen
		Bernhard Thomas
v.02 June.2020 -- added error handling
				  added source/header for functions
				  minor changes to formating

*/


#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;

#include "nick.h"
#include "myError.h"



int main()

try {
	string nick{ "no nickname" };
	string real{ "no realname" };
	int yob{ 0 };
	int mob{ 0 };
	int ageInYears{};
	int ageInMonth{};

	Uinput(real, nick, yob, mob);

	Ureview(real, nick, yob, mob);

	calcAgeBeforeApril2020(yob, mob);

	checkvalid(real, nick, yob, mob, ageInYears);

	cout << "\n\n\n\t" << "Age at Start of Semester: " << calcAgeBeforeApril2020(yob, mob) << "\n\n\n";

	return 0;
}

catch (std::runtime_error& e)
{
	std::cerr << std::endl;  e.what();
}

catch (...)
{
	std::cerr << std::endl << "unknown error.";

}

