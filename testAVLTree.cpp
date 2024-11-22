// #define CATCH_CONFIG_MAIN

// #include <iostream>

// #include "AvlTree.h"
// #include "catch2/catch.hpp"

// /*
// - copy constructor
// - operator=
// - contains
// - isEmpt insert
// - find
// - remove
// */

// TEST_CASE("Test copy constructor function", "[AvlTree]") {
//     SECTION("") {
//         AvlTree<int, int> tester;

//         tester.insert(1, 1);
//     }

//     SECTION("Test copy constructor with an empty tree", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree1;
//         AvlTree<int, map<string, int>> tree2(tree1);

//         REQUIRE(tree2.isEmpty() == true);
//     }

//     SECTION("Test copy constructor with non-empty tree", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree1;
//         tree1.insert(10, {{"id1", 1}});
//         tree1.insert(5, {{"id2", 1}});

//         AvlTree<int, map<string, int>> tree2(tree1);

//         REQUIRE(tree2.contains(10) == true);
//         REQUIRE(tree2.contains(5) == true);
//     }

//     SECTION("Test copy constructor with self-copy", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});

//         AvlTree<int, map<string, int>> tree2(tree);

//         REQUIRE(tree2.contains(10) == true);
//         REQUIRE(tree2.contains(5) == true);
//     }
// }

// TEST_CASE("Test operator= function", "[AvlTree]") {
//     SECTION("Test operator= with an empty tree", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree1;
//         AvlTree<int, map<string, int>> tree2;

//         tree1 = tree2;

//         REQUIRE(tree1.isEmpty() == true);
//         REQUIRE(tree2.isEmpty() == true);
//     }

//     SECTION("Test operator= with non-empty trees", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree1;
//         tree1.insert(10, {{"id", 1}});
//         tree1.insert(5, {{"id2", 1}});

//         AvlTree<int, map<string, int>> tree2;
//         tree2.insert(15, {{"id3", 1}});
//         tree2.insert(20, {{"id4", 1}});

//         tree1 = tree2;

//         REQUIRE(tree1.contains(10) == false);
//         REQUIRE(tree1.contains(5) == false);
//         REQUIRE(tree1.contains(15) == true);
//         REQUIRE(tree1.contains(20) == true);
//     }

//     SECTION("Test operator= with self-assignment", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});

//         tree = tree;

//         REQUIRE(tree.contains(10) == true);
//         REQUIRE(tree.contains(5) == true);
//     }
// }

// TEST_CASE("Test contains function") {
//     AvlTree<int, map<string, int>> tree;

//     SECTION("Empty tree") {
//         REQUIRE(tree.contains(5) == false);
//     }

//     tree.insert(10, {{"id1", 1}});
//     tree.insert(5, {{"id2", 1}});
//     tree.insert(15, {{"id3", 1}});
//     tree.insert(3, {{"id4", 1}});
//     tree.insert(7, {{"id5", 1}});

//     SECTION("Element is present") {
//         REQUIRE(tree.contains(10) == true);
//         REQUIRE(tree.contains(3) == true);
//         REQUIRE(tree.contains(7) == true);
//     }

//     SECTION("Element is not present") {
//         REQUIRE(tree.contains(20) == false);
//         REQUIRE(tree.contains(2) == false);
//         REQUIRE(tree.contains(8) == false);
//     }
// }
// /// h

// TEST_CASE("Test isEmpty function", "[AvlTree]") {
//     SECTION("Empty tree") {
//         AvlTree<int, map<string, int>> tree;
//         REQUIRE(tree.isEmpty() == true);
//     }

//     SECTION("Non-empty tree") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         REQUIRE(tree.isEmpty() == false);
//     }

//     SECTION("After inserting and removing elements") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});
//         tree.remove(10);
//         REQUIRE(tree.isEmpty() == false);
//     }

//     SECTION("After making the tree empty") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.makeEmpty();
//         REQUIRE(tree.isEmpty() == true);
//     }
// }

// TEST_CASE("Test makeEmpty function", "[AvlTree]") {
//     SECTION("Check with an empty tree") {
//         AvlTree<int, map<string, int>> tree;
//         tree.makeEmpty();
//         REQUIRE(tree.isEmpty() == true);
//         tree.makeEmpty();
//         REQUIRE(tree.isEmpty() == true);
//     }

//     SECTION("Check with a non-empty tree") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});
//         tree.makeEmpty();
//         REQUIRE(tree.isEmpty() == true);
//     }

//     SECTION("Check after inserting and removing elements") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"d2", 1}});
//         tree.remove(10);
//         tree.makeEmpty();
//         REQUIRE(tree.isEmpty() == true);
//     }
// }

// TEST_CASE("Test avlTree insert function", "[AvlTree]") {
//     AvlTree<string, map<string, int>> tree;

