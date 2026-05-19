#ifndef GRAPHREADER_H
#define GRAPHREADER_H

#include <string>
#include <vector>
#include "Graph.h"


class GraphReader {
private:
    struct EdgeData {
        std::string origin;
        std::string target;
        size_t weight;
    };

    static std::vector<std::string> parseGraphLine(const std::string& line);


public:
    static Graph* readGraphFile(const std::string& filePath);
};

#endif // GRAPHREADER_H