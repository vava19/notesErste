#include <string>
#include <vector>

struct Task  // needed * public
{
    std::string description;
    bool done;
};
// need to save Tasks to file -> that can be loaded at start up

void SaveTasksToFile(const std::vector<Task>& tasks, const std:: string& fileName);


// loading function shoud return a vactor of tasks
std::vector<Task>LoadTasksFromFile(const std::string& fileName);



