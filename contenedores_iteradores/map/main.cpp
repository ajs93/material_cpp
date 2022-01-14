// Inclusion para el uso de std::map
#include <map>

// Inclusion para std::cout
#include <iostream>

// Inclusino para std::string
#include <string>

enum ClaseDeAnimal {
  Mamifero,
  Ave,
  Pez,
};

void imprimir_animales(const std::map<std::string, ClaseDeAnimal> &mapa) {
  // Instanciacion de traduccion de enumeraciones a std::string
  const std::map<ClaseDeAnimal, std::string> mapa_clase_a_str = {
    { ClaseDeAnimal::Mamifero, "mamifero" },
    { ClaseDeAnimal::Ave, "ave" },
    { ClaseDeAnimal::Pez, "pez" },
  };
  
  std::cout << "Mapa de animales:" << std::endl;
  // Cabe destacar que para este tipo de contenedores, cada item se representa con otro tipo
  // de contenedor de la libreria STL, std::pair<a, b>
  // ATENCION: Como el mapa es pasado como una referencia constante, cada elemento en la pasada
  // de iteracion tambien debe serlo
  for (const std::pair<std::string, ClaseDeAnimal> &item : mapa) {
    std::cout << "Un/a " << item.first << " es un " << mapa_clase_a_str.at(item.second) << std::endl;
  }

  std::cout << std::endl;
}

int main() {
  // Instanciacion e inicializacion del mapa de animales
  std::map<std::string, ClaseDeAnimal> mapa_animales = {
    { "leon", ClaseDeAnimal::Mamifero },
    { "paloma", ClaseDeAnimal::Ave },
    { "trucha", ClaseDeAnimal::Pez },
  };

  imprimir_animales(mapa_animales);

  // Agregado con una sintaxis "intuitiva":
  mapa_animales["bagre"] = ClaseDeAnimal::Pez;
  mapa_animales["bandurria"] = ClaseDeAnimal::Ave;
  // Notese que en este caso, el operator[] no arroja una excepcino en caso de que no
  // exista el elemento buscado, en cambio, crea la entrada y le podemos asignar un valor

  imprimir_animales(mapa_animales);

  // Otras formas de agregar valores al mapa:
  mapa_animales.emplace("lobo", ClaseDeAnimal::Mamifero);
  mapa_animales.insert(std::pair<std::string, ClaseDeAnimal>("mono", ClaseDeAnimal::Mamifero));

  imprimir_animales(mapa_animales);

  // Que pasa si intentamos agregar un valor que ya existia?
  mapa_animales.emplace("lobo", ClaseDeAnimal::Ave);
  mapa_animales.insert(std::pair<std::string, ClaseDeAnimal>("mono", ClaseDeAnimal::Ave));
  // Como se puede observar en la salida del programa, simplemente no se modifica el contenido
  // de dicha entrada, pero la funcion devuelve un iterador a donde se encuentra el elemento existente

  // Como con los demas contenedores, at() arroja una excepcion
  try {
    mapa_animales.at("animal imaginario");
  } catch (const std::exception &e) {
    std::cerr << "Se atrapo excepcion: " << e.what() << std::endl;
  }

  std::cout << "\nNotese que siempre los elementos fueron impresos de forma ordenada en base a su identificador, "
               "para una version de mapa no ordenado, ver -> std::unordered_map" << std::endl;

  std::cout << "\nAsimismo, para una version de mapas que soporten multiples entradas con la misma llave o identificador, " 
               "ver -> std::multimap y std::unordered_multimap" << std::endl;

  return 0;
}