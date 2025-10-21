#include <iostream>
#include <vector>   // Librería necesaria para usar std::vector
#include <algorithm> // Para funciones como sort(), find(), etc.
using namespace std;

// Función auxiliar para mostrar el contenido del vector
void mostrarVector(const vector<int>& v) {
    cout << "Contenido del vector: ";
    for (auto it = v.begin(); it != v.end(); ++it)
        cout << *it << " "; // *it desreferencia el iterador (como un puntero)
    cout << endl;
}

int main() {
    // 🔹 1. CONSTRUCTORES
    vector<int> v1;                      // Vector vacío
    vector<int> v2(5);                   // Vector con 5 elementos inicializados en 0
    vector<int> v3(5, 10);               // Vector con 5 elementos inicializados en 10
    vector<int> v4 = {1, 2, 3, 4, 5};    // Inicialización con lista

    cout << "Vector v3 (5 elementos = 10): ";
    mostrarVector(v3);
    
    // 🔹 2. ATRIBUTOS BÁSICOS
    cout << "Tamano de v4: " << v4.size() << endl;
    cout << "Capacidad de v4: " << v4.capacity() << endl;
    cout << "Esta vacio?: " << (v4.empty() ? "Sí" : "No") << endl;

    // 🔹 3. AGREGAR ELEMENTOS
    v4.push_back(6); // Agrega al final
    v4.push_back(7);
    mostrarVector(v4);

    // Insertar en posición específica (antes del elemento con índice 2)
    v4.insert(v4.begin() + 2, 99);
    cout << "Despues de insertar 99 en la posicion 2: ";
    mostrarVector(v4);

    // 🔹 4. ACCEDER A ELEMENTOS
    cout << "Elemento en posicion 0 (v4[0]): " << v4[0] << endl;
    cout << "Elemento en posicion 3 (v4.at(2)): " << v4.at(2) << endl;
    cout << "Primer elemento (front): " << v4.front() << endl;
    cout << "Ultimo elemento (back): " << v4.back() << endl;

    // 🔹 5. MODIFICAR ELEMENTOS
    v4[1] = 111; // Asignación directa
    v4.at(3) = 222; // Usando método at()
    cout << "Despues de modificar elementos: ";
    mostrarVector(v4);

    // 🔹 6. ELIMINAR ELEMENTOS
    v4.pop_back(); // Elimina el último elemento
    cout << "Despues de pop_back(): ";
    mostrarVector(v4);

    // Eliminar elemento en posición 2
    v4.erase(v4.begin() + 2);
    cout << "Despues de erase(pos 2): ";
    mostrarVector(v4);

    // Eliminar todos los elementos
    vector<int> copia = v4; // guardamos copia
    v4.clear();
    cout << "Despues de clear(), tamano: " << v4.size() << endl;

    // 🔹 7. ITERADORES (recorrer y modificar)
    cout << "Usando iteradores para modificar (copia): ";
    for (auto it = copia.begin(); it != copia.end(); ++it)
        *it += 10; // suma 10 a cada elemento
    mostrarVector(copia);

    // 🔹 8. ORDENAR ELEMENTOS
    sort(copia.begin(), copia.end());
    cout << "Vector ordenado: ";
    mostrarVector(copia);

    // 🔹 9. BUSCAR ELEMENTOS
    auto it = find(copia.begin(), copia.end(), 121);
    if (it != copia.end())
        cout << "Elemento 121 encontrado en posicion " << (it - copia.begin()) << endl;
    else
        cout << "Elemento 121 no encontrado." << endl;

    return 0;
}

/*
| Método           | Función                                      | Tipo de acceso      |
| ---------------- | -------------------------------------------- | ------------------- |
| `push_back(x)`   | Agrega `x` al final                          | Inserción constante |
| `insert(pos, x)` | Inserta antes de `pos`                       | Inserción lineal    |
| `pop_back()`     | Elimina el último elemento                   | Constante           |
| `erase(pos)`     | Elimina el elemento en `pos`                 | Lineal              |
| `clear()`        | Vacía el vector                              | Constante           |
| `size()`         | Devuelve cantidad de elementos               | Constante           |
| `capacity()`     | Espacio reservado antes de reasignar memoria | Constante           |
| `empty()`        | Devuelve `true` si está vacío                | Constante           |
| `at(i)`          | Accede al elemento i (controla límites)      | Constante           |
| `front()`        | Devuelve referencia al primer elemento       | Constante           |
| `back()`         | Devuelve referencia al último elemento       | Constante           |
*/