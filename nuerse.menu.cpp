#include <iostream>
#include <string>
#include "structures.h"
#include "utils.h"
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <map>
#include "tree.node.h"
#include "database.h"

using namespace std;
using namespace utils;

database::Database<Paciente> pacienteDatabase("db/pacientes.txt");

// Funcion para registrar datos del paciente con validaciones
void registrarDatosPaciente(Paciente &paciente)
{
    cout << "Registrando datos del paciente..." << endl;
    // Ingresar el nombre
    cout << "Nombre: ";
    cin.ignore(); // Limpiar el buffer del teclado
    getline(cin, paciente.nombre);
    while (!esNombreValido(paciente.nombre))
    {
        cout << "Nombre no valido. Ingrese solo caracteres alfabeticos." << endl;
        cout << "Nombre: ";
        getline(cin, paciente.nombre);
    }
    // Ingresar el apellido
    cout << "Apellido: ";
    getline(cin, paciente.apellido);
    while (!esNombreValido(paciente.apellido))
    {
        cout << "Apellido no valido. Ingrese solo caracteres alfabeticos." << endl;
        cout << "Apellido: ";
        getline(cin, paciente.apellido);
    }
    // Ingresa la fecha de nacimiento
    cout << "Fecha de nacimiento (formato dd/mm/aaaa): ";
    cin >> paciente.fechaNacimiento;
    // Ingresa el genero
    cout << "Genero (M/F): ";
    do
    {
        cin >> paciente.genero;
        if (!esGeneroValido(paciente.genero))
        {
            cout << "Genero no valido. Por favor, ingrese 'M' o 'F'." << endl;
            cout << "Genero (M/F): ";
        }
    } while (!esGeneroValido(paciente.genero));

    cout << "Estado civil (S/C/V/D): ";
    do
    {
        cin >> paciente.estadoCivil;
        if (!esEstadoCivilValido(paciente.estadoCivil))
        {
            cout << "Estado civil no valido. Por favor, ingrese 'S', 'C', 'V' o 'D'." << endl;
            cout << "Estado civil (S/C/V/D): ";
        }
    } while (!esEstadoCivilValido(paciente.estadoCivil));

    do
    {
        cout << "DNI (8 digitos): ";
        cin >> paciente.dni;
        if (!esDniValido(paciente.dni))
        {
            cout << "DNI no valido. Intente nuevamente." << endl;
        }
    } while (!esDniValido(paciente.dni));

    cin.ignore(); // Limpiar el buffer del teclado

    // Ingresa la direccion
    cout << "Direccion: ";
    getline(cin, paciente.direccion);
    // Ingresa el numero de celular
    do
    {
        cout << "Celular (9 digitos): ";
        cin >> paciente.celular;
        if (!esCelularValido(paciente.celular))
        {
            cout << "Celular no valido. Intente nuevamente." << endl;
        }
    } while (!esCelularValido(paciente.celular));

    cout << "Correo electronico: ";
    cin >> paciente.correo;
}

