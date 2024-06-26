#include <iostream>
#include <map>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <map>
#include <vector>
#include <thread>
#include "structures.h"
#include "database.h"
#include "data.h"
#include "utils.h"
#include "tree.node.h"

using namespace std;
using namespace utils;

// Estructura para almacenar los pacientes y su historial medico
map<string, vector<HistorialMedico>> historialPorNombre; // Usando el nombre como clave
btree::BTree<HistorialMedico> historialTree(3, "db/historial.txt");
database::Database<Receta> recetaDatabase("db/receta.txt");

// Funcion para anadir un nuevo registro al historial medico
void agregarRegistroHistorial(const string &nombrePaciente, const HistorialMedico &registro)
{
    historialTree.insert(registro.nombre, registro, 0);
    historialTree.writeToCSV();
    historialTree.readFromCSV();
}

// Funcion para buscar el historial medico por el nombre del paciente
vector<HistorialMedico> buscarHistorialPorNombre(const string &nombrePaciente)
{
    std::vector<HistorialMedico> result = historialTree.searchVector(nombrePaciente);
    return result;
}

// Funcion para mostrar el historial medico de un paciente
void mostrarHistorialMedico(const vector<HistorialMedico> &historial)
{
    std::cout << "\nHistorial Medico:" << endl;
    if (historial.empty())
    {
        std::cout << "El historial medico esta vacio." << endl;
    }
    else
    {
        for (size_t i = 0; i < historial.size(); ++i)
        {
            std::cout << "ID Consulta: " << to_string(historial[i].id) << endl;
            std::cout << "Fecha de consulta (formato dd/mm/aaaa): " << historial[i].fechaConsulta << endl;
            std::cout << "Motivo de consulta: " << historial[i].motivoConsulta << endl;
            std::cout << "Diagnostico: " << historial[i].diagnostico << endl;
            std::cout << "Tratamiento: " << historial[i].tratamiento << endl;
            std::cout << endl;
        }
    }
}

// Funcion para actualizar un registro especifico en el historial medico
void actualizarRegistroHistorial(HistorialMedico nuevoRegistro, const string &nombrePaciente, int indice)
{
    historialTree.remove(nombrePaciente, indice);
    historialTree.writeToCSV();
    historialTree.readFromCSV();
}

// Funcion para mostrar el historial medico
void mostrarHistorialMedicoConIndices(const HistorialMedico &historial)
{
    std::cout << "\nHistorial Medico:" << endl;
    size_t baseIndex = 0;
    cout << baseIndex + 1 << ". Fecha de consulta (formato dd/mm/aaaa): " << historial.fechaConsulta << endl;
    cout << baseIndex + 2 << ". Motivo de consulta: " << historial.motivoConsulta << endl;
    cout << baseIndex + 3 << ". Diagnostico: " << historial.diagnostico << endl;
    cout << baseIndex + 4 << ". Tratamiento: " << historial.tratamiento << endl;
    cout << endl;
}

// Funcion para manejar la actualizacion del historial medico
void manejarActualizacionHistorialMedico()
{
    string nombrePaciente;
    string idHistorial;
    int id = 0;
    std::cout << "Ingrese el nombre del paciente: ";
    std::cin.ignore();
    std::getline(std::cin, nombrePaciente);

    while (!esNombreValido(nombrePaciente))
    {
        std::cout << "Nombre no valido. Ingrese solo caracteres alfabeticos." << endl;
        std::cout << "Ingrese el nombre del paciente: ";
        std::getline(std::cin, nombrePaciente);
    }

    std::cout << "Ingrese el id de la consulta: ";
    std::cin >> idHistorial;
    id = stoi(idHistorial);
    std::vector<HistorialMedico> historial = historialTree.searchVector(nombrePaciente);
    if (historial.empty())
    {
        std::cout << "No se encontro historial medico para " << nombrePaciente << endl;
        return;
    }
    HistorialMedico nuevoRegistro;
    for (size_t i = 0; i < historial.size(); ++i)
    {
        if (historial[i].id == id)
        {
            nuevoRegistro = historial[i];
            break;
        }
    }
    mostrarHistorialMedicoConIndices(nuevoRegistro);
    size_t indice;
    std::cout << "Ingrese el numero de indice del registro que desea actualizar: ";
    std::cin >> indice;
    if (indice > 0 && indice <= 4)
    {
        switch (indice)
        {
        case 1:
            std::cout << "Ingrese la nueva fecha de consulta (formato dd/mm/aaaa): ";
            std::cin >> nuevoRegistro.fechaConsulta;
            break;
        case 2:
            std::cout << "Ingrese el nuevo motivo de consulta: ";
            std::cin.ignore();
            std::getline(std::cin, nuevoRegistro.motivoConsulta);
            break;
        case 3:
            std::cout << "Ingrese el nuevo diagnostico: ";
            std::cin.ignore();
            std::getline(std::cin, nuevoRegistro.diagnostico);
            break;
        case 4:
            std::cout << "Ingrese el nuevo tratamiento: ";
            std::cin.ignore();
            std::getline(std::cin, nuevoRegistro.tratamiento);
            break;
        default:
            std::cout << "Opcion no valida. Por favor, intente nuevamente." << endl;
            return;
        }

        actualizarRegistroHistorial(nuevoRegistro, nombrePaciente, id);

        historialTree.insert(nombrePaciente, nuevoRegistro, 0);
        historialTree.writeToCSV();
        historialTree.readFromCSV();
    }
    else
    {
        std::cout << "Indice fuera de rango." << endl;
    }
}

