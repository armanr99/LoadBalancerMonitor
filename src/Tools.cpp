#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include "Tools.hpp"
using namespace std;

vector<string> Tools::readFile(string filePath)
{
    ifstream file(filePath);
    
    string line;
    vector<string> lines;

    while (getline(file, line))
        lines.push_back(line);

    return lines;
}

vector<string> Tools::splitByChar(string word, char separator)
{
    vector<string> result;
    stringstream ss(word);

    string str;

    while (getline(ss, str, separator))
        result.push_back(str);

    return result;
}

string Tools::removeSpaces(string input)
{
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    return input;
}

vector<char> Tools::convertToChars(const vector<string> &input)
{
    vector<char> result;

    for(int i = 0; i < input.size(); i++)
        result.push_back(input[i][0]);

    return result; 
}

int Tools::getRandomNumberInRange(int beginRange, int endRange)
{
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(beginRange, endRange);

    return distr(eng);
}

int64_t Tools::getEpochTime()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );

    return ms.count();
}