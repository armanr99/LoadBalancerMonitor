#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <vector>
#include <string>

class Tools
{
public:
    static std::vector<std::string> readFile(std::string filePath);
    static std::vector<std::string> splitByChar(std::string word, char separator);
    static std::string removeSpaces(std::string input);
    static std::vector<char> convertToChars(const std::vector<std::string> &input);
    static int getRandomNumberInRange(int beginRange, int endRange);
    static int64_t getEpochTime();
};

#endif