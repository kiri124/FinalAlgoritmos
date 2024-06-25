#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>
#include <map>
#include <vector>
#include <algorithm>
#include "structures.h"
#include "utils.h"
#include "database.h"

using namespace std;

database::Database<Usuario> dbUsuario;

// Declaracion de la funcion para mostrar el menu del medico
extern void manejarMenuMedico(vector<Receta> &recetas);
// Declaracion de la funcion para mostrar el menu del medico
void manejarMenuMedico();
// Vector para la lista de espera
vector<Paciente> listaEspera;
// Estructura para almacenar los pacientes y su historial medico
map<string, vector<HistorialMedico>> historialPorNombre; // Usando el nombre como clave

// Funcion para manejar la asignacion de recetas
void asignarReceta(vector<Receta> &recetas)
{
  Receta nuevaReceta;
  bool entradaValida;
  cin.ignore(); // Para limpiar cualquier caracter pendiente en el buffer de entrada

  // Validar nombre del paciente
  do
  {
    cout << "Ingrese nombre del paciente: ";
    getline(cin, nuevaReceta.nombrePaciente);
    entradaValida = esSoloLetrasYEspacios(nuevaReceta.nombrePaciente);
    if (!entradaValida)
    {
      cout << "Nombre incorrecto. Solo se permiten letras y espacios. Vuelva a ingresar." << endl;
    }
  } while (!entradaValida);

  // Validar medicamento
  do
  {
    cout << "Ingrese medicamento: ";
    getline(cin, nuevaReceta.medicamento);
    entradaValida = esSoloLetrasNumerosYEspacios(nuevaReceta.medicamento);
    if (!entradaValida)
    {
      cout << "Medicamento incorrecto. Solo se permiten letras, numeros y espacios. Vuelva a ingresar." << endl;
    }
  } while (!entradaValida);

  // Validar dosis
  do
  {
    cout << "Ingrese dosis: ";
    getline(cin, nuevaReceta.dosis);
    entradaValida = esSoloLetrasNumerosYEspacios(nuevaReceta.dosis);
    if (!entradaValida)
    {
      cout << "Dosis incorrecta. Solo se permiten letras, numeros y espacios. Vuelva a ingresar." << endl;
    }
  } while (!entradaValida);

  // Validar numero de dias
  do
  {
    cout << "Ingrese numero de dias que debe tomarse: ";
    cin >> nuevaReceta.numeroDias;
    if (cin.fail() || nuevaReceta.numeroDias <= 0)
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Numero de dias incorrecto. Debe ser un numero positivo. Vuelva a ingresar." << endl;
      entradaValida = false;
    }
    else
    {
      entradaValida = true;
      cin.ignore(); // Limpiar el buffer de entrada
    }
  } while (!entradaValida);

  // Validar cada cuantas horas debe tomarse
  do
  {
    cout << "Ingrese cada cuantas horas debe tomarse: ";
    cin >> nuevaReceta.cadaCuantasHoras;
    if (cin.fail() || nuevaReceta.cadaCuantasHoras <= 0)
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Numero de horas incorrecto. Debe ser un numero positivo. Vuelva a ingresar." << endl;
      entradaValida = false;
    }
    else
    {
      entradaValida = true;
      cin.ignore(); // Limpiar el buffer de entrada
    }
  } while (!entradaValida);

  recetas.push_back(nuevaReceta);
  cout << "Receta asignada con exito." << endl;
}

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

// Funcion para crear un nuevo usuario
Usuario *crearUsuario(string tipo, string nombre, string contrasena)
{
  Usuario *nuevo = new Usuario;
  nuevo->tipo = tipo;
  nuevo->nombre = nombre;
  nuevo->contrasena = contrasena;
  nuevo->siguiente = nullptr;
  return nuevo;
}

// Funcion para añadir un usuario a la lista
void agregarUsuario(Usuario *&cabeza, string tipo, string nombre, string contrasena)
{
  Usuario *nuevo = crearUsuario(tipo, nombre, contrasena);
  nuevo->siguiente = cabeza;
  cabeza = nuevo;
}
void agregarUsuario_(vector<Usuario> &cabeza, string tipo, string nombre, string contrasena)
{
  Usuario *nuevo = crearUsuario(tipo, nombre, contrasena);
  cabeza.push_back(*nuevo);
  dbUsuario.writeCsv("./db/usuarios.txt", cabeza);
  delete nuevo;
}

