#include "IndexHandler.h"

void IndexHandler::insertWord(string word, string docID, string docTitle, string docPath)
{
    lockedin::Document tempDocument(docID, docTitle, docPath);
    wordsAVL.insert(word, tempDocument);
    wordsAVL.get(word)[tempDocument]++;
}

void IndexHandler::insertOrg(string org, string docID, string docTitle, string docPath)
{
    lockedin::Document tempDocument(docID, docTitle, docPath);
    orgAVL.insert(org, tempDocument);
    orgAVL.get(org)[tempDocument]++;
}

void IndexHandler::insertPerson(string person, string docID, string docTitle, string docPath)
{
    lockedin::Document tempDocument(docID, docTitle, docPath);
    orgAVL.insert(person, tempDocument);
    orgAVL.get(person)[tempDocument]++;
}

void IndexHandler::writePersist()
{
    //START CHRONOS FOR WRITE TO PERSISTENT FILE STAT

    auto startWritePersistentStats = std::chrono::high_resolution_clock::now();

    ofstream wordsFile("words.txt");
    wordsAVL.writePersist(wordsFile);
    wordsFile.close();


    ofstream orgsFile("orgs.txt");
    orgAVL.writePersist(orgsFile);
    orgsFile.close();

    ofstream peopleFile("people.txt");
    personsAVL.writePersist(peopleFile);
    peopleFile.close();
    //STOP

    auto stopWritePersistentStats = std::chrono::high_resolution_clock::now();
    writeToRuntime = std::chrono::duration<float, std::milli>(stopWritePersistentStats - startWritePersistentStats).count();


}

void IndexHandler::readPersist()
{
    //START CHRONOS FOR READ FROM PERSISTENT FILE STAT
    auto startReadPersistentStats = std::chrono::high_resolution_clock::now();

    ifstream wordsFile("words.txt");
    string line;
    while(getline(wordsFile, line)){
        string key;
        key = line;
        map<lockedin::Document, int> mapValue;
        while(getline(wordsFile, line) && line != "-"){
            string docID = line;

            getline(wordsFile, line);
            string title = line;
            getline(wordsFile, line);
            string path = line;
            getline(wordsFile, line);
            int frequency = stoi(line);

            mapValue.emplace(lockedin::Document(docID, title, path), frequency);
        }

        wordsAVL.insert(key, mapValue);
    }
    wordsFile.close();

    ifstream orgsFile("orgs.txt");
    while(getline(orgsFile, line)){
        string key;
        key = line;
        map<lockedin::Document, int> mapValue;
        while(getline(orgsFile, line) && line != "-"){
            string docID = line;

            getline(orgsFile, line);
            string title = line;
            getline(orgsFile, line);
            string path = line;
            getline(orgsFile, line);
            int frequency = stoi(line);

            mapValue.emplace(lockedin::Document(docID, title, path), frequency);
        }

        orgAVL.insert(key, mapValue);
    }
    orgsFile.close();
    
    ifstream peopleFile("people.txt");
    while(getline(peopleFile, line)){
        string key;
        key = line;
        map<lockedin::Document, int> mapValue;
        while(getline(peopleFile, line) && line != "-"){
            string docID = line;

            getline(peopleFile, line);
            string title = line;
            getline(peopleFile, line);
            string path = line;
            getline(peopleFile, line);
            int frequency = stoi(line);

            mapValue.emplace(lockedin::Document(docID, title, path), frequency);
        }

        personsAVL.insert(key, mapValue);
    }
    peopleFile.close();

    auto stopReadPersistentStats = std::chrono::high_resolution_clock::now();
    readFromRuntime = std::chrono::duration<float, std::milli>(stopReadPersistentStats - startReadPersistentStats).count();



}

map<lockedin::Document, int>& IndexHandler::getWord(string term)
{
    return wordsAVL.get(term);
}

map<lockedin::Document, int>& IndexHandler::getOrg(string term)
{
    return orgAVL.get(term);
}

map<lockedin::Document, int>& IndexHandler::getPerson(string term)
{
    return personsAVL.get(term);
}

bool IndexHandler::containsWord(string term)
{
    return wordsAVL.contains(term);
}

bool IndexHandler::containsOrg(string term)
{
    return orgAVL.contains(term);
}

bool IndexHandler::containsPerson(string term)
{
    return personsAVL.contains(term);
}

float IndexHandler:: returnWriteToRuntime(){
    return writeToRuntime;
}

float IndexHandler:: returnReadFromRuntime(){
    return readFromRuntime;

}
