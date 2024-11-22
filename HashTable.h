// #ifndef HASH_H
// #define HASH_H

// #include <iostream>

// using namespace std;
// template <typename k, typename v>

// class HashTable{
//     struct HashNode {

//         k key;
//         v value;
//         HashNode* next;

//         //constructor 

//         }

//         private:

//         HashNode** table;
//         int size_count;
//         int capacity;
//         void rehash();
//         int hash(k);

//         public:


//         HashTable(int n = 100);

//         //rule of three 

//         //make a destructoir and call clear 
//         //make a d
//         void clone(const HashTable&);
//         void clear();

//         //overload constructor 

//         void insert(k, v);

//         v find(k);
//         int getSize();

//         void createHash(int n = 100);



//     };
// template <typename k, typename v>

// void HashTable<k, v> :: createHash(int n){
//     cap = n;
//     size = 0;
//     table = new HashNode*[cap];
//     for(int i = 0; i< cap; i++){
//         table[i] = nullptr;
//     }


// }

// template <typename k, typename v>
// void HashTable<k, v> :: clear(){

//     for(int i = 0; i< cap; i++){

//         HashNode* itr = table[i];

//         while(itr != nullptr){
//             HashNode* prev = itr;
//             itr = itr -> next;
//             delete prev;
//         }
//         table[i] = nullptr;
//     }

//     delete[] table; 
//     createHash(cap);
// }

// template <typename k, typename v>
// void HashTable<k, v> :: clone(const HashTable& copy){
//     clear();
//     delete[] table;
//     createHash(copy.cap);

//     for (int i =0; i< cap; i++){
//         HashNode* itr1 = copytable[i];
//         HashNode* itr2 = nullptr;

//         while(itr1 != nullptr){
//             HashNode* newNode = new HashNode(*itr1);

//             if(itr2 == nullptr){
//                 table[i] = newNode;
//             }
//             else{
//                 itr2-> next = newNode;
//             }
//             itr2 = newNode;
//             itr1 = itr1 -> next;
//         }
//     }
// }

// template <typename k, typename v>
// int hash(k key){
//     int index = std::hash<k>{}(key)
//     return abs(index%cap)
// }

// template <typename k, typename v>
// void insert(k key, v value){
//     int index = hash(key);
//     if(table[index] == nullptr){
//         table[index] = new HashNode(key, value);
//         size++;
//     } else{
//         HashNode* prev = nullptr;
//         HashNode* itr = table[index];
//         while(itr != nullptr){
//             if(itr->key = key){
//                 itr -> value = value;
//                 break;
//             }
//             prev = itr;
//             itr = itr->next;
//         }
//     if(itr == nullptr && prev != nullptr){
//         prev->next = new HashNode(key, value);
//         size++
//     }
//     }
//     if(size==cap){
//         rehash();
//     }
// }

// template <typename k, typename v>
// v find (key){
//     int index = hash(key);
//     HashNode* itr = table[index];
//     while(itr!=nullptr){
//         if(itr->key == key){
//             return itr->value;
//         }
//         itr = itr->next;
//     }

//     return v();

    
// }

// template <typename k, typename v>
// void rehash(){
//     int oldCap = cap;
//     cap* = 2;
//     HashNode** oldTable = table;
//     createHash(cap);
//     for(int i = 0; i < oldCap; i++){
//         HashNode* itr = oldTable[i];
    
//     while(itr != nullptr){
//         insert(itr->key, itr->value) // create deep copy
//         HashNode* temp = itr;
//         itr = itr->next;
//         delete temp;

//     }
//     oldTable[i] = nullptr;

//     }
//     delete[] oldTable;

// }

// ;
// #endif