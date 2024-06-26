#include <iostream>
#include <fstream>
#include <vector>
#include "structures.h"
#include "database.h"

template <typename T>
database::Database<T>::Database() {}

template <typename T>
database::Database<T>::Database(std::string filename) : filename(filename) {}

template <typename T>
database::Database<T>::~Database() {}

// Función genérica para escribir un vector de objetos T en un archivo CSV
template <typename T>
void database::Database<T>::writeCsv(std::vector<T> &data)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    // auto headers = data.front().getHeaders();
    // for (size_t i = 0; i < headers.size(); ++i)
    // {
    //     file << headers[i];
    //     if (i < headers.size() - 1)
    //         file << ",";
    // }
    // file << "\n";

    for (const auto &person : data)
    {
        // Aquí asumo que Person tiene un método toCsvString() para obtener una representación CSV
        file << person.toCsvString() << "\n";
    }

    file.close();
}

template <typename T>
void database::Database<T>::readCsv(std::vector<T> &data)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    std::string line;
    // Omitir encabezados
    if (std::getline(file, line))
    {
        // Leer datos
        while (std::getline(file, line))
        {
            try
            {
                data.push_back(T(line));
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error al procesar la línea: " << line << "\n"
                          << e.what() << '\n';
            }
        }
    }

    file.close();
}

template class database::Database<Usuario>;
template class database::Database<HistorialMedico>;
template class database::Database<Receta>;
template class database::Database<Paciente>;