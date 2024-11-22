#ifndef QueryProcessor_H
#define QueryProcessor_H

#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <algorithm>
#include "Document.h"
#include "IndexHandler.h"

class QueryProcessor{
public:
    QueryProcessor(IndexHandler*);
    
    // parses the user's query and returns a structured representation of the search conditions.
    vector<pair<lockedin::Document, int>> parseQuery(const std::string& query);

    float returnRuntime();
    
private:
    
        IndexHandler* indexHandler;
        float runtime;
};

#endif
