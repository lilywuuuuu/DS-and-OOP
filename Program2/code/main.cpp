#include <iostream>
#include <string>
#include <vector>


int main(int argc, const char* argv[]){
    std::vector<std::string> all_args;
    all_args.assign(argv, argv + argc); // convert command line argument to string 

    std::cout << "DSOO-Program2-Demo: ";
    for(auto a : all_args){
        std::cout << a << " ";
    }
    std::cout << "\n";
    
	

    
    if(argc != 2){
        std::cout << "part1\n";
    }else{
        std::string filename = argv[1];
        std::cout << "read file from : " << "test/" << filename << std::endl;
    }

    
    
    

    return 0;
}