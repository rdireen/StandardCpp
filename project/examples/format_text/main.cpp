
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <boost/format.hpp>

using namespace std;

namespace b = boost;

using fmt = b::format;

/// An example showing how to format strings
void format_examples(){

    cout << fmt{"who's cool: %1%"} % "randy" << endl;

    cout << fmt("here's a number: %2.2f") % 3.14159268979 << endl;

    // left align
    cout << fmt("Integer: %-12i see") % 23555 << endl;

    // right align
    cout << b::format("Integer: %12i see") % 23555 << endl;

    // add some color
    cout << b::format("Integer: \33\[33msee\33\[0m") << endl;
    
}

int main(int argc, char * argv[]){

    format_examples();

}
