#ifndef AVL_TREE_H
#define AVL_TREE_H

// #define DEBUG  // Debug macro, uncomment to enable debug mode

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>

using namespace std;

/*
 * @class AvlTree
 * @brief This implementation is based on the unbalanced binary search tree and adds hight information
 * to the nodes and a balance function to perform the needed rotations.
 */
template <typename Comparable, typename ValueType>
class AvlTree {
   private:
    struct AvlNode {
        map<ValueType, int> value;
        Comparable key;
        AvlNode *left;
        AvlNode *right;
        int height;  // Height of the node used for balancing

        AvlNode(const Comparable &theKey, AvlNode *lt, AvlNode *rt, int h)
            : key{theKey}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;

    // Allowed imbalance in the AVL tree. A higher value will make balancing cheaper
    // but the search less efficient.
    static const int ALLOWED_IMBALANCE = 1;

   public:
    // Default constructor
    AvlTree() : root{nullptr} {
    }

    // Rule-of-3 Part 1: Copy constructor
    AvlTree(const AvlTree &rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    // Rule-of-3 Part 2: Destructor
    ~AvlTree() {
        makeEmpty();
    }

    // Rule-of-3 Part 3: Copy assignment operator
    AvlTree &operator=(const AvlTree &rhs) {
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }

        return *this;
    }

    // Move semantics could be implemented here.

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    /**
     * Return a reference to a node in the tree if exists.
     */
    map<ValueType, int> &get(const Comparable &x) const {
        return get(x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree structure.
     */
    void prettyPrintTree() const {
        prettyPrintTree("", root, false);
    }

    /**
     * Make the tree empty.
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x, const ValueType &y){
        insert(x, y, root);
    }
    
    
    void insert(const Comparable &x, const map<ValueType, int> &y){
        insert(x, y, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }

    void writePersist(ofstream& outFile){
        writePersist(outFile, root);
    }

#ifdef DEBUG
    /**
     * Check if the tree is balanced and that the height of the nodes is correct.
     * Throws an exception if the tree is not balanced or the height is wrong.
     * This function is not necessary in production code since the tree is always balanced.
     * It is only compiled when DEBUG is defined.
     */

    int check_balance() {
        return check_balance(root);
    }
#endif

   private:
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */

    void insert(const Comparable &x, const ValueType &y,  AvlNode *&t) {
        if (t == nullptr) {
            t = new AvlNode{x, nullptr, nullptr, 0};
            t->value.emplace(y, 0);
            return;  // a single node is always balanced
        }

        if (x < t->key)
            insert(x, y,  t->left);
        else if (t->key < x)
            insert(x, y,  t->right);
        else {
            t->value.emplace(y, 0);
        }  // Duplicate; do nothing

        // This will call balance on the way back up the tree. It will only balance
        // once at node the where the tree got imbalanced (called node alpha in the textbook)
        // and update the height all the way back up the tree.
        balance(t);
    }
    
    void insert(const Comparable &x, const map<ValueType, int> &y,  AvlNode *&t) {
        if (t == nullptr) {
            t = new AvlNode{x, nullptr, nullptr, 0};
            t->value = y;
            return;  // a single node is always balanced
        }

        if (x < t->key)
            insert(x, y,  t->left);
        else if (t->key < x)
            insert(x, y,  t->right);
        else {
        }  // Duplicate; do nothing

        // This will call balance on the way back up the tree. It will only balance
        // once at node the where the tree got imbalanced (called node alpha in the textbook)
        // and update the height all the way back up the tree.
        balance(t);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable &x, AvlNode *&t) {
        throw std::runtime_error("Not implemented yet!");
        // same as in a binary search tree

        // don't forget to balance the AVL tree after the deletion!
    }

    /**
     * Internal method to check if x is found in a subtree rooted at t.
     */
    bool contains(const Comparable &x, AvlNode *t) const {
        if (t == nullptr)
            return false;

        if (x == t->key)
            return true;  // Element found.
        else if (x < t->key)
            return contains(x, t->left);
        else
            return contains(x, t->right);
    }

    /**
     * Internal method to return a reference to a node in the tree if exists.
     */
    map<ValueType, int>& get(const Comparable &x, AvlNode *t) const {
        if (t == nullptr)
            throw invalid_argument("key not found");

        if (x == t->key)
            return t->value;  // Element found.
        else if (x < t->key)
            return get(x, t->left);
        else
            return get(x, t->right);
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t) {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const {
        if (t == nullptr)
            return nullptr;

        return new AvlNode{t->key, clone(t->left), clone(t->right), t->height};
    }

    /**
     * Pretty print the tree structure
     * Uses preorder traversal with R and L swapped (NRL)
     *
     * Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
     */
    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const {
        if (node == nullptr)
            return;

        std::cout << prefix;
        // Note: this uses unicode characters for the tree structure. They might not print correctly on
        // all systems (Windows!?!) and all types of output devices.
        std::cout << (isRight ? "├──" : "└──");
        // print the value of the node
        std::cout << node->key << std::endl;

        // enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
    }

    // Balancing: AVL Rotations

    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const {
        return t == nullptr ? -1 : t->height;
    }

    /**
     * 1. Performs rotations if the the the difference of the height stored in t's two child nodes
     *    more than ALLOWED_IMBALANCE.
     * 2. Updates the height information of the note t.
     *
     * Assumes that the high information in the child nodes is correct. This is guaranteed by calling
     * balance() recursively from the inserted node up to the tree node (see insert()). Rotations will
     * only be performed for node alpha (parent of the parent of the inserted node). For all other nodes,
     * only the height will be updated.
     */
    void balance(AvlNode *&t) {
        // special case: empty tree
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)  // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);  // case 1 (outside)
            else
                doubleWithLeftChild(t);                                     // case 2 (inside)
        } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)  // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);  // case 4 (outside)
            else
                doubleWithRightChild(t);  // case 3 (inside)
        }
        // else ... no imbalance was created

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const {
        return lhs > rhs ? lhs : rhs;
    }

