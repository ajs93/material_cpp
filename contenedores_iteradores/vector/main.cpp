// Inclusion para el uso de la clase std::vector
#include <vector>

// Inclusion para std::cin, std::cout, std::cerr
#include <iostream>

// Inclusion para std::find_if
#include <algorithm>

bool es_negativo(int valor) {
  return valor < 0;
}

int main() {
  // Creacion del vector con el tipo de dato que el mismo va a alojar
  std::vector<int> numeros_ingresados;

  // Pedimos al usuario que ingrese numeros hasta que ingrese algun numero negativo
  std::cout << "Ingrese numeros. Se terminara el ingreso al ingresar un numero negativo:" << std::endl;

  // Para "detectar" si se ingreso algun numero negativo, se puede utilizar la
  // funcion std::find_if
  // Documentacion del metodo: https://www.cplusplus.com/reference/algorithm/find_if/
  while (std::find_if(numeros_ingresados.begin(),
                      numeros_ingresados.end(),
                      es_negativo) == numeros_ingresados.end()) {
    // Notese que cuando find_if() no encuentra ningun contenido que cumpla la condicion pasada, se devuelve
    // el iterador correspondiente al metodo end() el cual corresponde a un elemento "luego del final" del vector
    // Si intentaramos desreferenciar dicho valor, generariamos una excepcion de memoria, similar a:
    // int buffer[10];
    // buffer[11] = 0;
    
    int nuevo_valor;
    std::cin >> nuevo_valor;

    // "Empujamos" el nuevo valor en el vector mediante el metodo push_back
    numeros_ingresados.push_back(nuevo_valor);

    // Particularidad de la clase std::vector:
    // Existen dos metodos que a primera vista podrian "dar lo mismo" pero son muy distintos
    // - size() -> Devuelve el tamaño ocupado actualmente por el vector (cantidad de elementos en el mismo)
    // - capacity() -> Devuelve la cantidad de memoria reservada actualmente por el vector
    // La clase std::vector cada vez que tiene que reservar memoria para extenderse, no lo hace de forma
    // lineal. Probar ingresando distintas cantidades de numeros y analizando esta salida
    std::cout << "Size: " << numeros_ingresados.size() << std::endl;
    std::cout << "Capacity: " << numeros_ingresados.capacity() << std::endl << std::endl;
  }

  // Obtenemos el lugar donde se encuentra el valor negativo ingresado y lo eliminamos del vector:
  // Como sabemos que esta en el ultimo lugar, podriamos hacer:
  // numeros_ingresados.erase(numeros_ingresados.end() - 1); // Usando iterador
  // Otra forma de eliminar el ultimo elemento:
  numeros_ingresados.pop_back(); // Usando metodo provisto por la clase std::vector

  std::cout << "Numeros ingresados:" << std::endl;
  // Podemos corroborar si se ingreso algun numero positivo evaluando si el vector
  // se encuentra vacio luego de eliminar el numero negativo ingresado:
  if (!numeros_ingresados.empty()) { // No confundir con el metodo clear() que elimina todo el contenido del vector
    // El vector tiene al menos un elemento
    // Como con todos los contenedores de la libreria STL, podemos iterar a traves del vector
    // de la siguiente forma:
    for (int v : numeros_ingresados) {
      std::cout << v << " ";
    }
  } else {
    // El vector no tiene ningun elemento!
    std::cout << "No se ingreso ningun numero positivo!";
  }

  std::cout << std::endl << std::endl;

  // Asi como con el contenedor array, los metodos at() y operator[] tienen la misma
  // sutil diferencia al indexar elementos que no son validos (indice >= size()):
  // - at() -> Arroja una excepcion de tipo out_of_range
  // - operator[] -> Comportamiento no definido
  try {
    std::cout << numeros_ingresados.at(numeros_ingresados.size() + 1) << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Se atrapo exepcion con contenido: " << e.what() << std::endl;
  }

  return 0;
}