// Funcion para actualizar los datos de un paciente
void actualizarDatosPaciente(Paciente &paciente)
{
    int opcion;
    do
    {
        cout << "Seleccione el dato que desea actualizar:" << endl;
        cout << "1. Nombre" << endl;
        cout << "2. Apellido" << endl;
        cout << "3. Fecha de nacimiento" << endl;
        cout << "4. Genero" << endl;
        cout << "5. Estado civil" << endl;
        cout << "6. DNI" << endl;
        cout << "7. Direccion" << endl;
        cout << "8. Celular" << endl;
        cout << "9. Correo electronico" << endl;
        cout << "10. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        cin.ignore();

        switch (opcion)
        {
        case 1:
            cout << "Nuevo nombre: ";
            do
            {
                getline(cin, paciente.nombre);
                if (!esNombreValido(paciente.nombre))
                {
                    cout << "Nombre no valido. Por favor, ingrese solo caracteres alfabeticos." << endl;
                    cout << "Nuevo nombre: ";
                }
            } while (!esNombreValido(paciente.nombre));
            break;
        case 2:
            cout << "Nuevo apellido: ";
            do
            {
                getline(cin, paciente.apellido);
                if (!esNombreValido(paciente.apellido))
                {
                    cout << "Apellido no valido. Por favor, ingrese solo caracteres alfabeticos." << endl;
                    cout << "Nuevo apellido: ";
                }
            } while (!esNombreValido(paciente.apellido));
            break;
        case 3:
            cout << "Nueva fecha de nacimiento (formato dd/mm/aaaa): ";
            cin >> paciente.fechaNacimiento;
            break;
        case 4:
            cout << "Nuevo genero (M/F): ";
            do
            {
                cin >> paciente.genero;
                if (!esGeneroValido(paciente.genero))
                {
                    cout << "Genero no valido. Por favor, ingrese 'M' o 'F'." << endl;
                    cout << "Nuevo genero (M/F): ";
                }
            } while (!esGeneroValido(paciente.genero));
            break;
        case 5:
            cout << "Nuevo estado civil (S/C/V/D): ";
            do
            {
                cin >> paciente.estadoCivil;
                if (!esEstadoCivilValido(paciente.estadoCivil))
                {
                    cout << "Estado civil no valido. Por favor, ingrese 'S', 'C', 'V' o 'D'." << endl;
                    cout << "Nuevo estado civil (S/C/V/D): ";
                }
            } while (!esEstadoCivilValido(paciente.estadoCivil));
            break;
        case 6:
            do
            {
                cout << "Nuevo DNI (8 digitos): ";
                cin >> paciente.dni;
                if (!esDniValido(paciente.dni))
                {
                    cout << "DNI no valido. Intente nuevamente." << endl;
                }
            } while (!esDniValido(paciente.dni));
            break;
        case 7:
            cout << "Nueva direccion: ";
            cin.ignore(); // Limpiar el buffer
            getline(cin, paciente.direccion);
            break;
        case 8:
            do
            {
                cout << "Nuevo celular (9 digitos): ";
                cin >> paciente.celular;
                if (!esCelularValido(paciente.celular))
                {
                    cout << "Celular no valido. Intente nuevamente." << endl;
                }
            } while (!esCelularValido(paciente.celular));
            break;
        case 9:
            cout << "Nuevo correo electronico: ";
            cin >> paciente.correo;
            break;
        case 10:
            cout << "Saliendo de la actualizacion de datos..." << endl;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    } while (opcion != 10);
}

// Funcion para registrar el triaje de un paciente
void registrarTriaje(Paciente &paciente)
{
    string nombrePaciente;
    bool nombreValido = false;
    cin.ignore(); // Limpiar el buffer de entrada

    // Leer y validar el nombre del paciente
    do
    {
        cout << "Ingrese el nombre del paciente: ";
        getline(cin, nombrePaciente);
        if (!esNombreValido(nombrePaciente))
        {
            cout << "El nombre debe contener solo letras." << endl;
        }
        else
        {
            nombreValido = true;
            paciente.nombre = nombrePaciente; // Guardar el nombre del paciente
        }
    } while (!nombreValido);

    cout << "Peso (kg): ";
    while (!(cin >> paciente.peso))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada no valida
        cout << "Entrada no valida. Por favor, ingrese un numero para el peso: ";
    }

    cout << "Talla (m): ";
    while (!(cin >> paciente.talla))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada no valida. Por favor, ingrese un numero para la talla: ";
    }

    cout << "Temperatura (C): ";
    while (!(cin >> paciente.temperatura))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada no valida. Por favor, ingrese un numero para la temperatura: ";
    }

    cout << "Presion arterial (mmHg): ";
    while (!(cin >> paciente.presion))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada no valida. Por favor, ingrese un numero para la presion arterial: ";
    }

    cout << "Saturacion de oxigeno (%): ";
    while (!(cin >> paciente.saturacion))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada no valida. Por favor, ingrese un numero para la saturacion de oxigeno: ";
    }
}

// Funcion para mostrar el triaje de un paciente
void mostrarTriaje(const Paciente &paciente)
{
    const int ancho = 50; // Ancho del cuadro
    cout << string(ancho, '-') << endl;
    cout << "| " << left << setw(ancho - 8) << "Datos de triaje del paciente:" << " |" << endl;
    cout << string(ancho, '-') << endl;
    cout << "| Peso (kg): " << left << setw(ancho - 17) << paciente.peso << " |" << endl;
    cout << "| Talla (m): " << left << setw(ancho - 17) << paciente.talla << " |" << endl;
    cout << "| Temperatura (C): " << left << setw(ancho - 22) << paciente.temperatura << " |" << endl;
    cout << "| Presion arterial (mmHg): " << left << setw(ancho - 29) << paciente.presion << " |" << endl;
    cout << "| Saturacion de oxigeno (%): " << left << setw(ancho - 31) << paciente.saturacion << " |" << endl;
    cout << string(ancho, '-') << endl;
}

