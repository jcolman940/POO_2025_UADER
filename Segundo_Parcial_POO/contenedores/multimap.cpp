#include <iostream>
#include <map>        // std::multimap está en el mismo header, en multimap se permiten claves duplicadas
#include <string>
using namespace std;

// Función auxiliar para mostrar el contenido del multimap
void mostrarMultimap(const multimap<string, int>& mm) {
    cout << "Contenido del multimap:\n";
    for (auto it = mm.begin(); it != mm.end(); ++it)
        cout << "Clave: " << it->first << "  Valor: " << it->second << endl;
    cout << endl;
}

int main() {
    // 🔹 1. DECLARACIÓN
    multimap<string, int> notas; // Clave = nombre, Valor = nota

    // 🔹 2. INSERCIÓN DE ELEMENTOS (permite claves repetidas)
    notas.insert(make_pair("Ana", 8));
    notas.insert(make_pair("Juan", 6));
    notas.insert(make_pair("Ana", 10));  // misma clave
    notas.insert(make_pair("Lucia", 7));
    notas.insert(make_pair("Juan", 9));
    notas.insert(make_pair("Pedro", 5));

    mostrarMultimap(notas);

    // 🔹 3. CANTIDAD DE ELEMENTOS CON UNA CLAVE
    cout << "Juan aparece " << notas.count("Juan") << " veces.\n";
    cout << "Ana aparece " << notas.count("Ana") << " veces.\n\n";

    // 🔹 4. BUSCAR TODOS LOS ELEMENTOS DE UNA CLAVE
    string nombre = "Juan";
    auto rango = notas.equal_range(nombre); // devuelve par de iteradores [inicio, fin)
    cout << "Notas de " << nombre << ": ";
    for (auto it = rango.first; it != rango.second; ++it)
        cout << it->second << " ";
    cout << endl << endl;

    // 🔹 5. ELIMINAR ELEMENTOS
    // Eliminar por clave (elimina TODOS los elementos con esa clave)
    notas.erase("Pedro");
    cout << "Despues de eliminar a Pedro:\n";
    mostrarMultimap(notas);

    // Eliminar un solo elemento (por iterador)
    auto it = notas.find("Ana"); // elimina solo la primera aparición
    if (it != notas.end())
        notas.erase(it);
    cout << "Despues de eliminar una sola entrada de Ana:\n";
    mostrarMultimap(notas);

    // 🔹 6. RECORRER TODO ORDENADO POR CLAVE
    cout << "Recorriendo multimap ordenado:\n";
    for (const auto& [nombre, nota] : notas)
        cout << nombre << " -> " << nota << endl;
    cout << endl;

    // 🔹 7. INSERTAR NUEVOS ELEMENTOS Y USAR upper_bound()
    notas.insert({"Juan", 4});
    notas.insert({"Juan", 7});

    cout << "Notas actualizadas de Juan: ";
    auto inicio = notas.find("Juan");
    auto fin = notas.upper_bound("Juan");
    for (auto it = inicio; it != fin; ++it)
        cout << it->second << " ";
    cout << endl;

    // 🔹 8. LIMPIAR TODO
    notas.clear();
    cout << "\nDespues de clear(), tamano: " << notas.size() << endl;

    return 0;
}

/*
| Método           | Función                                                                            | Complejidad  | Notas                          |
| ---------------- | ---------------------------------------------------------------------------------- | ------------ | ------------------------------ |
| `insert({k, v})` | Inserta un par clave–valor                                                         | O(log n)     | Permite duplicados             |
| `count(k)`       | Devuelve cuántos elementos tienen esa clave                                        | O(log n + m) | m = repeticiones               |
| `find(k)`        | Devuelve el **primer** elemento con esa clave                                      | O(log n)     | No recorre todos               |
| `equal_range(k)` | Devuelve un rango `[first, second)` con todos los elementos que comparten la clave | O(log n + m) | Ideal para recorrer duplicados |
| `erase(k)`       | Elimina todos los elementos con la clave `k`                                       | O(log n + m) | —                              |
| `erase(it)`      | Elimina un solo elemento (iterador)                                                | O(1)         | —                              |
| `upper_bound(k)` | Iterador al **primer elemento después** de los que tienen la clave                 | O(log n)     | Muy útil junto a `find()`      |
| `clear()`        | Elimina todos los elementos                                                        | O(n)         | —                              |

*/