//     SECTION("Check insert") {
//         tree.insert("Andy", {{"id1", 1}});
//         tree.insert("Alex", {{"id1", 1}});
//         tree.insert("Orly", {{"id1", 1}});
//         tree.insert("Olivia", {{"id1", 1}});
//         tree.insert("Ale", {{"id1", 1}});
//         tree.insert("Poolah", {{"id1", 1}});
//         tree.insert("Bianca", {{"id1", 1}});
//         tree.insert("Sophie", {{"id1", 1}});
//         tree.remove("Ethan");

//         REQUIRE(tree.contains("Andy") == true);
//         REQUIRE(tree.contains("XXXX") == false);
//     }
// }

// TEST_CASE("Test AvlTree find function", "[AvlTree]") {
//     AvlTree<string, map<string, int>> tree;

//     SECTION("if function throws oob") {
//         REQUIRE_THROWS(tree.find("hello"));
//     }

//     SECTION("Check find") {
//         tree.insert("Andy", {{"id1", 1}});
//         tree.insert("Toney", {{"id2", 1}});
//         tree.insert("Carlos", {{"id3", 1}});
//         tree.insert("Bianca", {{"id4", 1}});
//         // tree.insert("Ethan", {{"id1", 1}});
//         tree.insert("Booola", {{"id1", 1}});
//         tree.insert("Poola", {{"id1", 1}});
//         tree.insert("China", {{"id1", 1}});
//         // tree.remove("Ethan");
//         map<string, int> test;
//         test["id1"] = 1;
//         map<string, int> test2;
//         test2["id1"] = 1;
//         REQUIRE(tree.find("Andy") == test);
//         // REQUIRE(tree.find("Ethan") != test);
//         REQUIRE(tree.find("China") == test2);
//     }
// }

// TEST_CASE("Test avlTree remove function", "[AvlTree]") {
//     AvlTree<string, map<string, int>> tree;

//     SECTION("Remove a node with no children", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.remove(10);

//         REQUIRE(tree.contains(10) == false);
//         REQUIRE(tree.isEmpty() == true);
//     }

//     // remove a node with one child
//     SECTION("Remove a node with one child", "[avlTree]") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});
//         tree.remove(10);

//         REQUIRE(tree.contains(10) == false);
//         REQUIRE(tree.contains(5) == true);
//     }

//     // remove a node with two children
//     SECTION("Remove a node with two children", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});
//         tree.insert(15, {{"id3", 1}});
//         tree.remove(10);

//         REQUIRE(tree.contains(10) == false);
//         REQUIRE(tree.contains(5) == true);
//         REQUIRE(tree.contains(15) == true);
//     }

//     // remove root node
//     SECTION("Remove root node", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});
//         tree.insert(15, {{"id3", 1}});
//         tree.remove(10);

//         REQUIRE(tree.contains(10) == false);
//         REQUIRE(tree.contains(5) == true);
//         REQUIRE(tree.contains(15) == true);
//     }

//     // remove node that causes rotation
//     SECTION("Remove node that causes rotation", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});
//         tree.insert(15, {{"id3", 1}});
//         tree.insert(13, {{"id4", 1}});
//         tree.remove(5);

//         REQUIRE(tree.contains(5) == false);
//         REQUIRE(tree.contains(10) == true);
//         REQUIRE(tree.contains(13) == true);
//         REQUIRE(tree.contains(15) == true);
//     }

//     // remove a nonexistent node
//     SECTION("Remove a nonexistent node", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});
//         tree.remove(15);

//         REQUIRE(tree.contains(10) == true);
//         REQUIRE(tree.contains(5) == true);
//         REQUIRE(tree.contains(15) == false);
//     }

//     // remove nodes until tree is empty
//     SECTION("Remove nodes until tree is empty", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});
//         tree.insert(15, {{"id3", 1}});
//         tree.remove(10);
//         tree.remove(5);
//         tree.remove(15);

//         REQUIRE(tree.isEmpty() == true);
//     }

//     // remove nodes to create multiple rotations
//     SECTION("Remove nodes to create multiple rotations", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree;
//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});
//         tree.insert(15, {{"id3", 1}});
//         tree.insert(13, {{"id4", 1}});
//         tree.insert(20, {{"id5", 1}});
//         tree.remove(5);

//         REQUIRE(tree.contains(5) == false);
//         REQUIRE(tree.contains(10) == true);
//         REQUIRE(tree.contains(13) == true);
//         REQUIRE(tree.contains(15) == true);
//         REQUIRE(tree.contains(20) == true);
//     }

//     SECTION("Randomly remove nodes", "[AvlTree]") {
//         AvlTree<int, map<string, int>> tree;

//         tree.insert(10, {{"id1", 1}});
//         tree.insert(5, {{"id2", 1}});
//         tree.insert(15, {{"id3", 1}});
//         tree.insert(3, {{"id4", 1}});
//         tree.insert(7, {{"id5", 1}});
//         tree.insert(12, {{"id6", 1}});
//         tree.insert(17, {{"id7", 1}});

//         tree.remove(10);
//         tree.remove(7);
//         tree.remove(15);

//         REQUIRE(tree.contains(10) == false);
//         REQUIRE(tree.contains(7) == false);
//         REQUIRE(tree.contains(15) == false);
//     }
// }
