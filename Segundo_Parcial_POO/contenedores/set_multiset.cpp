#include <iostream>
#include <set>       // Para std::set y std::multiset
using namespace std;

// Función auxiliar para mostrar contenido genérico
template <typename T>
void mostrarConjunto(const T& c, const string& nombre) {
    cout << nombre << ": ";
    for (auto it = c.begin(); it != c.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

int main() {
    // ============================================================
    // 🔹 1. SET<T> (conjunto de elementos ÚNICOS y ORDENADOS)
    // ============================================================
    set<int> s;

    // Agregar elementos (duplicados se ignoran)
    s.insert(5);
    s.insert(2);
    s.insert(8);
    s.insert(1);
    s.insert(5); // ignorado (ya existe)

    mostrarConjunto(s, "Set inicial");

    // Acceder y recorrer
    cout << "Tamano del set: " << s.size() << endl;
    cout << "¿Contiene el 8? " << (s.count(8) ? "Si" : "No") << endl;

    // Buscar un elemento
    auto it = s.find(2);
    if (it != s.end())
        cout << "Encontrado: " << *it << endl;

    // Eliminar elementos
    s.erase(5); // elimina el valor 5
    mostrarConjunto(s, "Despues de erase(5)");

    // Insertar más y mostrar ordenado
    s.insert(10);
    s.insert(0);
    mostrarConjunto(s, "Set final (ordenado automaticamente)");

    // Limpiar
    s.clear();
    cout << "Despues de clear(), tamano: " << s.size() << "\n\n";



    // ============================================================
    // 🔹 2. MULTISET<T> (permite elementos DUPLICADOS)
    // ============================================================
    multiset<int> ms;

    // Insertar elementos (duplicados aceptados)
    ms.insert(5);
    ms.insert(2);
    ms.insert(5);
    ms.insert(8);
    ms.insert(2);
    ms.insert(1);

    mostrarConjunto(ms, "Multiset inicial");

    // Contar cuántas veces aparece un valor
    cout << "El numero 5 aparece " << ms.count(5) << " veces.\n";
    cout << "El numero 2 aparece " << ms.count(2) << " veces.\n";

    // Buscar rango de elementos repetidos
    auto rango = ms.equal_range(2);
    cout << "Elementos iguales a 2: ";
    for (auto it = rango.first; it != rango.second; ++it)
        cout << *it << " ";
    cout << endl;

    // Eliminar un solo elemento (por iterador)
    auto it2 = ms.find(5);
    if (it2 != ms.end())
        ms.erase(it2); // elimina solo una de las apariciones de 5
    mostrarConjunto(ms, "Despues de eliminar una ocurrencia de 5");

    // Eliminar todas las apariciones de un valor
    ms.erase(2);
    mostrarConjunto(ms, "Despues de eliminar todas las ocurrencias de 2");

    // Limpiar
    ms.clear();
    cout << "Despues de clear(), tamano: " << ms.size() << endl;

    return 0;
}

/*
| Método              | Descripción                                          |
| ------------------- | ---------------------------------------------------- |
| `insert(x)`         | Inserta el valor (único o duplicado según tipo)      |
| `find(x)`           | Devuelve iterador al elemento o `end()` si no existe |
| `count(x)`          | Devuelve cuántas veces aparece `x`                   |
| `erase(x)`          | Elimina todas las ocurrencias de `x`                 |
| `erase(it)`         | Elimina una sola ocurrencia (por iterador)           |
| `equal_range(x)`    | Devuelve rango con todos los elementos iguales a `x` |
| `clear()`           | Elimina todo el contenido                            |
| `size()`            | Devuelve cantidad de elementos                       |
| `begin()` / `end()` | Iteradores para recorrer ordenadamente               |

*/
