#include "PathEdge.hpp"
using namespace std;

PathEdge::PathEdge(int _h)
{
    h = _h;
    monitor = new Monitor(1);
}

int PathEdge::getH()
{
    return h;
}

void PathEdge::enterCar()
{
    monitor->enterCar();
}

void PathEdge::exitCar()
{
    monitor->exitCar();
}