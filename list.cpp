#include <iostream>
#include <list>        // Librería para std::list
#include <algorithm>   // Para sort(), find(), reverse(), etc.
using namespace std;

// Función auxiliar para mostrar el contenido de la lista
void mostrarLista(const list<int>& l) {
    cout << "Contenido de la lista: ";
    for (auto it = l.begin(); it != l.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

int main() {
    // 🔹 1. CONSTRUCTORES
    list<int> l1;                     // Lista vacía
    list<int> l2(5);                  // Lista con 5 elementos = 0
    list<int> l3(4, 10);              // Lista con 4 elementos = 10
    list<int> l4 = {1, 2, 3, 4, 5};   // Lista inicializada con valores

    cout << "Lista l3 (4 elementos = 10): ";
    mostrarLista(l3);

    // 🔹 2. ATRIBUTOS BÁSICOS
    cout << "Tamano de l4: " << l4.size() << endl;
    cout << "Esta vacia?: " << (l4.empty() ? "Si" : "No") << endl;

    // 🔹 3. AGREGAR ELEMENTOS
    l4.push_back(6);   // Agrega al final
    l4.push_front(0);  // Agrega al principio
    mostrarLista(l4);

    // Insertar en posición específica (antes del tercer elemento)
    auto it = l4.begin();
    advance(it, 3);  // mueve el iterador 3 posiciones desde el inicio
    l4.insert(it, 99);
    cout << "Despues de insertar 99 en la posicion 3: ";
    mostrarLista(l4);

    // 🔹 4. ACCEDER A ELEMENTOS (solo frente y final)
    cout << "Primer elemento (front): " << l4.front() << endl;
    cout << "Ultimo elemento (back): " << l4.back() << endl;

    // 🔹 5. MODIFICAR ELEMENTOS (usando iteradores)
    cout << "Sumando 10 a cada elemento..." << endl;
    for (auto it = l4.begin(); it != l4.end(); ++it)
        *it += 10;
    mostrarLista(l4);

    // 🔹 6. ELIMINAR ELEMENTOS
    l4.pop_front(); // elimina el primero
    l4.pop_back();  // elimina el último
    cout << "Despues de pop_front y pop_back: ";
    mostrarLista(l4);

    // Eliminar un elemento específico (el valor 99+10=109)
    l4.remove(109); // elimina TODAS las ocurrencias del valor
    cout << "Despues de remove(109): ";
    mostrarLista(l4);

    // Eliminar por posición con iterador
    it = l4.begin();
    advance(it, 2);
    l4.erase(it);
    cout << "Despues de erase en posicion 2: ";
    mostrarLista(l4);

    // 🔹 7. ORDENAR Y REVERSAR
    l4.push_back(15);
    l4.push_back(3);
    cout << "Lista desordenada: ";
    mostrarLista(l4);

    l4.sort(); // ordena en orden ascendente
    cout << "Lista ordenada: ";
    mostrarLista(l4);

    l4.reverse(); // invierte el orden
    cout << "Lista invertida: ";
    mostrarLista(l4);

    // 🔹 8. COMBINAR Y ELIMINAR DUPLICADOS
    list<int> l5 = {5, 6, 7, 8};
    l4.merge(l5); // combina y ordena (requiere listas ordenadas)
    cout << "Después de merge(l5): ";
    mostrarLista(l4);

    l4.unique(); // elimina duplicados consecutivos
    cout << "Despues de unique(): ";
    mostrarLista(l4);

    // 🔹 9. LIMPIAR
    l4.clear();
    cout << "Despues de clear(), tamano: " << l4.size() << endl;

    return 0;
}

/*
| Método              | Función                               | Complejidad |
| ------------------- | ------------------------------------- | ----------- |
| `push_back(x)`      | Agrega `x` al final                   | Constante   |
| `push_front(x)`     | Agrega `x` al principio               | Constante   |
| `insert(it, x)`     | Inserta `x` antes de la posición `it` | Constante   |
| `pop_back()`        | Elimina el último elemento            | Constante   |
| `pop_front()`       | Elimina el primer elemento            | Constante   |
| `erase(it)`         | Elimina el elemento apuntado por `it` | Constante   |
| `remove(x)`         | Elimina todas las apariciones de `x`  | Lineal      |
| `sort()`            | Ordena la lista                       | O(n log n)  |
| `reverse()`         | Invierte el orden de los elementos    | Lineal      |
| `merge(l2)`         | Combina dos listas ordenadas          | Lineal      |
| `unique()`          | Elimina duplicados consecutivos       | Lineal      |
| `clear()`           | Elimina todos los elementos           | Constante   |
| `front()`, `back()` | Accede al primer/último elemento      | Constante   |

"list" es ideal cuando necesitás insertar o eliminar frecuentemente elementos en cualquier posición, pero no si necesitás acceder por índice.
En cambio, "vector" es más rápido para recorrer y acceder por posición, pero más costoso para insertar o borrar del medio.
*/