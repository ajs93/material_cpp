// Inclusion necesaria para el uso de std::deque
#include <deque>

// Inclusion para std::cin, std::cout, std::cerr
#include <iostream>

// Inclusion para std::find
#include <algorithm>

int main() {
  // Creacion de la cola
  std::deque<int> numeros_ingresados;

  // Solicitamos al usuario que ingrese numeros hasta ingresar el -1
  std::cout << "Ingrese numeros, se finalizara el ingreso al ingresar el numero\n"
               "Los numeros luego se mostraran todos los negativos primero y luego los positivos:" << std::endl;
  // Al igual que con los contenedores de la libreria STL, podemos utiliar el metodo std::find
  while(std::find(numeros_ingresados.begin(),
                  numeros_ingresados.end(),
                  0) == numeros_ingresados.end()) {
    int nuevo_numero;
    std::cin >> nuevo_numero;

    if (nuevo_numero >= 0) {
      numeros_ingresados.push_back(nuevo_numero);
    } else {
      numeros_ingresados.push_front(nuevo_numero);
    }
  }

  // Removemos el ultimo elemento que sabemos que es el cero
  if (numeros_ingresados.back() == 0) {
    // Sabemos que siempre vamos a ingresar a este if!
    numeros_ingresados.pop_back();
  }

  std::cout << "Numeros ingresados:" << std::endl;
  // Como con los demas contenedores, podemos utilizar iteradores
  for (int v : numeros_ingresados) {
    std::cout << v << " ";
  }

  std::cout << std::endl << std::endl;

  std::cout << "Numeros ingresados (orden inverso):" << std::endl;
  // A su vez, podemos utilizar iteradores en el sentido opuesto de manera mas manual:
  auto it = numeros_ingresados.rbegin();
  while (it != numeros_ingresados.rend()) {
    std::cout << *it << " ";
    it++;
  }

  std::cout << std::endl << std::endl;

  return 0;
}