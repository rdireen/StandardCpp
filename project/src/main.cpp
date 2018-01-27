
#include <iostream>
#include <boost/version.hpp>
#include <boost/format.hpp>
#include <rhd/common.hpp>

using namespace std;
namespace b = boost;

int main(){

    cout << "Boost Version: " << rhd::boost_version() << endl;
    cout << "Goodbye cruel world" << endl;

    cout << endl;

    cout << b::format{"who's cool: %1%"} % "randy" << endl;

    cout << b::format("here's a number: %2.2f") % 3.14159268979 << endl;

    // left align
    cout << b::format("Integer: %-12i see") % 23555 << endl;

    // right align
    cout << b::format("Integer: %12i see") % 23555 << endl;

    // add some color
    cout << b::format("Integer: \33\[33msee\33\[0m") << endl;

}
