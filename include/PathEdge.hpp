#ifndef _PATH_EDGE_H_
#define _PATH_EDGE_H

#include "Monitor.hpp"

class PathEdge
{
public:
    PathEdge(int _h);
    int getH();
    void enterCar();
    void exitCar();

private:
    int h;
    Monitor* monitor;
};

#endif