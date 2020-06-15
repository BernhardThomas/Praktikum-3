#ifndef NICK_H
#define NICK_H

#include <string>
using std::string;

void Uinput(string& real, string& nick, int& yob, int& mob);

void Ureview(string& real, string& nick, int& yob, int& mob);

void checkvalid(string& real, string& nick, int& yob, int& mob, int& age);

double calcAgeBeforeApril2020(int& yob, int& mob);

#endif // NICK