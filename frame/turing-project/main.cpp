#include <iostream>
#include "TM.h"
using namespace std;

int main(int argc, char* argv[]){
    if(argc == 2)
    {
        string option = argv[1];
        if(option == "-h" || option == "--help")
        {
            cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>";
            return 1;
        }
        else
        {
            cerr << "syntax error";
            std::exit(EXIT_FAILURE);
        }
    }
    else if(argc == 3)
    {
        string filename = argv[1];
        string input = argv[2];
        TM tm(filename);
        //init TM and tape
        if(!tm.initTape(input))  
        {
            std::exit(EXIT_FAILURE);
        }
        while(tm.transfer());
        if(tm.isAccept())
        {
            cout << "(ACCEPT) ";
            tm.printFirstTape();
        }
        else
        {
            cout << "(UNACCEPT) ";
            tm.printFirstTape();
        }
    }
    else if(argc == 4)
    {
        string verbose = argv[1];
        string filename = argv[2];
        string input = argv[3];
        if(verbose != "-v" && verbose != "--verbose")
        {
            cerr << "Wrong argument, use \"-h\" or \"--help\" to check";
            std::exit(EXIT_FAILURE);
        }
        TM tm(filename, true);
        //init TM and tape
        //in verbose mode, error msg should print in tm's func
        if(!tm.initTape(input))  
        {
            std::exit(EXIT_FAILURE);
        }
        while(tm.transfer());
        if(tm.isAccept())
        {
            cout << "ACCEPTED" << endl;
            cout << "Result: ";
            tm.printFirstTape();
            cout << endl << "==================== END ====================";
        }
        else
        {
            cout << "UNACCEPTED" << endl;
            cout << "Result: ";
            tm.printFirstTape();
            cout << endl << "==================== END ====================";

        }
    }
    else
    {
        cerr << "illegal input string";
        std::exit(EXIT_FAILURE);
    }
    return 1;
}