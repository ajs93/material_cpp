// Inclusion para el uso de la clase std::array
#include <array>

// Inclusion para el uso de std::cin, std::cout, std::cerr
#include <iostream>

// Cantidad de numeros a ingresar por el usuario
#define   NUMEROS_A_INGRESAR    (5)

int main() {
  // Notese que esta clase necesita dos variables de template:
  // - Tipo de datos que se van a alojar en el array
  // - Cantidad de datos maximos que se van a alojar en el array
  std::array<int, NUMEROS_A_INGRESAR> numeros_ingresados;

  // Una vez creado el array, no se puede cambiar ni su tamaño ni el tipo
  // de dato que el mismo aloja

  // Ingreso de numeros en el array
  std::cout << "Ingrese " << NUMEROS_A_INGRESAR << " numeros" << std::endl;
  for (int i = 0; i < NUMEROS_A_INGRESAR; i++) {
    std::cin >> numeros_ingresados[i];
  }

  // Mostramos los numeros ingresados uno por uno
  std::cout << "Numeros ingresados:" << std::endl;
  // Notese que podemos utilizar el metodo size() de std::array para obtener su tamaño
  // si es que usaramos el viejo metodo para iterar como lo solemos hacer en C
  // for (int i = 0; i < numeros_ingresados.size(); i++) {
  //   std::cout << numeros_ingresados.at(i) << std::endl;
  // }

  // Usando una nueva posibilidad (mas comoda) con los iteradores de C++
  for (int v : numeros_ingresados) {
    std::cout << v << std::endl;
  }

  // Diferencia entre at() y operator[].
  // En caso de que el indice accedido sea invalido:
  // - at() -> arroja una excepcion de tipo std::out_of_range
  // - operator[] -> Causa comportamiento indefinido
  try {
    std::cout << numeros_ingresados.at(numeros_ingresados.size() + 1) << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Se atrapo exepcion con contenido: " << e.what() << std::endl;
  }

  return 0;
}