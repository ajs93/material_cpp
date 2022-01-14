// Inclusion para el uso de std::list
#include <list>

// Inclusion para el uso de std::cin, std::cout, std::cerr
#include <iostream>

// Inclusion para generacion de numeros aleatorios
#include <random>

// Inclusion para funciones temporales
#include <chrono>

void imprimir_lista(const std::list<int> lista) {
  for (int n : lista) {
    std::cout << n << " ";
  }

  std::cout << std::endl;
}

bool impar(int v) {
  return v % 2 == 1;
}

int main() {
  // Semilla para el generador de numeros aleatorios
  unsigned int semilla = std::chrono::system_clock::now().time_since_epoch().count();

  // Generador de numeros aleatorios
  std::minstd_rand0 generador(semilla);

  // Lista de numeros
  std::list<int> lista_numeros;

  // Insertamos 10 numeros aleatorios entre 0 y 9:
  for (int i = 0; i < 10; i++) {
    lista_numeros.push_back(generador() % 10);
  }

  std::cout << "Lista original:" << std::endl;
  imprimir_lista(lista_numeros);

  std::cout << "Lista invertida:" << std::endl;
  lista_numeros.reverse();
  imprimir_lista(lista_numeros);

  std::cout << "Lista ordenada:" << std::endl;
  lista_numeros.sort();
  imprimir_lista(lista_numeros);

  // Eliminamos valores impares
  std::cout << "Lista ordenada sin numeros impares:" << std::endl;
  lista_numeros.remove_if(impar);
  imprimir_lista(lista_numeros);
}