// Funcion para administrar traslado
void manejarTraslado()
{
    vector<Hospital> hospitales = {
        {"Hospital General Central", "123-456-789"},
        {"Clinica San Pedro", "987-654-321"},
        {"Hospital del Este", "456-789-123"},
        {"Clinica Santa Maria", "321-654-987"}};

    std::cout << "Lista de hospitales disponibles para traslado:" << endl;
    for (size_t i = 0; i < hospitales.size(); ++i)
    {
        std::cout << i + 1 << ". Nombre: " << hospitales[i].nombre << ", Contacto: " << hospitales[i].contacto << endl;
    }

    string nombrePaciente;
    bool nombreValido = false;

    while (!nombreValido)
    {
        std::cout << "Ingrese el nombre del paciente: ";
        std::cin.ignore();
        std::getline(std::cin, nombrePaciente);

        if (!nombrePaciente.empty() && isalpha(nombrePaciente[0]))
        {
            nombreValido = true;
        }
        else
        {
            std::cout << "Nombre no valido. Por favor, intente nuevamente." << endl;
        }
    }

    int opcion;
    bool opcionValida = false;

    while (!opcionValida)
    {
        std::cout << "Ingrese el numero del hospital al que desea trasladar al paciente: ";
        std::cin >> opcion;

        if (std::cin.fail() || opcion <= 0 || opcion > hospitales.size())
        {
            std::cin.clear();                                         // Limpiar el estado de error
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar el buffer de entrada
            std::cout << "Opcion no valida. Por favor, intente nuevamente." << endl;
        }
        else
        {
            opcionValida = true;
        }
    }

    std::cout << "Paciente " << nombrePaciente << " trasladado a " << hospitales[opcion - 1].nombre << " con contacto " << hospitales[opcion - 1].contacto << endl;
}

// Funcion para manejar la asignacion de recetas
void asignarReceta(vector<Receta> &recetas)
{
    Receta nuevaReceta;
    bool entradaValida;
    std::cin.ignore(); // Para limpiar cualquier caracter pendiente en el buffer de entrada

    // Validar nombre del paciente
    do
    {
        std::cout << "Ingrese nombre del paciente: ";
        std::getline(std::cin, nuevaReceta.nombrePaciente);
        entradaValida = esSoloLetrasYEspacios(nuevaReceta.nombrePaciente);
        if (!entradaValida)
        {
            std::cout << "Nombre incorrecto. Solo se permiten letras y espacios. Vuelva a ingresar." << endl;
        }
    } while (!entradaValida);

    // Validar medicamento
    do
    {
        std::cout << "Ingrese medicamento: ";
        std::getline(std::cin, nuevaReceta.medicamento);
        entradaValida = esSoloLetrasNumerosYEspacios(nuevaReceta.medicamento);
        if (!entradaValida)
        {
            std::cout << "Medicamento incorrecto. Solo se permiten letras, numeros y espacios. Vuelva a ingresar." << endl;
        }
    } while (!entradaValida);

    // Validar dosis
    do
    {
        std::cout << "Ingrese dosis: ";
        std::getline(std::cin, nuevaReceta.dosis);
        entradaValida = esSoloLetrasNumerosYEspacios(nuevaReceta.dosis);
        if (!entradaValida)
        {
            std::cout << "Dosis incorrecta. Solo se permiten letras, numeros y espacios. Vuelva a ingresar." << endl;
        }
    } while (!entradaValida);

    // Validar numero de dias
    do
    {
        std::cout << "Ingrese numero de dias que debe tomarse: ";
        std::cin >> nuevaReceta.numeroDias;
        if (std::cin.fail() || nuevaReceta.numeroDias <= 0)
        {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Numero de dias incorrecto. Debe ser un numero positivo. Vuelva a ingresar." << endl;
            entradaValida = false;
        }
        else
        {
            entradaValida = true;
            std::cin.ignore(); // Limpiar el buffer de entrada
        }
    } while (!entradaValida);

    // Validar cada cuantas horas debe tomarse
    do
    {
        std::cout << "Ingrese cada cuantas horas debe tomarse: ";
        std::cin >> nuevaReceta.cadaCuantasHoras;
        if (std::cin.fail() || nuevaReceta.cadaCuantasHoras <= 0)
        {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Numero de horas incorrecto. Debe ser un numero positivo. Vuelva a ingresar." << endl;
            entradaValida = false;
        }
        else
        {
            entradaValida = true;
            std::cin.ignore(); // Limpiar el buffer de entrada
        }
    } while (!entradaValida);

    recetas.push_back(nuevaReceta);
    recetaDatabase.writeCsv(recetas);
    std::cout << "Receta asignada con exito." << endl;
}

