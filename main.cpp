#include <type_traits>
#include <utility>
#include <cstdlib>

#include "literal_types.h"

/*
    g++ main.cpp -std=c++14 -o exe
*/

// Example of usage

#include <string>
#include <iostream>

using namespace std;


int main()
{
   cout << STYPE("another string")::value() << endl;
   cout << DTYPE("12345")::value() << endl;
   cout << XTYPE("0ABcdEf")::value() << endl;
   cout << FTYPE("0X1.BC70A3D70A3D7P+6")::value() << endl;
   cin.get();
}
