#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include "IndexHandler.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"

class SearchEngine {
private:
    IndexHandler ih;
    DocumentParser dp;
    QueryProcessor qp;

    int printMenu();
    void printOpenDocMenu(vector<pair<lockedin::Document, int>>& results);

public:
    SearchEngine() : dp(&ih), qp(&ih) {}

    void initiateUI();
};

#endif

