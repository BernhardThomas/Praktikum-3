/*
Taschenrechner-Program
Bernhard Thomas Juni-2020

Erkennt mathematische eingaben in der Console und behandelt dieser anhand folgender Grammatik:

Expression:
    Term
    Expression + Term
    Expression - Term
Term
    Primary
    Term * Primary
    Term / Primary
Primary
    Number
    ( Expression )
    - Primary
    + Primary
Number
    floating-point-literal 
*/


#include <iostream>
#include <exception>
#include "myError.h"
#include "Token.h"
using std::cin;
using std::cout;

Token_Stream ts;


/*Implementierung der benötigten Grammatik*/

double expression();
double term();
double primary();

double expression() 
{
    double left = term();
    Token t = ts.get();
    while (true){
        switch (t.kind) {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

double term() 
{
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind){
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return d;
    }
    case '8':
        return t.value;
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}


/*Eingabeaufforderung*/
void start_prompt()
{
    cout << "Geben sie eine mathematischen Ausdruck ein. \nGeben sie '?' ein, um Bedienungshilfe an zu zeigen.\n";
}

/*Bedienungshilfe*/
void help()
{
    cout << "Mathematische Ausdruecke die folgende Zeichen enthalten sind erlaubt:\nKlammern:\t'('\t')'\nOperatoren:\t '+'\t'-'\t'*'\t'/'\n"
        "Einem Ausdruck muss ein ';' folgen\n"
        "Es koennen mehrere Ausdruecke hintereinander eingegeben werden\n"
        "geben sie 'q' ein, um das Program zu beenden\n";
}

/**/
void calculate()
{
    while (cin)
    {
        const string prompt = "> ";             // EingabeAufforderung
        const string result = "= ";             // Angabe Ausgabe

        cout << prompt;
        Token t = ts.get();


        while (t.kind == ';') t = ts.get();
        if (t.kind == 'q')
        {
            cout << "Program terminated \n";
            break;
        }
        if (t.kind == '?')
        {
            help();
            calculate();
        }
        ts.putback(t);
        cout << result << expression() << '\n';
    }
}




int main()
{
    try {
        start_prompt();
        calculate();
        }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    catch (...) {
        std::cerr << "exception \n";
        return -2;
    }
}