// Funcion para mostrar los datos del paciente en un cuadro
void mostrarDatosPaciente(const Paciente &paciente)
{
    const int ancho = 50; // Ancho del cuadro
    cout << string(ancho, '-') << endl;
    cout << "| " << left << setw(ancho - 4) << "Datos del paciente:" << " |" << endl;
    cout << string(ancho, '-') << endl;
    cout << "| Nombre: " << left << setw(ancho - 12) << paciente.nombre << " |" << endl;
    cout << "| Apellido: " << left << setw(ancho - 12) << paciente.apellido << " |" << endl;
    cout << "| Fecha de nacimiento: " << left << setw(ancho - 26) << paciente.fechaNacimiento << " |" << endl;
    cout << "| Genero: " << left << setw(ancho - 10) << paciente.genero << " |" << endl;
    cout << "| Estado civil: " << left << setw(ancho - 16) << paciente.estadoCivil << " |" << endl;
    cout << "| DNI: " << left << setw(ancho - 9) << paciente.dni << " |" << endl;
    cout << "| Direccion: " << left << setw(ancho - 13) << paciente.direccion << " |" << endl;
    cout << "| Celular: " << left << setw(ancho - 12) << paciente.celular << " |" << endl;
    cout << "| Correo electronico: " << left << setw(ancho - 24) << paciente.correo << " |" << endl;
    cout << string(ancho, '-') << endl;
}

// Funcion para asignar especialidad y medico al paciente
void asignarEspecialidadYMedico(Paciente &paciente)
{
    cout << "Ingrese el nombre del paciente: ";
    cin.ignore(); // Limpiar el buffer del teclado
    getline(cin, paciente.nombre);
    while (!esNombreValido(paciente.nombre))
    {
        cout << "Nombre no valido. Ingrese solo caracteres alfabeticos." << endl;
        cout << "Ingrese el nombre del paciente: ";
        getline(cin, paciente.nombre);
    }

    cout << "Especialidades disponibles\n";
    cout << "1. Medicina general\n";
    cout << "2. Obstetricia\n";
    cout << "3. Podologia\n";
    cout << "4. Pediatria\n";
    cout << "5. Cardiologia\n";
    cout << "6. Odontologia\n";
    cout << "7. Nutricion\n";
    cout << "8. Terapia fisica\n";
    cout << "9. Traumatologia\n";
    cout << "10. Psicologia\n";
    cout << "Ingrese el numero correspondiente a la especialidad asignada: ";

    while (true)
    {
        string input;
        getline(cin, input);

        try
        {
            paciente.especialidadAsignada = stoi(input);
            if (paciente.especialidadAsignada >= 1 && paciente.especialidadAsignada <= 10)
            {
                break;
            }
            else
            {
                cout << "Numero no valido. Por favor, ingrese un numero valido de especialidad." << endl;
                cout << "Ingrese el numero correspondiente a la especialidad asignada: ";
            }
        }
        catch (invalid_argument &e)
        {
            cout << "Entrada no valida. Por favor, ingrese un numero valido de especialidad." << endl;
            cout << "Ingrese el numero correspondiente a la especialidad asignada: ";
        }
        catch (out_of_range &e)
        {
            cout << "Numero fuera de rango. Por favor, ingrese un numero valido de especialidad." << endl;
            cout << "Ingrese el numero correspondiente a la especialidad asignada: ";
        }
    }

    cout << "Ingrese el nombre del medico asignado: ";
    cin.ignore(); // Limpiar el buffer del teclado
    getline(cin, paciente.medicoAsignado);
    while (!esNombreValido(paciente.medicoAsignado))
    {
        cout << "Nombre no valido. Ingrese solo caracteres alfabeticos." << endl;
        cout << "Ingrese el nombre del medico asignado: ";
        getline(cin, paciente.medicoAsignado);
    }
    cout << "Especialidad y medico asignados con exito." << endl;
}

