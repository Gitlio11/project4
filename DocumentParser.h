#ifndef DocumentParser_H
#define DocumentParser_H

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_set>

#include "IndexHandler.h"
#include "porter2_stemmer.h"
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;
namespace fs = std::filesystem;

class DocumentParser {
   private:
        IndexHandler* indexHandler;
        float runtime;
   public:
    DocumentParser(IndexHandler*);

    void parse(string directoryName);

    float returnRuntime();
    
};

#endif