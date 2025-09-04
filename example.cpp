#include "benchmark.hpp"
#include <iostream>

int main()
{
    std::cout << current_area << std::endl;

    startArea("function a");
    for(int i=0; i<1000000000; i++);
    closeArea();
    endBenchmark("file.csv");
    
    std::cout << current_area << std::endl;

    return 0;
}