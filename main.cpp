#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>
#include <map>
#include <vector>
#include <thread>
#include <algorithm>
#include "structures.h"
#include "login.menu.h"
#include "data.h"
#include "database.h"
#include "utils.h"

using namespace std;
using namespace data;
using namespace utils;

void loadFromCsv(Trie<Usuario> &trie, const std::string &filename)
{
  trie.dbPath = filename;
  trie.loadFromCsv();
}

int main()
{
  Trie<Usuario> medicosTrie;
  Trie<Usuario> enfermerasTrie;

  std::string archivoMedicos = "./db/medicos.txt";
  std::string archivoEnfermeras = "./db/enfermeras.txt";
  std::thread threadMedicos(loadFromCsv, std::ref(medicosTrie), archivoMedicos);
  std::thread threadEnfermeras(loadFromCsv, std::ref(enfermerasTrie), archivoEnfermeras);

  threadMedicos.join();
  threadEnfermeras.join();

  mostrarMenuIngreso(medicosTrie, enfermerasTrie);
  return 0;
}
