#include <iostream>
#include <string>
#include "structures.h"
#include "utils.h"
#include <cctype>
#include <iomanip>
#include <limits>
#include <map>

using namespace std;
using namespace utils;

// Funcion para registrar datos del paciente con validaciones
void registrarDatosPaciente(Paciente &paciente);
// Funcion para actualizar los datos de un paciente
void actualizarDatosPaciente(Paciente &paciente);
// Funcion para registrar el triaje de un paciente
void registrarTriaje(Paciente &paciente);
// Funcion para mostrar el triaje de un paciente
void mostrarTriaje(const Paciente &paciente);
// Funcion para mostrar los datos del paciente en un cuadro
void mostrarDatosPaciente(const Paciente &paciente);
// Funcion para asignar especialidad y medico al paciente
void asignarEspecialidadYMedico(Paciente &paciente);
// Funcion para asignar un lugar en la lista de espera al paciente
void lugarEnListaEspera(vector<Paciente> &listaEspera, Paciente &paciente);
// Funcion para eliminar a un paciente de la lista de espera
void eliminarPacienteDeLista(vector<Paciente> &listaEspera);
// Funcion para mostrar el menu de la enfermera
void manejarMenuEnfermera(vector<Paciente> &listaEspera);