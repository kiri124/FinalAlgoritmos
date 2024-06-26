#include <iostream>
#include <fstream>
#include <filesystem>
#include <queue>
#include "structures.h"
#include "utils.h"

using namespace std;

// Funcion recursiva para validar que una cadena contiene solo letras y espacios
bool utils::esSoloLetrasYEspacios(const string &str, int index)
{
  if (index == str.length())
    return true;
  if (!isalpha(str[index]) && str[index] != ' ')
    return false;
  return esSoloLetrasYEspacios(str, index + 1);
}

// Funcion recursiva para validar que una cadena contiene solo letras, numeros y espacios
bool utils::esSoloLetrasNumerosYEspacios(const string &str, int index)
{
  if (index == str.length())
    return true;
  if (!isalnum(str[index]) && str[index] != ' ')
    return false;
  return esSoloLetrasNumerosYEspacios(str, index + 1);
}

// Funcion recursiva para validar si un numero de DNI es valido
bool utils::esDniValido(const string &dni, int index)
{
  // Se asume que un DNI valido tiene 8 digitos
  if (dni.length() != 8)
    return false;
  if (index == dni.length())
    return true;
  if (!isdigit(dni[index]))
    return false;
  return esDniValido(dni, index + 1);
}

// Funcion recursiva para validar si un numero de telefono es valido
bool utils::esCelularValido(const string &celular, int index)
{
  // Se asume que un numero de telefono valido tiene 9 digitos
  if (celular.length() != 9)
    return false;
  if (index == celular.length())
    return true;
  if (!isdigit(celular[index]))
    return false;
  return esCelularValido(celular, index + 1);
}

// Funcion recursiva para validar si el nombre ingresado contiene caracteres alfabeticos solamente
bool utils::esNombreValido(const string &nombre, int index)
{
  if (index == nombre.length())
    return true;
  if (!isalpha(nombre[index]) && nombre[index] != ' ')
    return false;
  return esNombreValido(nombre, index + 1);
}

// Funcion para validar si el genero ingresado es valido (M o F)
bool utils::esGeneroValido(char genero)
{
  return genero == 'M' || genero == 'm' || genero == 'F' || genero == 'f';
}

// Funcion para validar si el estado civil ingresado es valido (S, C, V o D)
bool utils::esEstadoCivilValido(char estadoCivil)
{
  return estadoCivil == 'S' || estadoCivil == 's' || estadoCivil == 'C' || estadoCivil == 'c' || estadoCivil == 'V' || estadoCivil == 'v' || estadoCivil == 'D' || estadoCivil == 'd';
}

void utils::checkAndCreateFile(const std::string &filename)
{
  // Verificar si el archivo existe
  if (!std::filesystem::exists(filename))
  {
    std::cout << "El archivo no existe. Creando el archivo..." << std::endl;

    // Crear el archivo
    std::ofstream outFile(filename);
    if (!outFile)
    {
      std::cerr << "Error al crear el archivo." << std::endl;
      return;
    }
    outFile.close();
    std::cout << "Archivo creado exitosamente." << std::endl;
  }
  else
  {
    std::cout << "El archivo ya existe." << std::endl;
  }
}
