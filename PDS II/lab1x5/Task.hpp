#ifndef TASK_H
#define TASK_H

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

struct Task
{
	int id;
	int arrival;
	int duration;
	int end;
	bool inQueue;
	Task(int, int, int);
};

struct TaskScheduler
{
	int quantum;
	std::queue<Task *> schedulerQueue;
	std::vector<Task *> tasksWaiting;
	TaskScheduler(int, std::vector<Task *>);
	void RoundRobin();
	void checkIncomingTasks(int);
	void displayResult(std::vector<Task *>);
};

#endif