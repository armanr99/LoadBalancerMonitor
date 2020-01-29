#ifndef _TRAFFIC_HANDLER_H_
#define _TRAFFIC_HANDLER_H_

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <semaphore.h>
#include "Car.hpp"
#include "PathEdge.hpp"
#include "constants.hpp"

class TrafficHandler
{
public:
    TrafficHandler();
    void start(std::string inputFilePath);

private:
    static sem_t totalEmissionMutex;
    static long long totalEmission;
    static std::vector<Car*> cars;
    static std::map<PathEdgeInfo, PathEdge*> paths;

    void readInput(std::string inputFilePath);
    void parseInput(const std::vector<std::string> &fileLines);
    void parsePathInput(std::string fileLine);
    void parseCarInput(std::string fileLine1, std::string fileLine2, int pathNumber);
    void moveCars();

    static void* moveCar(void* carIndex);
    static std::string getLog(PathEdgeInfo edgeInfo, int64_t entranceTime, int64_t exitTime, long long carEmission, long long currentEmission);
    static void writeLogFile(int pathNumber, int carNumber, PathEdgeInfo edgeInfo, int64_t entranceTime, int64_t exitTime, long long carEmission, long long currentEmission);
    static std::string getFilePath(int pathNumber, int carNumber);
};

#endif