    void writePersist(ofstream& outFile, AvlNode* t) {
        if (t == nullptr)
            return;

        outFile<< t->key<<endl;
        for (auto& ele: t->value) {
            outFile<< ele.first.docID<<endl;
            outFile<< ele.first.docTitle<<endl;
            outFile<< ele.first.docPath<<endl;
            outFile<< ele.second<<endl;
        }

        outFile<< "-"<<endl;

        writePersist(outFile, t->left);
        writePersist(outFile, t->right);
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2) {
#ifdef DEBUG
        cout << "need to rotateWithLeftChild for node " << k2->key << endl;
        cout << "Before:" << endl;
        prettyPrintTree();
#endif

        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
#ifdef DEBUG
        cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1) {
#ifdef DEBUG
        cout << "need to rotateWithRightChild for node " << k1->key << endl;
        cout << "Before:" << endl;
        prettyPrintTree();

#endif

        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
#ifdef DEBUG
        cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3) {
#ifdef DEBUG
        cout << "doubleWithLeftChild" << endl;
#endif
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1) {
#ifdef DEBUG
        cout << "doubleWithRightChild" << endl;
#endif
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

#ifdef DEBUG
    /**
     * Check if the tree is balanced and that the height of the nodes is correct.
     * Throws an exception if the tree is not balanced or the height is wrong.
     * This function is not necessary in production code since the tree is always balanced.
     * It is only compiled when DEBUG is defined.
     */

    int check_balance(AvlNode *node) {
        if (node == nullptr) {
            return -1;
        }

        // use LRN traversal to check the balance of the tree
        int lHeight = check_balance(node->left) + 1;
        int rHeight = check_balance(node->right) + 1;

        if (std::abs(lHeight - rHeight) > ALLOWED_IMBALANCE) {
            throw std::runtime_error("tree is not balanced in node with key " + std::to_string(node->key) + ".");
        }

        int trueNodeHeight = std::max(lHeight, rHeight);

        if (trueNodeHeight != node->height) {
            throw std::runtime_error("node does not have correct height value in node with key " + std::to_string(node->key) + ".");
        }

        return trueNodeHeight;
    }
#endif
};

#endif