// Funcion para pedir los datos del usuario
void pedirDatos(string &nombre, string &contrasena)
{
  cout << "Ingrese nombre: ";
  cin >> nombre;

  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer del teclado

  cout << "Ingrese contraseña (debe tener al menos 6 caracteres): ";
  cin >> contrasena;
  while (contrasena.length() < 6)
  {
    cout << "La contraseña debe tener al menos 6 caracteres. Por favor, ingrese una contraseña valida: ";
    cin >> contrasena;
  }
}

// Funcion para validar las credenciales
bool validarCredenciales(Usuario *cabeza, string nombre, string contrasena)
{
  Usuario *actual = cabeza;
  while (actual != nullptr)
  {
    if (actual->nombre == nombre && actual->contrasena == contrasena)
    {
      return true;
    }
    actual = actual->siguiente;
  }
  return false;
}

// Funcion para liberar memoria de la lista de usuarios
void liberarMemoria(Usuario *&cabeza)
{
  while (cabeza != nullptr)
  {
    Usuario *temp = cabeza;
    cabeza = cabeza->siguiente;
    delete temp;
  }
}

// Funcion para mostrar el menu de la enfermera
void manejarMenuEnfermera(Paciente &paciente, vector<Paciente> &listaEspera)
{
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

// Funcion para mostrar el menu y gestionar el ingreso de usuarios
void mostrarMenuIngreso(Usuario *&listaMedicos, Usuario *&listaEnfermeras, Paciente &paciente)
{
  int opcion;
  vector<Receta> recetas;

  do
  {
    cout << "***********" << endl;
    cout << "Policlinico San Vicente de Paul" << endl;
    cout << "***********" << endl;
    cout << "1. Ingresar como personal medico" << endl;
    cout << "2. Ingresar como personal de enfermeria" << endl;
    cout << "3. Registrarse como personal medico" << endl;
    cout << "4. Registrarse como personal de enfermeria" << endl;
    cout << "5. Salir" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opcion;

    if (cin.fail())
    {
      // Limpiar el buffer de entrada
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Entrada no valida. Por favor, ingrese un numero valido." << endl;
      continue;
    }

    switch (opcion)
    {
    case 1:
    {
      string nombre, contrasena;
      bool credencialesValidas = false;
      do
      {
        pedirDatos(nombre, contrasena);
        if (validarCredenciales(listaMedicos, nombre, contrasena))
        {
          cout << "Acceso concedido al medico" << endl;
          manejarMenuMedico(recetas);
          credencialesValidas = true;
        }
        else
        {
          cout << "Credenciales de medico incorrectas. Intente nuevamente." << endl;
        }
      } while (!credencialesValidas);
      break;
    }
    case 2:
    {
      string nombre, contrasena;
      bool credencialesValidas = false;
      do
      {
        pedirDatos(nombre, contrasena);
        if (validarCredenciales(listaEnfermeras, nombre, contrasena))
        {
          cout << "Acceso concedido al enfermero" << endl;
          manejarMenuEnfermera(paciente, listaEspera);
          credencialesValidas = true;
        }
        else
        {
          cout << "Credenciales de enfermero incorrectas. Intente nuevamente." << endl;
        }
      } while (!credencialesValidas);
      break;
    }
    case 3:
    {
      string nombre, contrasena;
      pedirDatos(nombre, contrasena);
      agregarUsuario(listaMedicos, "medico", nombre, contrasena);
      cout << "Medico registrado con exito" << endl;
      break;
    }
    case 4:
    {
      string nombre, contrasena;
      pedirDatos(nombre, contrasena);
      agregarUsuario(listaEnfermeras, "enfermero", nombre, contrasena);
      cout << "Enfermera registrada con exito" << endl;
      break;
    }
    case 5:
      cout << "Saliendo..." << endl;
      break;
    default:
      cout << "Opcion no valida" << endl;
      break;
    }
  } while (opcion != 5);
}

// Funcion para anadir un nuevo registro al historial medico
void agregarRegistroHistorial(const string &nombrePaciente, const HistorialMedico &registro)
{
  historialPorNombre[nombrePaciente].push_back(registro);
}

// Funcion para buscar el historial medico por el nombre del paciente
vector<HistorialMedico> buscarHistorialPorNombre(const string &nombrePaciente)
{
  if (historialPorNombre.find(nombrePaciente) != historialPorNombre.end())
  {
    return historialPorNombre[nombrePaciente];
  }
  else
  {
    return {}; // Historial no encontrado
  }
}

// Funcion para mostrar el historial medico de un paciente
void mostrarHistorialMedico(const vector<HistorialMedico> &historial)
{
  cout << "\nHistorial Medico:" << endl;
  if (historial.empty())
  {
    cout << "El historial medico esta vacio." << endl;
  }
  else
  {
    for (size_t i = 0; i < historial.size(); ++i)
    {
      cout << "Consulta " << i + 1 << ":" << endl;
      cout << "Fecha de consulta (formato dd/mm/aaaa): " << historial[i].fechaConsulta << endl;
      cout << "Motivo de consulta: " << historial[i].motivoConsulta << endl;
      cout << "Diagnostico: " << historial[i].diagnostico << endl;
      cout << "Tratamiento: " << historial[i].tratamiento << endl;
      cout << endl;
    }
  }
}

// Funcion para actualizar un registro especifico en el historial medico
void actualizarRegistroHistorial(const string &nombrePaciente, size_t indice, const HistorialMedico &nuevoRegistro)
{
  if (historialPorNombre.find(nombrePaciente) != historialPorNombre.end())
  {
    if (indice < historialPorNombre[nombrePaciente].size())
    {
      historialPorNombre[nombrePaciente][indice] = nuevoRegistro;
      cout << "Registro actualizado con exito." << endl;
    }
    else
    {
      cout << "El indice especificado esta fuera de rango." << endl;
    }
  }
  else
  {
    cout << "No se encontro historial medico para " << nombrePaciente << endl;
  }
}

// Funcion para mostrar el historial medico
void mostrarHistorialMedicoConIndices(const vector<HistorialMedico> &historial)
{
  cout << "\nHistorial Medico:" << endl;
  if (historial.empty())
  {
    cout << "El historial medico esta vacio." << endl;
  }
  else
  {
    for (size_t i = 0; i < historial.size(); ++i)
    {
      size_t baseIndex = i * 4;
      cout << baseIndex + 1 << ". Fecha de consulta (formato dd/mm/aaaa): " << historial[i].fechaConsulta << endl;
      cout << baseIndex + 2 << ". Motivo de consulta: " << historial[i].motivoConsulta << endl;
      cout << baseIndex + 3 << ". Diagnostico: " << historial[i].diagnostico << endl;
      cout << baseIndex + 4 << ". Tratamiento: " << historial[i].tratamiento << endl;
      cout << endl;
    }
  }
}

// Funcion para manejar la actualizacion del historial medico
void manejarActualizacionHistorialMedico()
{
  string nombrePaciente;
  cout << "Ingrese el nombre del paciente: ";
  cin.ignore();
  getline(cin, nombrePaciente);

  while (!esNombreValido(nombrePaciente))
  {
    cout << "Nombre no valido. Ingrese solo caracteres alfabeticos." << endl;
    cout << "Ingrese el nombre del paciente: ";
    getline(cin, nombrePaciente);
  }

  if (historialPorNombre.find(nombrePaciente) != historialPorNombre.end())
  {
    vector<HistorialMedico> &historial = historialPorNombre[nombrePaciente];
    mostrarHistorialMedicoConIndices(historial);
    size_t indice;
    cout << "Ingrese el numero de indice del registro que desea actualizar: ";
    cin >> indice;

    if (indice > 0 && indice <= historial.size() * 4)
    {
      size_t registroIndex = (indice - 1) / 4;              // Calcular el indice del registro
      size_t campo = (indice - 1) % 4;                      // Calcular el campo a actualizar
      HistorialMedico &registro = historial[registroIndex]; // Obtener el registro a actualizar

      switch (campo)
      {
      case 0:
        cout << "Ingrese la nueva fecha de consulta (formato dd/mm/aaaa): ";
        cin >> registro.fechaConsulta;
        break;
      case 1:
        cout << "Ingrese el nuevo motivo de consulta: ";
        cin.ignore();
        getline(cin, registro.motivoConsulta);
        break;
      case 2:
        cout << "Ingrese el nuevo diagnostico: ";
        cin.ignore();
        getline(cin, registro.diagnostico);
        break;
      case 3:
        cout << "Ingrese el nuevo tratamiento: ";
        cin.ignore();
        getline(cin, registro.tratamiento);
        break;
      default:
        cout << "Opcion no valida. Por favor, intente nuevamente." << endl;
        return;
      }

      actualizarRegistroHistorial(nombrePaciente, registroIndex, registro);
    }
    else
    {
      cout << "Indice fuera de rango." << endl;
    }
  }
  else
  {
    cout << "No se encontro historial medico para " << nombrePaciente << endl;
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

  cout << "Lista de hospitales disponibles para traslado:" << endl;
  for (size_t i = 0; i < hospitales.size(); ++i)
  {
    cout << i + 1 << ". Nombre: " << hospitales[i].nombre << ", Contacto: " << hospitales[i].contacto << endl;
  }

  string nombrePaciente;
  bool nombreValido = false;

  while (!nombreValido)
  {
    cout << "Ingrese el nombre del paciente: ";
    cin.ignore();
    getline(cin, nombrePaciente);

    if (!nombrePaciente.empty() && isalpha(nombrePaciente[0]))
    {
      nombreValido = true;
    }
    else
    {
      cout << "Nombre no valido. Por favor, intente nuevamente." << endl;
    }
  }

  int opcion;
  bool opcionValida = false;

  while (!opcionValida)
  {
    cout << "Ingrese el numero del hospital al que desea trasladar al paciente: ";
    cin >> opcion;

    if (cin.fail() || opcion <= 0 || opcion > hospitales.size())
    {
      cin.clear();                                         // Limpiar el estado de error
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar el buffer de entrada
      cout << "Opcion no valida. Por favor, intente nuevamente." << endl;
    }
    else
    {
      opcionValida = true;
    }
  }

  cout << "Paciente " << nombrePaciente << " trasladado a " << hospitales[opcion - 1].nombre << " con contacto " << hospitales[opcion - 1].contacto << endl;
}

// Funcion para mostrar el menu del medico
void manejarMenuMedico(vector<Receta> &recetas)
{
  int opcion;
  vector<HistorialMedico> historial;
  HistorialMedico nuevoRegistro;

  do
  {
    cout << "\nMenu de personal medico" << endl;
    cout << "1. Crear historial medico para un paciente" << endl;
    cout << "2. Buscar historial medico" << endl;
    cout << "3. Actualizar historial medico" << endl;
    cout << "4. Asignar receta a paciente" << endl;
    cout << "5. Traslado de paciente" << endl;
    cout << "6. Salir" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opcion;

    if (cin.fail())
    {
      // Limpiar el buffer de entrada
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Entrada no valida. Por favor, ingrese un numero valido." << endl;
      continue;
    }

    switch (opcion)
    {
    case 1:
    {
      string nombrePaciente;
      bool nombreValido = false;

      cout << "Ingrese el nombre del paciente: ";
      cin.ignore(); // Limpiar el buffer del teclado antes de la entrada del nombre

      while (!nombreValido)
      {
        getline(cin, nombrePaciente);

        if (esNombreValido(nombrePaciente))
        {
          nombreValido = true;
        }
        else
        {
          cout << "Nombre no valido. Solo se permiten letras y espacios." << endl;
          cout << "Ingrese el nombre del paciente: ";
        }
      }
      HistorialMedico nuevoRegistro;
      cout << "Fecha de consulta (formato dd/mm/aaaa): ";
      getline(cin, nuevoRegistro.fechaConsulta);
      cout << "Motivo de consulta: ";
      getline(cin, nuevoRegistro.motivoConsulta);
      cout << "Diagnostico: ";
      getline(cin, nuevoRegistro.diagnostico);
      cout << "Tratamiento: ";
      getline(cin, nuevoRegistro.tratamiento);

      agregarRegistroHistorial(nombrePaciente, nuevoRegistro);
      cout << "Historial medico creado con exito." << endl;
      break;
    }
    case 2:
    {
      string nombrePaciente;
      cout << "Ingrese el nombre del paciente: ";
      cin.ignore();
      getline(cin, nombrePaciente);

      vector<HistorialMedico> historial = buscarHistorialPorNombre(nombrePaciente);
      if (!historial.empty())
      {
        mostrarHistorialMedico(historial);
      }
      else
      {
        cout << "No se encontro historial medico para " << nombrePaciente << endl;
      }
      break;
    }
    case 3:
      manejarActualizacionHistorialMedico();
      break;
    case 4:
      // Declarar vector de recetas para almacenar las recetas asignadas
      static vector<Receta> recetas;
      asignarReceta(recetas);
      break;
    case 5:
      manejarTraslado();
      break;
    case 6:
      cout << "Saliendo... ";
      break;
    }
  } while (opcion != 6);
}

int main()
{

  Usuario *listaMedicos = nullptr;
  Usuario *listaEnfermeras = nullptr;

  std::vector<Usuario> listaMedicos_ = {};
  std::vector<Usuario> *listaEnfermeras_ = {};
  Paciente paciente;

  // Agregar usuarios predeterminados
  agregarUsuario(listaMedicos, "medico", "Ana", "123456");
  agregarUsuario_(listaMedicos_, "medico", "Ana", "123456");

  agregarUsuario(listaEnfermeras, "enfermera", "Fabrizzio", "123456");

  mostrarMenuIngreso(listaMedicos, listaEnfermeras, paciente);

  // Liberar memoria de las listas de usuarios
  liberarMemoria(listaMedicos);
  liberarMemoria(listaEnfermeras);

  listaEnfermeras_->clear();
  listaMedicos_.clear();

  return 0;
}
