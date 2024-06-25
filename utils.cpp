#include <iostream>
#include "utils.h"

using namespace std;

// Funcion recursiva para validar que una cadena contiene solo letras y espacios
bool esSoloLetrasYEspacios(const string &str, int index)
{
  if (index == str.length())
    return true;
  if (!isalpha(str[index]) && str[index] != ' ')
    return false;
  return esSoloLetrasYEspacios(str, index + 1);
}

// Funcion recursiva para validar que una cadena contiene solo letras, numeros y espacios
bool esSoloLetrasNumerosYEspacios(const string &str, int index)
{
  if (index == str.length())
    return true;
  if (!isalnum(str[index]) && str[index] != ' ')
    return false;
  return esSoloLetrasNumerosYEspacios(str, index + 1);
}

// Funcion recursiva para validar si un numero de DNI es valido
bool esDniValido(const string &dni, int index)
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
bool esCelularValido(const string &celular, int index)
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
bool esNombreValido(const string &nombre, int index)
{
  if (index == nombre.length())
    return true;
  if (!isalpha(nombre[index]) && nombre[index] != ' ')
    return false;
  return esNombreValido(nombre, index + 1);
}

// Funcion para validar si el genero ingresado es valido (M o F)
bool esGeneroValido(char genero)
{
  return genero == 'M' || genero == 'm' || genero == 'F' || genero == 'f';
}

// Funcion para validar si el estado civil ingresado es valido (S, C, V o D)
bool esEstadoCivilValido(char estadoCivil)
{
  return estadoCivil == 'S' || estadoCivil == 's' || estadoCivil == 'C' || estadoCivil == 'c' || estadoCivil == 'V' || estadoCivil == 'v' || estadoCivil == 'D' || estadoCivil == 'd';
}