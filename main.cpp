#include <string>
#include <iostream>
#include "tag_types.h"

/*
    g++ main.cpp -std=c++14 -o exe
*/

// Example of usage

using namespace tag;

using configuration = tl::list<
    node<
       name<SL("warping_control")>
      ,lib <SL("libwarping_control_logic.so")>
      ,communication<
          inputs<>
         ,outputs<>
      >
    >
//   ,
>;

struct test : configuration {};

struct ggg :     node<
       name<SL("warping_control")>
      ,lib <SL("libwarping_control_logic.so")>
      ,communication<
          inputs<>
         ,outputs<>
      >
    > {};


using namespace std;



int main()
{

   cout << SL("another string")::value() << endl;
   cout << DL("12345")::value() << endl;
   cout << XL("0ABcdEf")::value() << endl;
   cout << FL("0X1.BC70A3D70A3D7P+6")::value() << endl;
   cin.get();
}
