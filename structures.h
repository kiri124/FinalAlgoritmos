// #include <iostream>
// #include <vector>

// #ifndef STRUCTURES_H
// #define STRUCTURES_H

// using namespace std;

// Estuctura para almacenar datos de hospitales de traslado
// struct Hospital
// {
//   std::string nombre;
//   std::string contacto;
// };

// Estructura para almacenar los datos del paciente
// struct Paciente
// {
//   // Datos Personales
//   string nombre;
//   string apellido;
//   string fechaNacimiento;
//   char genero;
//   char estadoCivil;
//   string dni;
//   string direccion;
//   string celular;
//   string correo;

//   // Datos Medicos
//   float peso;
//   float talla;
//   float temperatura;
//   float presion;
//   float saturacion;

//   // Asignaciones
//   int especialidadAsignada;
//   std::string medicoAsignado;
//   int nivelUrgencia;

//   // Función para obtener las cabezas de una línea CSV
//   std::vector<std::string> getHeaders() const;
//   // Función para obtener una línea CSV
//   std::string toCsvString() const;

//   Paciente();
//   Paciente(const std::string &csvLine);
// };

// Estructura para almacenar los datos de los usuarios
// struct Usuario
// {
//   string tipo; // 'medico' o 'enfermera'
//   string nombre;
//   string contrasena;
//   Usuario *siguiente;

//   // Función para obtener las cabezas de una línea CSV
//   std::vector<std::string> getHeaders() const;
//   // Función para obtener una línea CSV
//   std::string toCsvString() const;

//   Usuario();
//   Usuario(const std::string &csvLine);
// };

// Estructura para almacenar las recetas
// struct Receta
// {
//   string nombrePaciente;
//   string medicamento;
//   string dosis;
//   int numeroDias;
//   int cadaCuantasHoras;
//   // Función para obtener las cabezas de una línea CSV
//   std::vector<std::string> getHeaders() const;
//   // Función para obtener una línea CSV
//   std::string toCsvString() const;

//   Receta();
//   Receta(const std::string &csvLine);
// };

// Estructura para almacenar el historial medico de un paciente
// struct HistorialMedico
// {
//   int id;
//   string nombre;
//   string fechaConsulta;
//   string motivoConsulta;
//   string diagnostico;
//   string tratamiento;
//   // Función para obtener las cabezas de una línea CSV
//   std::vector<std::string> getHeaders() const;
//   // Función para obtener una línea CSV
//   std::string toCsvString() const;
//   friend std::ostream &operator<<(std::ostream &os, const HistorialMedico &historial)
//   {
//     os << historial.nombre << "," << historial.fechaConsulta << "," << historial.motivoConsulta << "," << historial.diagnostico << "," << historial.tratamiento;
//     return os;
//   }
// };

// class Person
// {
// public:
//   std::string name;
//   int age;

//   Person(std::string name, int age) : name(name), age(age) {}
//   Person(){};
//   Person(const std::string &csvLine);
//   friend std::ostream &operator<<(std::ostream &os, const Person &person)
//   {
//     os << person.name << person.age;
//     return os;
//   }
// };

/*/////////////////////////////////////////////////////*/

#include <iostream>
#include <vector>

#ifndef STRUCTURES_H
#define STRUCTURES_H

// Estructura abstracta para definir métodos comunes
class DataStructure
{
public:
  virtual std::vector<std::string> getHeaders() const = 0;
  virtual std::string toCsvString() const = 0;
  virtual ~DataStructure() {} // Destructor virtual para la clase base
};

// Estructura para almacenar datos de hospitales de traslado
struct Hospital
{
  std::string nombre;
  std::string contacto;
};

// Estructura para almacenar los datos del paciente
struct Paciente : public DataStructure
{
  // Datos Personales
  std::string nombre;
  std::string apellido;
  std::string fechaNacimiento;
  char genero;
  char estadoCivil;
  std::string dni;
  std::string direccion;
  std::string celular;
  std::string correo;

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

  // Implementación de métodos virtuales puros de DataStructure
  std::vector<std::string> getHeaders() const override;

  std::string toCsvString() const override;
  Paciente();
  Paciente(const std::string &csvLine);
};

// Estructura para almacenar los datos de los usuarios
struct Usuario : public DataStructure
{
  std::string tipo; // 'medico' o 'enfermera'
  std::string nombre;
  std::string contrasena;
  Usuario *siguiente;

  // Implementación de métodos virtuales puros de DataStructure
  std::vector<std::string> getHeaders() const override;

  std::string toCsvString() const override;
  Usuario();
  Usuario(const std::string &csvLine);
};

// Estructura para almacenar las recetas
struct Receta : public DataStructure
{
  std::string nombrePaciente;
  std::string medicamento;
  std::string dosis;
  int numeroDias;
  int cadaCuantasHoras;

  // Implementación de métodos virtuales puros de DataStructure
  std::vector<std::string> getHeaders() const override;

  std::string toCsvString() const override;
  Receta();
  Receta(const std::string &csvLine);
};

// Estructura para almacenar el historial medico de un paciente
struct HistorialMedico : public DataStructure
{
  int id;
  std::string nombre;
  std::string fechaConsulta;
  std::string motivoConsulta;
  std::string diagnostico;
  std::string tratamiento;

  // Implementación de métodos virtuales puros de DataStructure
  std::vector<std::string> getHeaders() const override;

  std::string toCsvString() const override;

  friend std::ostream &operator<<(std::ostream &os, const HistorialMedico &historial)
  {
    os << historial.nombre << "," << historial.fechaConsulta << "," << historial.motivoConsulta << "," << historial.diagnostico << "," << historial.tratamiento;
    return os;
  }

  HistorialMedico();
  HistorialMedico(const std::string &csvLine);
};

#endif // STRUCTURES_H
