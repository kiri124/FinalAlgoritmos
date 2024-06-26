#include <iostream>
#include <unordered_map>
#include <string>
#include "data.h"
#include "structures.h"

#ifndef UTILS_H
#define UTILS_H

using namespace std;

namespace utils
{

    bool esSoloLetrasYEspacios(const string &str, int index = 0);
    bool esSoloLetrasNumerosYEspacios(const string &str, int index = 0);
    bool esDniValido(const string &dni, int index = 0);
    bool esCelularValido(const string &celular, int index = 0);
    bool esNombreValido(const string &nombre, int index = 0);
    bool esGeneroValido(char genero);
    bool esEstadoCivilValido(char estadoCivil);
    void checkAndCreateFile(const std::string &filename);

}
#endif
