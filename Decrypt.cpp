#include <iostream>
#include <fstream>
#include <string>

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
    data = DecryptB64(data);

    return 0;
}