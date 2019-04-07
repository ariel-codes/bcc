#include <iostream>
#include <vector>
#include "Task.hpp"

using namespace std;

bool sortTasks(Task *t1, Task *t2)
{
    if (t1->arrival < t2->arrival)
        return true;
    else if (t1->arrival == t2->arrival)
    {
        if (t1->id < t2->id)
            return true;
        else
            return false;
    }
    else
        return false;
}

int main(int argc, char const *argv[])
{
    int quantum, taskNum;
    cin >> quantum >> taskNum;
    vector<Task *> taskList;
    taskList.reserve(taskNum * sizeof(Task *));

    for (int i = 0; i < taskNum; i++)
    {
        int id, arrival, duration;
        cin >> id >> arrival >> duration;
        Task *task = new Task(id, arrival, duration);
        taskList.push_back(task);
    }

    std::sort(taskList.begin(), taskList.end(), sortTasks);

    TaskScheduler *scheduler = new TaskScheduler(quantum, taskList);
    scheduler->displayResult(taskList);

    for (auto const &tk : taskList)
        delete tk;
    delete scheduler;

    return 0;
}
