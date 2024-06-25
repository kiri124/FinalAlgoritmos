#include <iostream>

#ifndef UTILS_H
#define UTILS_H

using namespace std;
bool esSoloLetrasYEspacios(const string &str, int index = 0);
bool esSoloLetrasNumerosYEspacios(const string &str, int index = 0);
bool esDniValido(const string &dni, int index = 0);
bool esCelularValido(const string &celular, int index = 0);
bool esNombreValido(const string &nombre, int index = 0);
bool esGeneroValido(char genero);
bool esEstadoCivilValido(char estadoCivil);
#endif
