#include "Task.hpp"

Task::Task(int id, int arrival, int duration)
{
    this->id = id;
    this->arrival = arrival;
    this->duration = duration;
    this->end = -1;
    this->inQueue = false;
}

TaskScheduler::TaskScheduler(int quantum, std::vector<Task *> tasks)
{
    this->quantum = quantum;
    this->tasksWaiting = tasks;
}

void TaskScheduler::displayResult(std::vector<Task *> initialTasks)
{
    this->RoundRobin();
    for (auto const &tsk : initialTasks)
    {
        if (tsk->inQueue)
            throw - 1;
        printf("Task %d, Duration: [%d,%d]\n", tsk->id, tsk->arrival, tsk->end);
    }
}

void TaskScheduler::RoundRobin()
{
    int elapsed = 0;
    this->checkIncomingTasks(0);
    while (!this->schedulerQueue.empty())
    {
        Task *t = this->schedulerQueue.front();
        for (int limit = 0; limit < quantum; limit++)
        {
            elapsed++;
            this->checkIncomingTasks(elapsed);
            t->duration--;
            if (t->duration == 0)
            {
                break;
            }
        }
        if (t->duration == 0)
        {
            t->end = elapsed;
            t->inQueue = false;
        }
        else
        {
            this->schedulerQueue.push(t);
        }
        this->schedulerQueue.pop();
    }
}

void TaskScheduler::checkIncomingTasks(int moment)
{
    for (auto const &t : this->tasksWaiting)
        if (t->arrival == moment)
        {
            t->inQueue = true;
            this->schedulerQueue.push(t);
        }
}