
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <boost/format.hpp>
#include <boost/program_options.hpp>

using namespace std;

namespace b = boost;

namespace po = b::program_options;

using fmt = b::format;

/// An example showing how to parse arguments from command line
int parse_args_example(int argc, char* argv[]){

    try{
        double opt;
        // These are basic options someone might want to know from the command
        // line
        po::options_description generic("Generic Options");
        generic.add_options()
            ("help,h", "provide help message")
            ("version,v", "print version")
            ;

        // These are actual configurations that the user can either input from
        // the command line or from the config file
        po::options_description config("Configuration");
        config.add_options()
            ("compression", po::value<int>(), "set compression level")
            ("tol", po::value<double>(&opt)->default_value(3.14), "set tolerance")
            ("include-path,I", po::value<vector<string>>(), "include path")
            ;

        // These will now show up in the help.
        po::options_description hidden("Hidden Options");
        hidden.add_options()
            ("input-file", po::value<vector<string>>(), "input file")
            ;


        // Now I can group these for various purposes 
        po::options_description cmdline_options;
        cmdline_options.add(generic).add(config).add(hidden);

        po::options_description config_file;
        config_file.add(config).add(hidden);

        po::options_description visible("Allowed Options");
        visible.add(generic).add(config);
        
        // Positional option so I don't have to have a flag for files
        po::positional_options_description p;
        p.add("input-file", -1);

        // Do the actual parsing
        po::variables_map vm;

        // This is the first store, these have higher priority than the config
        // file ones that I store next.
        po::store(po::command_line_parser(argc, argv).
                  options(cmdline_options).positional(p).run(), vm);

        // The command line options will be able to override these
        ifstream ifs("params.cfg");
        po::store(po::parse_config_file(ifs, config_file), vm);

        po::notify(vm);

        /**
         * Handle all the input here
         */
        if(vm.count("help") || argc == 1) {
            cout << "This is a program that does stuff. You can use it when\n"
                    "you are in need of doing stuff.\n";
                     
            cout << endl; 

            cout << visible << endl;

            cout << "I think this would be a good place to put Examples, and\n"
                    "... stuff" << endl;

            return 1;
        }

        if(vm.count("compression")) {
            stringstream ss;

            ss << fmt("Compression level: %5i") % 
                                vm["compression"].as<int>();

            cout << ss.str() << endl;
            cout << endl;
        }   

        if(vm.count("tol")) {
            stringstream ss;

            ss << fmt("tolerance: %2.2f") % 
                                vm["tol"].as<double>();

            cout << ss.str() << endl;
            cout << endl;
        }   

        if(vm.count("input-file")) {
            //Multiple input files

            cout << "Input files: ";
            for(auto i: vm["input-file"].as<vector<string>>())
                cout << i << " ";
            cout << endl;
            cout << endl;
        }   

    }catch(exception &e){
        cout << "Exception: " << e.what() << endl;
        return 1;
    }
}
int main(int argc, char * argv[]){

    if(parse_args_example(argc, argv))
        return 1;

}
