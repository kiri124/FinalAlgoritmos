#pragma once

#include <iostream>
#include <string>
#include "data.h"
#include "structures.h"

// Funcion para crear un nuevo usuario
Usuario *crearUsuario(std::string tipo, std::string nombre, std::string contrasena);
// Funcion para añadir un usuario a la lista
void agregarUsuario(data::Trie<Usuario> userTrie, std::string tipo, std::string nombre, std::string contrasena);
// Funcion para mostrar el menu y gestionar el ingreso de usuarios
void mostrarMenuIngreso(data::Trie<Usuario> &listaMedicos, data::Trie<Usuario> &listaEnfermeras);
// Funcion para pedir los datos del usuario
void pedirDatos(string &nombre, string &contrasena);
// Funcion para validar las credenciales
bool validarCredenciales(data::Trie<Usuario> userTrie, string nombre, string contrasena);