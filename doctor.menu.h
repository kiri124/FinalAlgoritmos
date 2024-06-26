#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "structures.h"
#include "utils.h"

using namespace std;
using namespace utils;

// Funcion para anadir un nuevo registro al historial medico
void agregarRegistroHistorial(const string &nombrePaciente, const HistorialMedico &registro);

// Funcion para buscar el historial medico por el nombre del paciente
vector<HistorialMedico> buscarHistorialPorNombre(const string &nombrePaciente);

// Funcion para mostrar el historial medico de un paciente
void mostrarHistorialMedico(const vector<HistorialMedico> &historial);

// Funcion para actualizar un registro especifico en el historial medico
void actualizarRegistroHistorial(const string &nombrePaciente, size_t indice, const HistorialMedico &nuevoRegistro);

// Funcion para mostrar el historial medico
void mostrarHistorialMedicoConIndices(const vector<HistorialMedico> &historial);

// Funcion para manejar la actualizacion del historial medico
void manejarActualizacionHistorialMedico();

// Funcion para administrar traslado
void manejarTraslado();

// Funcion para manejar la asignacion de recetas
void asignarReceta(vector<Receta> &recetas);

// Funcion para mostrar el menu del medico
void manejarMenuMedico(vector<Receta> &recetas);