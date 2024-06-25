
#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "structures.h"

namespace database
{

    template <typename T>
    class Database
    {
    public:
        Database();
        ~Database();
        void writeCsv(const std::string &filename, std::vector<T> &data);
        void readCsv(const std::string &filename, std::vector<T> &data);
    };

}
