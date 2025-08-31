#ifndef BENCMARK_HPP
#define BENCMARK_HPP

#include <iostream>
#include <ctime>
#include <string>
#include <vector>

clock_t start;
int task_id = -1;
std::vector<std::vector<std::string>> results;
inline std::string currect_area = "task_id: " + std::to_string(task_id);

void initBenchmark()
{
    start = clock();
}

void startArea(const std::string& name_area = "")
{
    task_id += 1;
    if(name_area.length() > 0){
        currect_area = name_area + " (task_id=" + std::to_string(task_id) + ")";
    }else{
        currect_area = "task_id=" + std::to_string(task_id);
    }
    
}

void closeArea()
{

}

void endBenckmark(const std::string& file_name)
{
    /* save to file */
}

#endif
