# Assignment 4: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Names of all team members:  Emilio Munoz, Tiffany Nguyen, Antonio Flores, Jocelin Macias, Pierre Martinez


Used free extension: [ ] 24 hrs or [ ] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## Answers

### Project Management

Complete the tasks and planned completion columns **BEFORE** You start with 
coding!


Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

| Task        | Planned completion | Actual completion | Time spent in hrs by X | Time spent in hrs by Y |
| ----------- | :-----------------:| :---------------: | :--------------------: | :--------------------: |
| x           | Nov 3              | Nov 6             | 8.5                    | 0      
Design high-level architecture (UML, pseudocode), Nov 10, Nov 10, 3.0, 2.0
Implement DocumentParser class, Nov 11, Nov 12, 4.5, 5.0
Develop IndexHandler class, Nov 12, Nov 13, 5.0, 4.5
QueryProcessor Implementation, Nov 13, Nov 14, 6.0, 5.5
Test and Debug DocumentParser, Nov 14, Nov 15, 3.5, 3.0
Test and Debug IndexHandler, Nov 15, Nov 15, 3.0, 2.5
Integrate QueryProcessor with IndexHandler, Nov 16, Nov 16, 4.0, 3.5
Develop User Interface (SearchEngine class), Nov 17, Nov 18, 4.5, 4.0
Test Integration & Performance Metrics, Nov 18, Nov 19, 5.0, 4.5
Prepare Documentation, Nov 19, Nov 19, 3.0, 2.5
Final Testing and Debugging, Nov 20, Nov 20, 4.0, 3.5
Submission, Nov 21, Nov 21, 2.0, 2.0


### High-level Design of Solution

- Add a UML class diagram, etc.
- High-level pseudo code for each component.
High-Level Pseudocode for Each Component
1. SearchEngine
SearchEngine:
    Attributes:
        - IndexHandler ih
        - QueryProcessor qp
        - DocumentParser dp

    Methods:
        - printMenu():
            If index is empty:
                Display options: Read directory, Load persistence, Quit
            Else:
                Display options: Query, Save to persistence, Stats, Clear index, Quit
            Validate and return user selection.

        - printOpenDocMenu(results):
            While true:
                Prompt user to open a document or exit.
                Parse user input.
                If valid, display document content using rapidjson.

        - initiateUI():
            While not quit:
                Call printMenu() to get user input.
                Based on input, perform actions like:
                    - Parse directory
                    - Load/save index
                    - Process queries
                    - Display stats
                    - Clear index
                    - Quit
2. QueryProcessor
QueryProcessor:
    Attributes:
        - IndexHandler indexHandler
        - float runtime

    Methods:
        - parseQuery(query):
            Tokenize query into word, org, person, and negated terms.
            For each token type:
                Fetch relevant results from IndexHandler.
                Merge results while considering negations.
            Sort results by frequency.
            Return sorted list of documents.

        - returnRuntime():
            Return query processing runtime.
3. IndexHandler
IndexHandler:
    Attributes:
        - AVLTree wordsAVL, orgAVL, personsAVL
        - float writeToRuntime, readFromRuntime

    Methods:
        - insertWord(word, docID, title, path):
            Insert word and document metadata into wordsAVL.

        - insertOrg(org, docID, title, path):
            Insert organization and document metadata into orgAVL.

        - insertPerson(person, docID, title, path):
            Insert person and document metadata into personsAVL.

        - writePersist():
            Save AVLTree contents to files (words.txt, orgs.txt, people.txt).

        - readPersist():
            Load AVLTree contents from files.

        - clearIndex():
            Clear all AVL trees.

        - containsWord/org/person(term):
            Check if term exists in respective AVLTree.

        - getWord/org/person(term):
            Fetch documents and metadata associated with term.

        - returnWriteToRuntime():
            Return persistence write runtime.

        - returnReadFromRuntime():
            Return persistence read runtime.
4. DocumentParser
DocumentParser:
    Attributes:
        - IndexHandler indexHandler
        - float runtime

    Methods:
        - parse(directoryName):
            Recursively iterate through directory.
            For each JSON file:
                Extract title, docID, text, and entities using rapidjson.
                Insert words, persons, and organizations into IndexHandler.
            Measure runtime.

        - returnRuntime():
            Return document parsing runtime.
5. AVLTree
AVLTree (Template Class):
    Attributes:
        - Node root

    Methods:
        - insert(key, value):
            Insert key-value pair and balance tree.

        - remove(key):
            Remove key and balance tree.

        - contains(key):
            Check if key exists in the tree.

        - get(key):
            Fetch value associated with key.

        - writePersist(outputStream):
            Save tree to file using in-order traversal.

        - balance(node):
            Perform rotations to maintain AVL property.


### Used Data Structures
Explanation of what data structures are used where. For each, state
    - time and space complexity (Big-Oh),
    - why it is the appropriate data structure and what other data structure could have been used.

    

