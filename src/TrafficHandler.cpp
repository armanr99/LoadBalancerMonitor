#include <pthread.h>
#include <cstdlib>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include "TrafficHandler.hpp"
#include "Tools.hpp"
using namespace std;

sem_t TrafficHandler::totalEmissionMutex;
long long TrafficHandler::totalEmission;
vector<Car*> TrafficHandler::cars;
map<PathEdgeInfo, PathEdge*> TrafficHandler::paths;

TrafficHandler::TrafficHandler()
{
    totalEmission = 0;
    sem_init(&totalEmissionMutex, 0, 1);
}

void TrafficHandler::start(string inputFilePath)
{
    readInput(inputFilePath);
    moveCars();
}

void TrafficHandler::readInput(std::string inputFilePath)
{
    vector<string> fileLines = Tools::readFile(inputFilePath);
    parseInput(fileLines);
}

void TrafficHandler::parseInput(const std::vector<std::string> &fileLines)
{
    int pathNumber = 0;
    bool firstSectionParsed = false;

    for(int i = 0; i < fileLines.size(); i++)
    {
        if(fileLines[i] == INPUT_SECTION_SEPARATOR)
            firstSectionParsed = true;
        else if(!firstSectionParsed)
            parsePathInput(fileLines[i]);
        else
        {
            parseCarInput(fileLines[i], fileLines[i + 1], pathNumber++);
            i++;
        }
    }
}

void TrafficHandler::parsePathInput(std::string fileLine)
{
    string lineWithoutSpace = Tools::removeSpaces(fileLine);
    vector<string> splittedLine = Tools::splitByChar(lineWithoutSpace, INPUT_SEPARATOR);

    char source = splittedLine[0][0];
    char destination = splittedLine[1][0];
    int h = stoi(splittedLine[2]);

    PathEdgeInfo pathEdgeInfo = make_pair(source, destination);
    paths[pathEdgeInfo] = new PathEdge(h);
}

void TrafficHandler::parseCarInput(std::string fileLine1, std::string fileLine2, int pathNumber)
{
    string firstLineWithoutSpace = Tools::removeSpaces(fileLine1);
    vector<string> splittedFirstLine = Tools::splitByChar(firstLineWithoutSpace, INPUT_SEPARATOR);

    int carsCount = stoi(fileLine2);
    vector<char> carPathLocations = Tools::convertToChars(splittedFirstLine);

    for(int i = 0; i < carsCount; i++)
        cars.push_back(new Car(carPathLocations, pathNumber));
}

void TrafficHandler::moveCars()
{
    int indexes[cars.size()];

    pthread_t threads[cars.size()];
	pthread_attr_t attr;

	pthread_attr_init(&attr);

    for (int i = 0; i < cars.size(); i++)
    {
        indexes[i] = i;
        pthread_create(&threads[i], NULL, moveCar, (int*)&indexes[i]);
    }
    
	for (int i = 0; i < cars.size(); i++)
		pthread_join(threads[i], NULL);
}

void* TrafficHandler::moveCar(void* carIndexPtr)
{
    int carIndex = *(int*)carIndexPtr;

    while(!cars[carIndex]->hasReachedDestination())
    {
        PathEdgeInfo nextEdgeInfo = cars[carIndex]->getNextEdgeInfo();
        
        paths[nextEdgeInfo]->enterCar();

        int64_t entranceTime = Tools::getEpochTime();
        int pathH = paths[nextEdgeInfo]->getH();
        long long carEmission = cars[carIndex]->getEmission(pathH);

        sem_wait(&totalEmissionMutex);
        totalEmission += carEmission;
        long long currentEmission = totalEmission;
        sem_post(&totalEmissionMutex);

        cars[carIndex]->moveFront();

        int64_t exitTime = Tools::getEpochTime();
        int pathNumber = cars[carIndex]->getPathNumber();
        
        writeLogFile(pathNumber, carIndex, nextEdgeInfo, entranceTime, exitTime, carEmission, currentEmission);

        paths[nextEdgeInfo]->exitCar();
    }

    pthread_exit(NULL);
}

string TrafficHandler::getFilePath(int pathNumber, int carNumber)
{
    string fileName = OUTPUT_DIR;
    fileName += to_string(pathNumber);
    fileName += OUTPUT_FILE_SEPARATOR;
    fileName += to_string(carNumber);

    return fileName;
}

string TrafficHandler::getLog(PathEdgeInfo edgeInfo, int64_t entranceTime, int64_t exitTime, long long carEmission, long long currentEmission)
{
    ostringstream logSS;

    logSS << edgeInfo.first;
    logSS << OUTPUT_SEPARATOR;
    logSS << entranceTime;
    logSS << OUTPUT_SEPARATOR;
    logSS << edgeInfo.second;
    logSS << OUTPUT_SEPARATOR;
    logSS << exitTime;
    logSS << OUTPUT_SEPARATOR;
    logSS << carEmission;
    logSS << OUTPUT_SEPARATOR;
    logSS << currentEmission;

    return logSS.str();
}

void TrafficHandler::writeLogFile(int pathNumber, int carNumber, PathEdgeInfo edgeInfo, int64_t entranceTime, int64_t exitTime, long long carEmission, long long currentEmission)
{
    string filePath = getFilePath(pathNumber, carNumber);

    fstream fs;
    fs.open(filePath, std::ios::out | std::ios::app);

    string log = getLog(edgeInfo, entranceTime, exitTime, carEmission, currentEmission);
    log += '\n';

    cout << log;

    fs << log;

    fs.close();
}