#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
using namespace std;

namespace lockedin {
struct Document {
    string docID;
    string docTitle;
    string docPath;

    Document(string docID, string docTitle, string docPath) {  //, int frequency = 0) {
        this->docID = docID;
        this->docTitle = docTitle;
        this->docPath = docPath;
    }

    bool operator==(const Document& d) const {
        return docID == d.docID;
    }

    bool operator<(const Document& d) const {
        return docID < d.docID;
    }

    bool operator>(const Document& d) const {
        return docID > d.docID;
    }
};
}

#endif