#include "SearchEngine.h"
#include "rapidjson/istreamwrapper.h"

int SearchEngine::printMenu() {
    if (ih.isEmpty()) {
        cout << "1) Read in index from file path" << endl;
        cout << "2) Read in index from persistence file" << endl;
        cout << "3) Quit program" << endl;
    } else {
        cout << "1) Enter a query" << endl;
        cout << "2) Write to persistence file" << endl;
        cout << "3) Print stats" << endl;
        cout << "4) Clear index" << endl;
        cout << "5) Quit program" << endl;
    }
    string input;
    cin >> input;
    while (input.empty() || !isdigit(input[0]) || input[0] == '0' || (ih.isEmpty() ? input[0] > '3' : input[0] > '5')) {
        cout << "Input was invalid" << endl;
        cin >> input;
    }

    return input[0] - '0';
}

void SearchEngine::printOpenDocMenu(vector<pair<lockedin::Document, int>>& results) {
    while (true) {
        cout << "Enter E if you want to exit. Enter a number if you want to view a document." << endl;

        string input;
        cin >> input;

        if (!input.empty() && (input[0] == 'E' || input[0] == 'e')) {
            break;
        }

        if (input.empty() || !isdigit(input[0]) || input[0] == '0') {
            cout << "Input was invalid" << endl;
            continue;
        }

        int index = stoi(input) - 1;
        cout << results[index].first.docTitle << endl;

        ifstream inputFile;
        inputFile.open(results[index].first.docPath);

        rapidjson::Document doc;
        IStreamWrapper isw(inputFile);
        doc.ParseStream(isw);

        cout << doc["text"].GetString() << endl;
    }
}

void SearchEngine::initiateUI() {
    bool wantsToQuit = false;
    while (!wantsToQuit) {
        int input = printMenu();
        if (ih.isEmpty()) {
            switch (input) {
                case 1: {
                    string path;
                    cout << "Enter a directory" << endl;
                    cin >> path;
                    dp.parse(path);
                    break;
                }
                case 2: {
                    ih.readPersist();
                    break;
                }
                case 3: {
                    wantsToQuit = true;
                    break;
                }
                default:
                    break;
            }
        } else {
            switch (input) {
                case 1: {
                    string query;
                    cout << "Enter a query" << endl;
                    cin >> query;
                    auto results = qp.parseQuery(query);
                    int i = 0;
                    for (auto& result : results) {
                        i++;
                        cout << i << ") " << result.first.docTitle << endl;
                        if (i == 15) {
                            break;
                        }
                    }
                    printOpenDocMenu(results);
                    break;
                }
                case 2: {
                    ih.writePersist();
                    break;
                }
                case 3: {
                    cout << "The Query Processor took: " << qp.returnRuntime() << " milliseconds." << endl;
                    cout << "The Write to Persistence File took: " << ih.returnWriteToRuntime() << " milliseconds." << endl;
                    cout << "The Document Parser took: " << dp.returnRuntime() << " milliseconds." << endl;
                    break;
                }
                case 4: {
                    ih.clearIndex();
                    break;
                }
                case 5: {
                    wantsToQuit = true;
                    break;
                }
                default:
                    break;
            }
        }
    }
}
