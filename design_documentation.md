# Design Documentation
Below will give a brief description of each of the classes and its key functions.
## Classes
### DocumentParser
- Handles parsing of JSON files containing news articles. Extracts metadata entities (persons, organizations), and the article text for indexing.
- Attributes:
  - `indexHandler`: A pointer to an IndexHandler object, which manages the insertion data into the index.
  - `runtime`: Tracks the time taken to parse all files in a given directy.
- Functions:
  - `DocumentParser(IndexHandler* ih)`: Constructor that initializes the DocumentParser object with a reference to an IndexHandler.
  - `parse(string directoryName)`: Processes all .json files in the given directory and extracts data for indexing.
  - `returnRuntime()`: Returns the runtime of the parse function.
- Dependencies:
  - rapidjson
  - IndexHandler
  - Porter2Stemmer
  - filesystem (fs)

### IndexHandler
- Manages the creation, retrieval, and persistence of indices for words, organizations, and persons using AVL trees.
- Attributes:
  - `wordsAVL`, `orgAVL`, `personsAVL`: AVL trees that store words, organizations, and persons with associated documents and frequencies.
  - `writeToRuntime`: Tracks the time taken to save indices to persistent storage.
  - `readFromRuntime`: Tracks the time taken to load indices from persistent storage.
- Functions:
  - `insertWord(string word, string docID, string docTitle, string docPath)`: Inserts a word into the word index.
  - `insertOrg(string org, string docID, string docTitle, string docPath)`: Inserts an organization into the organization index.
  - `insertPerson(string person, string docID, string docTitle, string docPath)`: Inserts a person into the person index.
  - `writePersist()`: Saves all indices (words, organizations, persons) to files (words.txt, orgs.txt, people.txt).
  - `readPersist()`: Loads indices from files and reconstructs AVL trees.
  - `getWord(string term)`, `getOrg(string term)`, `getPerson(string term)`: Retrieves the documents and frequencies for a specific word, organization, or person.
  - `containsWord(string term)`, `containsOrg(string term)`, `containsPerson(string term)`: Checks if a specific term exists in the corresponding index.
  - `returnWriteToRuntime()`: Returns the runtime of the writePersist function.
  - `returnReadFromRuntime()`: Returns the runtime of the readPersist function.
- Dependencies:
  - lockedin::Document
  - AVL tree implementation.
  - fstream
 
### QueryProcessor
- Handles parsing and execution of user queries to retrieve relevant documents from indices.
- Attributes:
  - `indexHandler`: A pointer to an `IndexHandler` object for accessing the word, organization, and person indices.
  - `runtime`: Tracks the time taken to parse and process a query.
- Functions:
  - `QueryProcessor(IndexHandler* ih)`: Constructor that initializes the QueryProcessor object with a reference to an IndexHandler.
  - `parseQuery(const string& query)`: Processes a user query string, applies logical operators (e.g., AND, NOT), and retrieves matching documents from indices.
  - `returnRuntime()`: Returns the runtime of the query processing function.
- Dependencies:
  - IndexHandler
  - Porter2Stemmer
  - sstream (standard libraries for string manipulation)
 
### SearchEngine
- Manages the user interface (UI) and coordinates the overall operation of the search engine, including querying, indexing, and persistence.
- Attributes:
  - `ih`: An instance of IndexHandler for managing indices.
  - `qp`: An instance of QueryProcessor for processing and executing user queries.
  - `dp`: An instance of DocumentParser for parsing and indexing new documents.
- Functions:
  - `printMenu()`: Displays the appropriate menu options based on whether the index is empty and retrieves user input.
  - `printOpenDocMenu(vector<pair<lockedin::Document, int>>& results)`: Allows users to view document contents or exit the detailed document menu.
  - `initiateUI()`: Main UI loop that interprets user inputs and executes corresponding actions (e.g., querying, indexing, viewing stats, writing to persistence).
- Dependencies:
  - IndexHandler
  - QueryProcessor
  - DocumentParser
  - rapidjson
  - iostream, fstream, string

### Porter2Stemmer
- Implements the Porter2 stemming algorithm, which reduces words to their root forms for more consistent indexing and searching.
- Attributes:
  - Internal Functions: Utility functions to handle specific steps of the algorithm (e.g., step0, step1A, etc.).
- Functions:
  - `stem(std::string& word)`: Applies the full Porter2 stemming process to a given word, including handling exceptions, reducing suffixes, and adjusting the word's structure.
  - `trim(std::string& word)`: Converts a word to lowercase and removes invalid characters.
  - `getStartR1(const std::string& word)`: Calculates the R1 region of the word (the first region after the first non-vowel following a vowel).
  - `getStartR2(const std::string& word, size_t startR1)`: Calculates the R2 region, which starts after the first non-vowel following a vowel in the R1 region.
  - `step0(std::string& word)`: Handles possessives and contractions.
  - `step1A/B/C(std::string& word, size_t startR1)`: Deals with common suffixes (e.g., sses, ied, ing) and adjusts the word accordingly.
  - `step2/3/4/5(std::string& word, size_t startR1, size_t startR2)`: Applies further suffix reductions based on predefined rules and regions.
  - `isVowel(char ch), isVowelY(char ch)`: Determines if a character is a vowel (including y in certain contexts).
  - `containsVowel(const std::string& word, size_t start, size_t end)`: Checks if a substring contains a vowel.
  - `replaceIfExists(std::string& word, const std::string& suffix, const std::string& replacement, size_t start)`: Replaces a suffix with a new string if it exists within the given region.
  - `isShort(const std::string& word)`: Determines if the word ends with a "short syllable."
  - `endsWith(const std::string& word, const std::string& str)`: Checks if a word ends with a specific string.
  - `endsInDouble(const std::string& word)`: Checks if a word ends with a double consonant.
  - `isValidLIEnding(char ch)`: Validates if a character is a valid li ending
- Dependencies:
  - algorithm
  - utility
  - unordered_map
  - string
  - sstream
