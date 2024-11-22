#include "QueryProcessor.h"
#include "porter2_stemmer.h"

QueryProcessor::QueryProcessor(IndexHandler * ih)
{
    indexHandler=ih;
    runtime = 0.0;
}

vector<pair<lockedin::Document, int>> QueryProcessor::parseQuery(const std::string &query)
{
    //START CHRONOS FOR PARSE QUERY STAT
    auto startParseQueryStats = std::chrono::high_resolution_clock::now();


    vector<string> wordTokens;
    vector<string> orgTokens;
    vector<string> peopleTokens;
    vector<string> notWordTokens;
    vector<string> notOrgTokens;
    vector<string> notPeopleTokens;

    stringstream queryStream(query);
    string token;
    while(queryStream>>token){
        bool isPerson = false;
        bool isOrg = false;
        bool isWord = false;
        if(token.substr(0, 7)== "PERSON:"){
            isPerson = true;
            token = token.substr(7);
        }
        else if(token.substr(0, 4)== "ORG:"){
            isOrg = true;
            token = token.substr(4);
        } 
        else {
            isWord = true;
        }

        bool isNot = false;
        if (token.empty() == false && token[0] == '-') {
            token = token.substr(1);
            isNot = true;
        }

           for(int i =0; i < token.size(); i++){
            token[i] = tolower(token[i]);
           }

        if(isPerson == true){

            if(isNot==true){
                notPeopleTokens.push_back(token);
            }
            else {
                peopleTokens.push_back(token);
            }
        }




        if(isOrg == true){

            if(isNot==true){
                notOrgTokens.push_back(token);
            }
            else {
                orgTokens.push_back(token);
            }
        }

        if(isWord == true){
            Porter2Stemmer::stem(token);
            if(isNot==true){
                notWordTokens.push_back(token);
            }
            else {
                wordTokens.push_back(token);
            }
        }

        
   }

    map<lockedin::Document, int> results;

    for(string word: wordTokens) {
        if (indexHandler->containsWord(word)){
            if (results.empty()) {
                results = indexHandler->getWord(word);
                continue;
            }
            for (auto& doc: indexHandler->getWord(word)) {
                if (results.count(doc.first)) {
                    results[doc.first] += doc.second;
                } else {
                    results.erase(doc.first);
                }
            }
        }
    }

    for(string word: orgTokens) {
        if (indexHandler->containsOrg(word)){
            if (results.empty()) {
                results = indexHandler->getOrg(word);
                continue;
            }
            for (auto& doc: indexHandler->getOrg(word)) {
                if (results.count(doc.first)) {
                    results[doc.first] += doc.second;
                } else {
                    results.erase(doc.first);
                }
            }
        }
    }

    for(string word: peopleTokens) {
        if (indexHandler->containsPerson(word)){
            if (results.empty()) {
                results = indexHandler->getPerson(word);
                continue;
            }
            for (auto& doc: indexHandler->getPerson(word)) {
                if (results.count(doc.first)) {
                    results[doc.first] += doc.second;
                } else {
                    results.erase(doc.first);
                }
            }
        }
    }


    for(string word: notWordTokens) {
        if (indexHandler->containsWord(word)){
            for (auto& doc: indexHandler->getWord(word)) {
                results.erase(doc.first);
            }
        }
    }

    for(string org: notOrgTokens) {
        if (indexHandler->containsOrg(org)){
            for (auto& doc: indexHandler->getOrg(org)) {
                results.erase(doc.first);
            }
        }
    }

    for(string person: notPeopleTokens) {
        if (indexHandler->containsPerson(person)){
            for (auto& doc: indexHandler->getPerson(person)) {
                results.erase(doc.first);
            }
        }
    }

    auto stopParseQueryStats = std::chrono::high_resolution_clock::now();
    runtime = std::chrono::duration<float, std::milli>(stopParseQueryStats - startParseQueryStats).count();


    vector<pair<lockedin::Document, int>> finalResults(results.begin(), results.end());
    sort(finalResults.rbegin(), finalResults.rend());
    return finalResults;

    


}

float QueryProcessor:: returnRuntime(){
    return runtime;
}