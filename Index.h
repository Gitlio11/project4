#include <string>
#include <vector>
#include <unordered_map>

#include "Document.h"
using namespace std;

struct Index {
    string word;
    unordered_map<string, lockedin::Document> docs;

    Index& operator=(const Index& i) {
        this->word = i.word;
        this->docs = i.docs;
        return *this;
    }

    bool operator==(const Index& i) const {
        return word == i.word;
    }

    bool operator<(const Index& i) const {
        return word < i.word;
    }

    bool operator>(const Index& i) const {
        return word > i.word;
    }
};