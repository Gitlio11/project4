#include "DocumentParser.h"
#include "rapidjson/istreamwrapper.h"

#include "IndexHandler.h"

DocumentParser::DocumentParser(IndexHandler* ih)
{
    indexHandler=ih;
    runtime = 0.0;
}

void DocumentParser::parse(string directoryName)
{

    //START CHRONOS FOR DOC PARSER STAT
    auto startDocParserStats = std::chrono::high_resolution_clock::now();

    // reads every file and puts it on a single string
    for (const auto& entry : fs::recursive_directory_iterator(directoryName)) {
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                // Open current file
                ifstream inputFile;
                inputFile.open(entry.path().c_str());

                rapidjson::Document doc;
                IStreamWrapper isw(inputFile);
                doc.ParseStream(isw);

                string title = doc["title"].GetString();
                string docID = doc["uuid"].GetString();

                
                for (auto& v : doc["entities"]["persons"].GetArray()) {
                    string s = v["name"].GetString();

                    for (int i = 0; i < s.length(); i++) {
                        s[i] = tolower(s[i]);
                    }

                    std::replace(s.begin(), s.end(), ' ', '_');
                   indexHandler->insertPerson(s, docID, title, entry.path().string());
                }

                for (auto& v : doc["entities"]["organizations"].GetArray()) {
                    string s = v["name"].GetString();

                    for (int i = 0; i < s.length(); i++) {
                        s[i] = tolower(s[i]);
                    }

                    std::replace(s.begin(), s.end(), ' ', '_');
                    indexHandler->insertPerson(s, docID, title, entry.path().string());
                }

                string text = doc["text"].GetString();
                for (int i = 0; i < text.length(); i++) {
                    text[i] = tolower(text[i]);
                }
                
                stringstream textStream(text);
                string s;
                while(textStream>>s){
                    int j = 0;
                    for(int i = 0; i < s.length(); i++){
                        s[j] = s[i];
                        if (isalpha(s[j])){
                            ++j;
                        }
                    }
                    s.resize(j);
                    Porter2Stemmer::stem(s);
                    indexHandler->insertPerson(s, docID, title, entry.path().string());
                }
            }
        }
    }

    auto stopDocParserStats = std::chrono::high_resolution_clock::now();
    runtime = std::chrono::duration<float, std::milli>(stopDocParserStats - startDocParserStats).count();


}

float DocumentParser:: returnRuntime(){
    return runtime;
}