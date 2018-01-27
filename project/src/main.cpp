
#include <iostream>
#include "rhd/common.hpp"
#include "examples.hpp"

using namespace std;
//****************************************************************************
//                            MAIN
//****************************************************************************
int main(int argc, char* argv[]){



    int err = parse_args_example(argc, argv);
    if(err) return err;

    cout << "Boost Version: " << rhd::boost_version() << endl;
    cout << endl;

    format_examples();
}
