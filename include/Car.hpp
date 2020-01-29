#ifndef _CAR_H_
#define _CAR_H_

#include <vector>
#include "constants.hpp"

class Car
{
public:
    Car(std::vector<char> _pathLocations, int _pathNumber);
    bool hasReachedDestination();
    PathEdgeInfo getNextEdgeInfo();
    void moveFront();
    long long getEmission(int h);
    int getPathNumber();

private:
    int p;
    int currentLocationIndex;
    int pathNumber;
    std::vector<char> pathLocations;
};

#endif