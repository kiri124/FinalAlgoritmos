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

std::vector<std::string> Receta::getHeaders() const
{
    return {"NombrePaciente", "Medicamento", "Dosis", "NumeroDias", "CadaCuantasHoras"};
}

// Ejemplo de función para obtener una representación CSV de Person (opcional)
std::string Receta::toCsvString() const
{
    return nombrePaciente + "," + medicamento + "," + dosis + "," + std::to_string(numeroDias) + "," + std::to_string(cadaCuantasHoras);
}
Receta::Receta() {}
Receta::Receta(const std::string &csvLine)
{
    std::stringstream ss(csvLine);
    std::string item;
    if (std::getline(ss, item, ','))
        nombrePaciente = item;
    if (std::getline(ss, item, ','))
        medicamento = item;
    if (std::getline(ss, item, ','))
        dosis = item;
    if (std::getline(ss, item, ','))
        numeroDias = std::stoi(item);
    if (std::getline(ss, item, ','))
        cadaCuantasHoras = std::stoi(item);
}

std::vector<std::string> HistorialMedico::getHeaders() const
{
    return {"NombrePaciente", "FechaConsulta", "MotivoConsulta", "Diagnostico", "Tratamiento"};
}

// Ejemplo de función para obtener una representación CSV de Person (opcional)
std::string HistorialMedico::toCsvString() const
{
    return nombre + "," + fechaConsulta + "," + motivoConsulta + "," + diagnostico + "," + tratamiento;
}

HistorialMedico::HistorialMedico()
{
}
HistorialMedico::HistorialMedico(const std::string &csvLine)
{
    std::stringstream ss(csvLine);
    std::string item;
    std::getline(ss, item, ','); // key is not used
    if (std::getline(ss, item, ','))
        id = stoi(item);
    if (std::getline(ss, item, ','))
        nombre = item;
    if (std::getline(ss, item, ','))
        fechaConsulta = item;
    if (std::getline(ss, item, ','))
        motivoConsulta = item;
    if (std::getline(ss, item, ','))
        diagnostico = item;
    if (std::getline(ss, item, ','))
        tratamiento = item;
}

std::vector<std::string> Paciente::getHeaders() const
{
    return {"Nombre", "Apellido", "FechaNacimiento", "Genero", "EstadoCivil", "Dni", "Direccion", "Celular", "Correo", "Peso", "Talla", "Temperatura", "Presion", "Saturacion", "EspecialidadAsignada", "MedicoAsignado", "NivelUrgencia"};
}
// Función para obtener una línea CSV
std::string Paciente::toCsvString() const
{
    return nombre + "," + apellido + "," + fechaNacimiento + "," + genero + "," + estadoCivil + "," + dni + "," + direccion + "," + celular + "," + correo + "," + std::to_string(peso) + "," + std::to_string(talla) + "," + std::to_string(temperatura) + "," + std::to_string(presion) + "," + std::to_string(saturacion) + "," + std::to_string(especialidadAsignada) + "," + medicoAsignado + "," + std::to_string(nivelUrgencia);
}

Paciente::Paciente(){};
Paciente::Paciente(const std::string &csvLine)
{
    std::stringstream ss(csvLine);
    std::string item;
    if (std::getline(ss, item, ','))
        nombre = item;
    if (std::getline(ss, item, ','))
        apellido = item;
    if (std::getline(ss, item, ','))
        fechaNacimiento = item;
    if (std::getline(ss, item, ','))
        genero = *item.data();
    if (std::getline(ss, item, ','))
        estadoCivil = *item.data();
    if (std::getline(ss, item, ','))
        dni = item;
    if (std::getline(ss, item, ','))
        direccion = item;
    if (std::getline(ss, item, ','))
        celular = item;
    if (std::getline(ss, item, ','))
        correo = item;
    if (std::getline(ss, item, ','))
        peso = std::stoi(item);
    if (std::getline(ss, item, ','))
        talla = std::stoi(item);
    if (std::getline(ss, item, ','))
        temperatura = std::stoi(item);
    if (std::getline(ss, item, ','))
        presion = std::stoi(item);
    if (std::getline(ss, item, ','))
        saturacion = std::stoi(item);
    if (std::getline(ss, item, ','))
        especialidadAsignada = std::stoi(item);
    if (std::getline(ss, item, ','))
        medicoAsignado = item;
    if (std::getline(ss, item, ','))
        nivelUrgencia = std::stoi(item);
}
