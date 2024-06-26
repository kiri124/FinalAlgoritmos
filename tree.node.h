#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

namespace btree
{
    template <typename T>
    class BTreeNode
    {
    public:
        bool isLeaf;
        int nextId;                                                                // Contador para autoincrementar el ID
        std::vector<std::pair<std::string, std::vector<std::tuple<int, T>>>> keys; // Pair of key and vector of tuples (id, value)
        std::vector<BTreeNode *> children;

        BTreeNode(bool isLeaf);
        ~BTreeNode();

        void insertNonFull(const std::string &key, const T &value_, int t, int currentId);
        void splitChild(int i, BTreeNode *y, int t);
        std::vector<std::tuple<int, T>> search(const std::string &key);
        void traverse();
        void writeToCSV(std::ofstream &outFile);
        bool remove(const std::string &key, int id);
    };

    template <typename T>
    class BTree
    {
    public:
        std::string filePath;
        BTree(int t);
        BTree(int t, std::string filePath);
        ~BTree();

        void insert(const std::string &key, const T &value, int currentId);
        std::vector<std::tuple<int, T>> search(const std::string &key);
        std::vector<T> searchVector(const std::string &key);
        void traverse();
        void writeToCSV();
        void readFromCSV();
        bool remove(const std::string &key, int id);

    private:
        BTreeNode<T> *root;
        int t; // Minimum degree
    };

}