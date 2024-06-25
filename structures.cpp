#include <iostream>
#include <vector>
#include <string>
#include "structures.h"
#include <sstream>
#include <stdexcept>

std::vector<std::string> Usuario::getHeaders() const
{
    return {"Tipo", "Nombre", "Contrasena"};
}

// Ejemplo de función para obtener una representación CSV de Person (opcional)
std::string Usuario::toCsvString() const
{
    return tipo + "," + nombre + "," + contrasena;
}
Usuario::Usuario() {}
Usuario::Usuario(const std::string &csvLine)
{
    std::stringstream ss(csvLine);
    std::string item;

    if (std::getline(ss, item, ','))
        tipo = item;
    else
        throw std::runtime_error("Failed to parse tipo");

    if (std::getline(ss, item, ','))
        nombre = item;
    else
        throw std::runtime_error("Failed to parse nombre");

    if (std::getline(ss, item, ','))
        contrasena = item;
    else
        throw std::runtime_error("Failed to parse contrasena");

    siguiente = nullptr;
}

std::vector<std::string> Person::getHeaders() const
{
    return {"Name", "Age", "City"};
}

// Ejemplo de función para obtener una representación CSV de Person (opcional)
std::string Person::toCsvString() const
{
    return name + "," + std::to_string(age) + "," + city;
}

// Constructor para inicializar desde parámetros
Person::Person(const std::string &name, int age, const std::string &city)
    : name(name), age(age), city(city) {}

Person::Person(const std::string &csvLine)
{
    std::stringstream ss(csvLine);
    std::string item;

    if (std::getline(ss, item, ','))
        name = item;
    else
        throw std::runtime_error("Failed to parse name");

    if (std::getline(ss, item, ','))
        age = std::stoi(item);
    else
        throw std::runtime_error("Failed to parse age");

    if (std::getline(ss, item, ','))
        city = item;
    else
        throw std::runtime_error("Failed to parse city");
}