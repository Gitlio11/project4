#ifndef IndexHandler_H
#define IndexHandler_H

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include <chrono>

#include "AvlTree.h"
#include "Document.h"
#include "HashTable.h"
#include "Index.h"

using namespace std;

class IndexHandler {
   private:
    AvlTree<string, lockedin::Document> wordsAVL;
    AvlTree<string, lockedin::Document> personsAVL;
    AvlTree<string, lockedin::Document> orgAVL;

    float writeToRuntime;
    float readFromRuntime;

   public:
    IndexHandler() {

    writeToRuntime = 0.0;
    readFromRuntime = 0.0;

    };

    void insertWord(string, string, string, string);
    void insertOrg(string, string, string, string);
    void insertPerson(string, string, string, string);
    void writePersist();
    void readPersist();

    map<lockedin::Document, int>& getWord(string);
    map<lockedin::Document, int>& getOrg(string);
    map<lockedin::Document, int>& getPerson(string);
    bool containsWord(string);
    bool containsOrg(string);
    bool containsPerson(string);

    bool isEmpty() {
        return wordsAVL.isEmpty() && personsAVL.isEmpty() && orgAVL.isEmpty();
    }
    
    void clearIndex() {
        wordsAVL.makeEmpty();
        personsAVL.makeEmpty();
        orgAVL.makeEmpty();
    }

    float returnWriteToRuntime();
    float returnReadFromRuntime();


};
#endif