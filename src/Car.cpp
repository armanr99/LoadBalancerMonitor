#include <utility>
#include <sstream>
#include "Car.hpp"
#include "Tools.hpp"
#include "constants.hpp"
using namespace std;

Car::Car(vector<char> _pathLocations, int _pathNumber)
{
    p = Tools::getRandomNumberInRange(P_BEGIN_RANGE, P_END_RANGE);
    pathNumber = _pathNumber;
    pathLocations = _pathLocations;
    currentLocationIndex = 0;
}

bool Car::hasReachedDestination()
{
    return (currentLocationIndex == pathLocations.size() - 1);
}

int Car::getPathNumber()
{
    return pathNumber;
}

PathEdgeInfo Car::getNextEdgeInfo()
{
    char currentLocation = pathLocations[currentLocationIndex];
    char nextLocation = pathLocations[currentLocationIndex + 1];
    PathEdgeInfo pathEdgeInfo = make_pair(currentLocation, nextLocation);

    return pathEdgeInfo;
}

void Car::moveFront()
{
    currentLocationIndex++;
}

long long Car::getEmission(int h)
{
    long long emission = 0;

    for(int k = 0; k <= 1e7; k++)
        emission += ((double)k / (double)(1e6 * p * h));

    return emission;
}