
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
        std::string filename;
        Database(std::string filename);
        Database();
        ~Database();
        void writeCsv(std::vector<T> &data);
        void readCsv(std::vector<T> &data);
    };

}
