#include <string>
#include "TrafficHandler.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    string inputFilePath = argv[1];

    TrafficHandler trafficHandler;
    trafficHandler.start(inputFilePath);

    return 0;
}