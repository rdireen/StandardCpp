
#pragma once

#include <string>
#include <sstream>
#include <boost/version.hpp>

namespace rhd{

std::string boost_version(){
    std::stringstream ss;
     ss  << BOOST_VERSION /100000 << "."
         << BOOST_VERSION /100 % 1000 << "."
         << BOOST_VERSION % 100 << ".";
    return  ss.str();
}

}
