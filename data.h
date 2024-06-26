#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "utils.h"

namespace data
{
    template <typename T>
    struct TrieNode
    {
        std::unordered_map<char, TrieNode *> children;
        T *data; // Referencia al dato si este nodo representa el final de una clave

        TrieNode() : data(nullptr) {}
        ~TrieNode()
        {
            delete data;
            for (auto &child : children)
            {
                delete child.second;
            }
        }
    };

    template <typename T>
    class Trie
    {
    public:
        std::string dbPath;
        Trie() : root(new TrieNode<T>()) {}
        Trie(std::string path) : root(new TrieNode<T>())
        {
            utils::checkAndCreateFile(path);
            dbPath = path;
        }
        ~Trie()
        {
        }
        void insert(T *data, const std::string &key);
        T *search(const std::string &key);
        std::vector<T *> searchMany(const std::string &key);
        void loadFromCsv();
        void saveToCsv();

    private:
        void searchHelper(data::TrieNode<T> *node_, const std::string &key, std::vector<T *> &results);
        TrieNode<T> *root;
    };

} // namespace data