// Funcion para mostrar el menu del medico
void manejarMenuMedico(vector<Receta> &recetas)
{
    int opcion;
    historialTree.readFromCSV();
    vector<HistorialMedico> historial;
    HistorialMedico nuevoRegistro;

    do
    {
        std::cout << "\nMenu de personal medico" << endl;
        std::cout << "1. Crear historial medico para un paciente" << endl;
        std::cout << "2. Buscar historial medico" << endl;
        std::cout << "3. Actualizar historial medico" << endl;
        std::cout << "4. Asignar receta a paciente" << endl;
        std::cout << "5. Traslado de paciente" << endl;
        std::cout << "6. Salir" << endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        if (std::cin.fail())
        {
            // Limpiar el buffer de entrada
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Entrada no valida. Por favor, ingrese un numero valido." << endl;
            continue;
        }

        switch (opcion)
        {
        case 1:
        {
            string nombrePaciente;
            bool nombreValido = false;

            std::cout << "Ingrese el nombre del paciente: ";
            std::cin.ignore(); // Limpiar el buffer del teclado antes de la entrada del nombre

            while (!nombreValido)
            {
                std::getline(std::cin, nombrePaciente);

                if (esNombreValido(nombrePaciente))
                {
                    nombreValido = true;
                }
                else
                {
                    std::cout << "Nombre no valido. Solo se permiten letras y espacios." << endl;
                    std::cout << "Ingrese el nombre del paciente: ";
                }
            }
            HistorialMedico nuevoRegistro;
            nuevoRegistro.nombre = nombrePaciente;
            std::cout << "Fecha de consulta (formato dd/mm/aaaa): ";
            std::getline(std::cin, nuevoRegistro.fechaConsulta);
            std::cout << "Motivo de consulta: ";
            std::getline(std::cin, nuevoRegistro.motivoConsulta);
            std::cout << "Diagnostico: ";
            std::getline(std::cin, nuevoRegistro.diagnostico);
            std::cout << "Tratamiento: ";
            std::getline(std::cin, nuevoRegistro.tratamiento);

            agregarRegistroHistorial(nombrePaciente, nuevoRegistro);
            std::cout << "Historial medico creado con exito." << endl;
            break;
        }
        case 2:
        {
            string nombrePaciente;
            std::cout << "Ingrese el nombre del paciente: ";
            std::cin.ignore();
            std::getline(std::cin, nombrePaciente);

            vector<HistorialMedico> historial = buscarHistorialPorNombre(nombrePaciente);
            if (!historial.empty())
            {
                mostrarHistorialMedico(historial);
            }
            else
            {
                std::cout << "No se encontro historial medico para " << nombrePaciente << endl;
            }
            break;
        }
        case 3:
            manejarActualizacionHistorialMedico();
            break;
        case 4:
            // Declarar vector de recetas para almacenar las recetas asignadas
            static vector<Receta> recetas;
            recetaDatabase.readCsv(recetas);
            asignarReceta(recetas);
            break;
        case 5:
            manejarTraslado();
            break;
        case 6:
            std::cout << "Saliendo... ";
            break;
        }
    } while (opcion != 6);
}
