#include "Monitor.hpp"
using namespace std;

Monitor::Monitor(int conditionsCount)
{
	nextCount = 0;
    sem_init(&mutex, 0, 1);
	sem_init(&next,0, 0);
	initConditions(conditionsCount);
	states.push_back(OPEN_PATH);
}

void Monitor::initConditions(int conditionsCount)
{
    for(int i = 0; i < conditionsCount; i++)
    {
        Condition condition;
        sem_init(&condition.semaphor,0, 0);
        condition.count = 0;
        conditions.push_back(condition);
    }
}

void Monitor::wait(int i)
{
	conditions[i].count++;

	if(nextCount > 0)
		sem_post(&next);
	else
		sem_post(&mutex);
	
    sem_wait(&conditions[i].semaphor);
	conditions[i].count--;
}

void Monitor::signal(int i)
{
	if(conditions[i].count > 0)
	{
		nextCount++;

		sem_post(&conditions[i].semaphor);
		sem_wait(&next);

		nextCount--;
	}
}

void Monitor::enterCar()
{
	sem_wait(&mutex);
	
	if(states[0] == CLOSED_PATH)
		wait(0);

	states[0] = CLOSED_PATH;

	if(nextCount > 0)
		sem_post(&next);
	else
		sem_post(&mutex);
}

void Monitor::exitCar()
{
	sem_wait(&mutex);

	states[0] = OPEN_PATH;
	signal(0);

	if(nextCount > 0)
		sem_post(&next);
	else
		sem_post(&mutex);
}