// Funcion para asignar un lugar en la lista de espera al paciente
void lugarEnListaEspera(vector<Paciente> &listaEspera, Paciente &paciente)
{
    cout << "Ingrese el nombre del paciente: ";
    cin.ignore(); // Limpiar el buffer del teclado
    getline(cin, paciente.nombre);
    while (!esNombreValido(paciente.nombre))
    {
        cout << "Nombre no valido. Ingrese solo caracteres alfabeticos." << endl;
        cout << "Ingrese el nombre del paciente: ";
        getline(cin, paciente.nombre);
    }

    cout << "Niveles de urgencia\n"
         << "1. Resucitacion\n"
         << "2. Emergencia\n"
         << "3. Urgencia\n"
         << "4. Urgencia menor\n"
         << "5. Sin urgencia\n"
         << "Indique el nivel de urgencia: ";
    cin >> paciente.nivelUrgencia;

    while (cin.fail() || paciente.nivelUrgencia < 1 || paciente.nivelUrgencia > 5)
    {
        cerr << "Nivel de urgencia no valido. Por favor, ingrese un valor entre 1 y 5." << endl;
        cout << "Indique el nivel de urgencia: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> paciente.nivelUrgencia;
    }

    auto it = find_if(listaEspera.begin(), listaEspera.end(), [&paciente](const Paciente &p)
                      { return p.nivelUrgencia > paciente.nivelUrgencia; });

    listaEspera.insert(it, paciente);
    cout << "El paciente ha sido ubicado en la lista de espera con exito." << endl;
}

// Funcion para eliminar a un paciente de la lista de espera
void eliminarPacienteDeLista(vector<Paciente> &listaEspera)
{
    cout << "Ingrese el nombre del paciente a eliminar: ";
    cin.ignore(); // Limpiar el buffer del teclado
    string nombre;
    getline(cin, nombre);
    while (!esNombreValido(nombre))
    {
        cout << "Nombre no valido. Ingrese solo caracteres alfabeticos." << endl;
        cout << "Ingrese el nombre del paciente: ";
        getline(cin, nombre);
    }

    auto it = find_if(listaEspera.begin(), listaEspera.end(), [&nombre](const Paciente &p)
                      { return p.nombre == nombre; });

    if (it != listaEspera.end())
    {
        listaEspera.erase(it);
        cout << "El paciente ha sido eliminado de la lista de espera.\n";
    }
    else
    {
        cout << "Paciente no encontrado en la lista de espera.\n";
    }
}

// Funcion para mostrar el menu de la enfermera
void manejarMenuEnfermera(vector<Paciente> &listaEspera)
{
    // btree::BTree<Paciente> pacienteTree(3, "db/listaEspera.txt");
    // pacienteTree.readFromCSV();
    Paciente paciente;
    int opcion;
    do
    {
        cout << "\nMenu de personal de enfermeria" << endl;
        cout << "1. Registrar datos del paciente" << endl;
        cout << "2. Triaje" << endl;
        cout << "3. Actualizar datos de registro" << endl;
        cout << "4. Mostrar datos del paciente" << endl;
        cout << "5. Asignar especialidad y medico" << endl;
        cout << "6. Actualizar lista de espera" << endl;
        cout << "7. Eliminar paciente de lista de espera" << endl;
        cout << "8. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            registrarDatosPaciente(paciente);
            break;
        case 2:
            cout << "Registro de triaje..." << endl;
            registrarTriaje(paciente);
            break;
        case 3:
            cout << "Actualizando datos de registro..." << endl;
            actualizarDatosPaciente(paciente);
            break;
        case 4:
            cout << "Mostrando datos del paciente..." << endl;
            mostrarDatosPaciente(paciente);
            mostrarTriaje(paciente);
            break;
        case 5:
            cout << "Asignando especialidad y medico..." << endl;
            asignarEspecialidadYMedico(paciente);
            break;
        case 6:
            cout << "Actualizando lista de espera dependiendo su nivel de emergencia..." << endl;
            lugarEnListaEspera(listaEspera, paciente);
            break;
        case 7:
            cout << "Eliminando paciente de lista de espera..." << endl;
            eliminarPacienteDeLista(listaEspera);
            break;
        case 8:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    } while (opcion != 8);
}
