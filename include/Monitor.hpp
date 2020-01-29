#ifndef _MONITOR_H_
#define _MONITOR_H_

#include <vector>
#include <semaphore.h>

typedef struct
{
	sem_t semaphor;
	int count;
} Condition;

enum State {OPEN_PATH, CLOSED_PATH};

class Monitor
{
public:
    Monitor(int conditionsCount);
    void enterCar();
    void exitCar();

private:
    sem_t mutex;
    sem_t next;
    int nextCount;
    std::vector<Condition> conditions;
    std::vector<State> states;

    void initConditions(int conditionsCount);
    void wait(int i);
    void signal(int i);
    void test(int i);
};

#endif