#include <iostream>
#include <fstream>
#include <filesystem>
#include <queue>
#include "structures.h"
#include "data.h"

/**
 * Inserts a data element into the Trie using the given key.
 *
 * @param data A pointer to the data element to be inserted.
 * @param key The key used to identify the position in the Trie where the data element should be inserted.
 *
 * @throws None
 */
template <typename T>
void data::Trie<T>::insert(T *data, const std::string &key)
{
    TrieNode<T> *node = root;
    for (char ch : key)
    {
        if (node->children.find(ch) == node->children.end())
        {
            node->children[ch] = new TrieNode<T>();
        }
        node = node->children[ch];
    }
    node->data = data;
}

/**
 * Searches for a data element in the Trie using the given key.
 *
 * @param key The key used to identify the position in the Trie where the data element is located.
 *
 * @return A pointer to the data element if the complete key is found in the Trie, nullptr otherwise.
 *
 * @throws None
 */
template <typename T>
T *data::Trie<T>::search(const std::string &key)
{
    TrieNode<T> *node = root;
    for (char ch : key)
    {
        if (node->children.find(ch) == node->children.end())
        {
            return nullptr; // Clave no encontrada
        }
        node = node->children[ch];
    }
    return node->data; // Devuelve el dato si la clave completa está en el Trie
}
template <typename T>
void data::Trie<T>::searchHelper(data::TrieNode<T> *node_, const std::string &key, std::vector<T *> &results)
{
    if (node_ == nullptr)
    {
        return;
    }

    // Ejemplo de búsqueda: Suponiendo que T tiene un método getNombre() para obtener el nombre
    if (node_->data && node_->data->nombre == key)
    {
        results.push_back(node_->data);
    }

    for (auto &child : node_->children)
    {
        searchHelper(child.second, key, results);
    }
}

template <typename T>
std::vector<T *> data::Trie<T>::searchMany(const std::string &key)
{
    std::vector<T *> results;
    searchHelper(root, key, results);
    return results;
}

/**
 * Loads data from a CSV file into a Trie.
 *
 * @tparam T The type of data stored in the Trie.
 *
 * @throws std::runtime_error If the CSV file cannot be opened.
 */
template <typename T>
void data::Trie<T>::loadFromCsv()
{
    std::ifstream inFile(dbPath);
    if (!inFile.is_open())
    {
        std::cerr << "Error al abrir el archivo CSV para lectura." << std::endl;
        return;
    }

    std::string line;
    bool isHeader = false;

    while (std::getline(inFile, line))
    {
        if (isHeader)
        {
            isHeader = false; // Ignorar la primera línea (encabezado)
            continue;
        }

        T *data = new T(line);
        insert(data, data->nombre);
    }

    inFile.close();
}
/**
 * Saves the data stored in the Trie to a CSV file.
 *
 * @param None
 *
 * @return None
 *
 * @throws None
 */
template <typename T>
void data::Trie<T>::saveToCsv()
{
    std::ofstream outFile(dbPath);
    if (!outFile.is_open())
    {
        std::cerr << "Error al abrir el archivo CSV para escritura." << std::endl;
        return;
    }

    if (root->data)
    {
        std::vector<std::string> headers = root->data->getHeaders();
        for (size_t i = 0; i < headers.size(); ++i)
        {
            outFile << headers[i];
            if (i < headers.size() - 1)
            {
                outFile << ",";
            }
        }
        outFile << "\n";
    }

    std::queue<TrieNode<T> *> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty())
    {
        TrieNode<T> *currentNode = nodeQueue.front();
        nodeQueue.pop();

        if (currentNode->data)
        {
            outFile << currentNode->data->toCsvString() << "\n";
        }

        for (auto &child : currentNode->children)
        {
            nodeQueue.push(child.second);
        }
    }

    outFile.close();
}

template class data::Trie<Usuario>;
template class data::Trie<HistorialMedico>;