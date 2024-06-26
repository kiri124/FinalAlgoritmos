#include <iostream>
#include <string>
#include "data.h"
#include "structures.h"
#include "doctor.menu.h"
#include "nuerse.menu.h"

// Funcion para crear un nuevo usuario
Usuario *crearUsuario(std::string tipo, std::string nombre, std::string contrasena)
{
  Usuario *nuevo = new Usuario;
  nuevo->tipo = tipo;
  nuevo->nombre = nombre;
  nuevo->contrasena = contrasena;
  nuevo->siguiente = nullptr;
  return nuevo;
}

// Funcion para añadir un usuario a la lista
void agregarUsuario(data::Trie<Usuario> userTrie, std::string tipo, std::string nombre, std::string contrasena)
{
  Usuario *nuevo = crearUsuario(tipo, nombre, contrasena);
  std::cout << "Usuario creado con exito." << endl;
  userTrie.insert(nuevo, nuevo->nombre);
  userTrie.saveToCsv();
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
bool validarCredenciales(data::Trie<Usuario> userTrie, string nombre, string contrasena)
{
  if (userTrie.search(nombre) != nullptr && userTrie.search(nombre)->contrasena == contrasena)
  {
    return true;
  }
  return false;
}

// Funcion para mostrar el menu y gestionar el ingreso de usuarios
void mostrarMenuIngreso(data::Trie<Usuario> &listaMedicos, data::Trie<Usuario> &listaEnfermeras)
{
  int opcion;

  vector<Receta> recetas;
  // Vector para la lista de espera
  vector<Paciente> listaEspera;
  do
  {
    std::cout << "***********" << endl;
    std::cout << "Policlinico San Vicente de Paul" << endl;
    std::cout << "***********" << endl;
    std::cout << "1. Ingresar como personal medico" << endl;
    std::cout << "2. Ingresar como personal de enfermeria" << endl;
    std::cout << "3. Registrarse como personal medico" << endl;
    std::cout << "4. Registrarse como personal de enfermeria" << endl;
    std::cout << "5. Salir" << endl;
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
      std::string nombre, contrasena;
      bool credencialesValidas = false;
      do
      {
        pedirDatos(nombre, contrasena);
        if (validarCredenciales(listaMedicos, nombre, contrasena))
        {
          std::cout << "Acceso concedido al medico" << endl;
          manejarMenuMedico(recetas);
          credencialesValidas = true;
        }
        else
        {
          std::cout << "Credenciales de medico incorrectas. Intente nuevamente." << endl;
        }
      } while (!credencialesValidas);
      break;
    }
    case 2:
    {
      std::string nombre, contrasena;
      bool credencialesValidas = false;
      do
      {
        pedirDatos(nombre, contrasena);
        if (validarCredenciales(listaEnfermeras, nombre, contrasena))
        {
          std::cout << "Acceso concedido al enfermero" << endl;
          manejarMenuEnfermera(listaEspera);
          credencialesValidas = true;
        }
        else
        {
          std::cout << "Credenciales de enfermero incorrectas. Intente nuevamente." << endl;
        }
      } while (!credencialesValidas);
      break;
    }
    case 3:
    {
      std::string nombre, contrasena;
      pedirDatos(nombre, contrasena);
      agregarUsuario(listaMedicos, "medico", nombre, contrasena);
      std::cout << "Medico registrado con exito" << endl;
      break;
    }
    case 4:
    {
      std::string nombre, contrasena;
      pedirDatos(nombre, contrasena);
      agregarUsuario(listaEnfermeras, "enfermero", nombre, contrasena);
      std::cout << "Enfermera registrada con exito" << endl;
      break;
    }
    case 5:
      std::cout << "Saliendo..." << endl;
      break;
    default:
      std::cout << "Opcion no valida" << endl;
      break;
    }
  } while (opcion != 5);
}
