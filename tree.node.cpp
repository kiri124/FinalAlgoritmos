#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <fstream>
#include <filesystem>
#include "tree.node.h"
#include "structures.h"

using namespace btree;

template <typename T>
BTreeNode<T>::BTreeNode(bool isLeaf) : isLeaf(isLeaf), nextId(1) {}

template <typename T>
BTreeNode<T>::~BTreeNode()
{
    for (auto child : children)
    {
        delete child;
    }
}

template <typename T>
void BTreeNode<T>::insertNonFull(const std::string &key, const T &value, int t, int currentId)
{
    int i = keys.size() - 1;
    int nextID = nextId++;
    if (currentId > 0)
    {
        nextID = currentId;
    }

    if (isLeaf)
    {
        while (i >= 0 && keys[i].first > key)
        {
            i--;
        }

        if (i >= 0 && keys[i].first == key)
        {
            keys[i].second.push_back({nextID, value}); // Incrementar y usar el siguiente ID
        }
        else
        {
            keys.insert(keys.begin() + i + 1, {key, {{nextID, value}}});
        }
    }
    else
    {
        while (i >= 0 && keys[i].first > key)
        {
            i--;
        }

        if (i >= 0 && keys[i].first == key)
        {
            keys[i].second.push_back({nextID, value}); // Incrementar y usar el siguiente ID
            return;
        }

        if (children[i + 1]->keys.size() == 2 * t - 1)
        {
            splitChild(i + 1, children[i + 1], t);
            if (keys[i + 1].first < key)
            {
                i++;
            }
        }
        children[i + 1]->insertNonFull(key, value, t, nextID);
    }
}

template <typename T>
void BTreeNode<T>::splitChild(int i, BTreeNode *y, int t)
{
    BTreeNode *z = new BTreeNode(y->isLeaf);
    z->keys.resize(t - 1);

    for (int j = 0; j < t - 1; j++)
    {
        z->keys[j] = y->keys[j + t];
    }

    if (!y->isLeaf)
    {
        z->children.resize(t);
        for (int j = 0; j < t; j++)
        {
            z->children[j] = y->children[j + t];
        }
    }

    y->keys.resize(t - 1);

    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

template <typename T>
std::vector<std::tuple<int, T>> BTreeNode<T>::search(const std::string &key)
{
    int i = 0;
    while (i < keys.size() && key > keys[i].first)
    {
        i++;
    }

    if (i < keys.size() && keys[i].first == key)
    {
        return keys[i].second;
    }

    if (isLeaf)
    {
        return {};
    }

    return children[i]->search(key);
}

template <typename T>
void BTreeNode<T>::traverse()
{
    int i;
    for (i = 0; i < keys.size(); i++)
    {
        if (!isLeaf)
        {
            children[i]->traverse();
        }
        std::cout << "Key: " << keys[i].first << " Values: ";
        for (const auto &[id, value] : keys[i].second)
        {
            std::cout << id << ":" << value << " ";
        }
        std::cout << std::endl;
    }

    if (!isLeaf)
    {
        children[i]->traverse();
    }
}

template <typename T>
void BTreeNode<T>::writeToCSV(std::ofstream &outFile)
{
    for (const auto &keyPair : keys)
    {
        for (const auto &[id, value] : keyPair.second)
        {
            outFile << keyPair.first << "," << id << "," << value << "\n";
        }
    }

    if (!isLeaf)
    {
        for (auto child : children)
        {
            child->writeToCSV(outFile);
        }
    }
}

template <typename T>
bool BTreeNode<T>::remove(const std::string &key, int id)
{
    int i = 0;
    while (i < keys.size() && key > keys[i].first)
    {
        i++;
    }

    if (i < keys.size() && keys[i].first == key)
    {
        auto &values = keys[i].second;
        for (auto it = values.begin(); it != values.end(); ++it)
        {
            if (std::get<0>(*it) == id)
            {
                values.erase(it);
                if (values.empty())
                {
                    keys.erase(keys.begin() + i);
                }
                return true;
            }
        }
    }

    if (isLeaf)
    {
        return false;
    }

    return children[i]->remove(key, id);
}

template <typename T>
BTree<T>::BTree(int t) : t(t)
{
    root = new BTreeNode<T>(true);
}
template <typename T>
BTree<T>::BTree(int t, std::string filePath) : t(t), filePath(filePath)
{
    root = new BTreeNode<T>(true);
}

template <typename T>
BTree<T>::~BTree()
{
    delete root;
}

template <typename T>
void BTree<T>::insert(const std::string &key, const T &value, int currentId)
{
    if (root->keys.size() == 2 * t - 1)
    {
        BTreeNode<T> *s = new BTreeNode<T>(false);
        s->children.push_back(root);
        s->splitChild(0, root, t);
        root = s;
    }
    root->insertNonFull(key, value, t, currentId);
}

template <typename T>
std::vector<std::tuple<int, T>> BTree<T>::search(const std::string &key)
{
    return root ? root->search(key) : std::vector<std::tuple<int, T>>{};
}

template <typename T>
std::vector<T> BTree<T>::searchVector(const std::string &key)
{
    std::vector<std::tuple<int, T>> results = search(key);
    std::vector<T> values;
    for (const auto &[id, value] : results)
    {
        values.push_back(value);
    }
    return values;
}

template <typename T>
void BTree<T>::traverse()
{
    if (root)
    {
        root->traverse();
    }
}

template <typename T>
void BTree<T>::writeToCSV()
{
    std::ofstream outFile(filePath);
    if (outFile.is_open())
    {
        std::queue<BTreeNode<T> *> nodeQueue;
        nodeQueue.push(root);

        while (!nodeQueue.empty())
        {
            BTreeNode<T> *currentNode = nodeQueue.front();
            nodeQueue.pop();

            for (const auto &keyPair : currentNode->keys)
            {
                for (const auto &[id, value] : keyPair.second)
                {
                    outFile << keyPair.first << "," << id << "," << value << "\n";
                }
            }

            if (!currentNode->isLeaf)
            {
                for (auto child : currentNode->children)
                {
                    nodeQueue.push(child);
                }
            }
        }
        outFile.close();
    }
}

template <typename T>
void BTree<T>::readFromCSV()
{
    try
    {
        std::ifstream inFile(filePath);
        if (inFile.is_open())
        {
            std::string line;
            int maxId = 0;
            while (std::getline(inFile, line))
            {
                try
                {
                    std::stringstream ss(line);
                    std::string key;
                    std::getline(ss, key, ',');
                    std::string id;
                    std::getline(ss, id, ',');
                    T value = T(line);
                    insert(key, value, stoi(id));
                    maxId = maxId < stoi(id) ? stoi(id) : maxId;
                }
                catch (...)
                {
                }
            }
            inFile.close();

            root->nextId = maxId + 1;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

template <typename T>
bool BTree<T>::remove(const std::string &key, int id)
{
    return root ? root->remove(key, id) : false;
}

template class BTree<HistorialMedico>;