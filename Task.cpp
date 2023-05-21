#include "Task.hpp"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>



void SaveTasksToFile(const std::vector<Task>& tasks, const std:: string& fileName)
{     // ovdje prebacivamo iz vektor of objects into string
    std::ofstream ostream(fileName);  // of stream is nemed ostream
    ostream <<tasks.size();   //write number of tasks, in this case 3 to the file

    for(const Task& task : tasks) {  
        std::string description = task.description;  // Buy_Grocaries 1  (1- boolean), for each of them get description
    //    std::replace(description.begin(), description.end(), ' ','_');  //replace empty space -> in this case will be read as one string

        ostream << '\n' <<description << ' ' << task.done;  // write description mit space between ' ' i task.done

    }

}
 // This is a function that loads tasks from a file and returns a vector of Task objects.
// pass to file, turn it into vector of task-objects
                      // ovdje prebacivamo if string(file) u vector of objects
std::vector<Task>LoadTasksFromFile(const std::string& fileName)
{
    // if(!std::filesystem::exists(fileName)) {    // does file exist
    //     return std::vector<Task>();   // return empty vector

    // }
           // goal is to turn again into of vector of objects
    std::vector<Task> tasks;
    std::ifstream istream(fileName);  //ifstream => open file for reading

    int n;
    istream >> n;   //istream  : read int from  istream into "n" and store it.
    for(int i = 0; i < n; i++) {   //  reads the description and done status of each task from the file
        std::string description;
        bool done;

        istream >> description >> done;   //description no space_ easy to read, threated as one string
     //   std::replace (description.begin(), description.end(), '_', ' ');     -->     MOZA REPLACE WITH SOMETHING ELSE
        tasks.push_back(Task{description,done});  // object added to the tasks vector

    }

    return tasks;

}

