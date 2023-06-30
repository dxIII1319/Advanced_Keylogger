#include <iostream>
#include <fstream>
#include <string>
#include "Base64.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        std::cout<<"Wrong number of arguments\nNeed two arguments: Input File and Output file.\n";
        return 2;
    }
    std::string in (argv[1]), out (argv[2]);
    std::ifstream fi (in);
    if(!fi)
    {
        std::cout<<"Cannot read the given file "<<in<<std::endl;
        return 3;
    }
    std::string data;
    fi>>data;
    if(!fi)
    {
        std::cout << "Input file "<<in<<" is corrupted\n";
        return 4;
    }
    data = Base64::DecryptB64(data);
    std::ofstream fo (out);
    if(!fo)
    {
        std::cout<<"Cannot access/write output in the given out file\n";
        return 5;
    }
    fo<<data;
    std::cout<<"Decoding was successfull"<<std::endl;
    return 0;
}