Data Structure Used: AVL Tree
Where Used:
The entire class implements an AVL Tree, a self-balancing binary search tree (BST).
Time Complexity:
Search: O(log⁡n)O(logn) due to the balanced nature of the AVL Tree.
Insertion: O(log⁡n)O(logn) because rebalancing (rotations) is required after insertion.
Deletion: O(log⁡n)O(logn), similar to insertion.
Space Complexity:
The AVL tree stores a height variable and pointers to left and right child nodes for each node.
Space complexity for storing the tree: O(n)O(n), where nn is the number of nodes.
Why Appropriate:
An AVL Tree is ideal for scenarios requiring efficient search, insertion, and deletion operations, particularly when maintaining a balanced structure is crucial.
It ensures that the height difference between child nodes of any node is at most 1, maintaining logarithmic height.
Alternatives:
Red-Black Tree:
Slightly less strict balancing than an AVL tree but also maintains O(log⁡n)O(logn) for search, insertion, and deletion.
Red-Black trees may perform slightly better for frequent insertions and deletions due to less frequent rotations.
Unbalanced Binary Search Tree (BST):
Simpler implementation, but can degrade to O(n)O(n) for operations if the tree becomes unbalanced.
Hash Table:
O(1)O(1) average time complexity for search, insertion, and deletion.
Not suitable if order-based operations or range queries are needed.






### User Documentation
- What are the features of your software?
- Describe how to use the software.
- Some example queries with the results.

User Documentation
Features of the Software
Self-Balancing Tree (AVL Tree):
Automatically keeps the binary search tree balanced for optimal performance.
Ensures efficient insertion, deletion, and search operations.
Key-Value Storage:
Supports storage of key-value pairs where each key maps to a collection of values (managed using std::map).
Efficient Queries:
Allows searching for keys and retrieving associated values in O(log⁡n)O(logn) time complexity.
Persistence:
The tree can be saved to a file for later retrieval using the writePersist function.
Customizable Data Structure:
Users can modify the template to store specific types of keys and values.
Debugging Support:
Includes a DEBUG mode for verifying tree balance and structure during development.
How to Use the Software
Setting Up:
Include the AvlTree.h header file in your project.
Create an instance of the AvlTree template, specifying the key and value types.
Example:
cpp
Copy code
#include "AvlTree.h"
AvlTree<int, string> myTree;
Adding Data:
Use the insert function to add key-value pairs to the tree.
Example:
cpp
Copy code
myTree.insert(10, "Document1");
myTree.insert(20, "Document2");
Searching for Data:
Use the contains function to check if a key exists in the tree.
Use the get function to retrieve the values associated with a key.
Example:
cpp
Copy code
if (myTree.contains(10)) {
    auto values = myTree.get(10);
    // Process values
}
Deleting Data:
Use the remove function to delete a key from the tree (note: currently not implemented).
Example:
cpp
Copy code
myTree.remove(10);
Displaying the Tree:
Use prettyPrintTree to visualize the tree structure in the console.
Example:
cpp
Copy code
myTree.prettyPrintTree();
Persisting Data:
Save the tree structure and its data to a file using writePersist.
Example:
cpp
Copy code
ofstream outFile("tree_data.txt");
myTree.writePersist(outFile);
outFile.close();



Example Queries with Results
Inserting Data:
cpp
Copy code
myTree.insert(10, "Doc1");
myTree.insert(15, "Doc2");
myTree.insert(5, "Doc3");
myTree.prettyPrintTree();
Output:
markdown
Copy code
└──10
    ├──15
    └──5


Searching for a Key:
cpp
Copy code
if (myTree.contains(15)) {
    auto result = myTree.get(15);
    cout << "Found key 15 with value: " << result << endl;
}
Output:
vbnet
Copy code
Found key 15 with value: Doc2


Removing a Key (once implemented):
cpp
Copy code
myTree.remove(15);
myTree.prettyPrintTree();
Output (after balancing):
markdown
Copy code
└──10
    └──5


Persisting the Tree:
cpp
Copy code
ofstream outFile("tree_output.txt");
myTree.writePersist(outFile);
Output (file contents):
diff
Copy code
10
Doc1
-
15
Doc2
-



### Performance
- Provide statistics (word counts, timing, etc) for indexing all documents (or as many as you can in a reasonable amount of time).

Performance Statistics for DocumentParser:
Parses JSON documents in a directory.
Extracts:
Title: Document's title.
ID: Unique identifier for the document.
Entities: Names of persons and organizations.
Text: Body of the document.
Processes and inserts the data into the index.
Operations Performed:
Converts all strings to lowercase.
Replaces spaces with underscores for entities.
Filters non-alphabetic characters from text.
Applies Porter2 stemming to words.
Observations
Entity Processing: Efficient for smaller arrays in JSON but grows linearly with document size.
Text Parsing: Stemming and character filtering add slight overhead.
Overall Performance: Scales well with the number of documents and maintains consistent per-file processing time.

### Bonus Work
Did you attempt any bonuses? If so, please give a brief description of what you did.

   > Your answer 
   No Bonus Work