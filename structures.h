#include <iostream>

#ifndef STRUCTURES_H
#define STRUCTURES_H

using namespace std;

// Estuctura para almacenar datos de hospitales de traslado
struct Hospital
{
  std::string nombre;
  std::string contacto;
};

// Estructura para almacenar los datos del paciente
struct Paciente
{
  // Datos Personales
  string nombre;
  string apellido;
  string fechaNacimiento;
  char genero;
  char estadoCivil;
  string dni;
  string direccion;
  string celular;
  string correo;

  // Datos Medicos
  float peso;
  float talla;
  float temperatura;
  float presion;
  float saturacion;

  // Asignaciones
  int especialidadAsignada;
  std::string medicoAsignado;
  int nivelUrgencia;
};

// Estructura para almacenar los datos de los usuarios
struct Usuario
{
  string tipo; // 'medico' o 'enfermera'
  string nombre;
  string contrasena;
  Usuario *siguiente;

  // Función para obtener las cabezas de una línea CSV
  std::vector<std::string> getHeaders() const;
  // Función para obtener una línea CSV
  std::string toCsvString() const;

  Usuario();
  Usuario(const std::string &csvLine);
};

// Estructura para almacenar las recetas
struct Receta
{
  string nombrePaciente;
  string medicamento;
  string dosis;
  int numeroDias;
  int cadaCuantasHoras;
};

// Estructura para almacenar el historial medico de un paciente
struct HistorialMedico
{
  string fechaConsulta;
  string motivoConsulta;
  string diagnostico;
  string tratamiento;
};

struct Person
{
  std::string name;
  int age;
  std::string city;

  // Función para obtener las cabezas de una línea CSV
  std::vector<std::string> getHeaders() const;
  // Función para obtener una línea CSV de Person
  std::string toCsvString() const;

  // Constructor
  Person(const std::string &name, int age, const std::string &city);
  // Constructor que toma una línea CSV
  Person(const std::string &csvLine);
};

#endif