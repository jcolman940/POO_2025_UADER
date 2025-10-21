#include <iostream>
#include <map>        // Para std::map
#include <string>     // Para std::string
using namespace std;

// Función auxiliar para mostrar el contenido del map
void mostrarMapa(const map<string, int>& m) {
    cout << "Contenido del map:\n";
    for (auto it = m.begin(); it != m.end(); ++it)
        cout << "Clave: " << it->first << "  Valor: " << it->second << endl;
    cout << endl;
}

int main() {
    // 🔹 1. DECLARACIÓN
    map<string, int> edades; // clave: string, valor: int

    // 🔹 2. AGREGAR ELEMENTOS
    edades["Juan"] = 25;           // Inserta o actualiza (usa operador [])
    edades["Ana"] = 19;
    edades["Pedro"] = 30;

    // Usando insert() con pair
    edades.insert(make_pair("Lucia", 22));

    // Usando insert() con initializer list (C++11+)
    edades.insert({ "Carlos", 27 });

    mostrarMapa(edades);

    // 🔹 3. ACCEDER A ELEMENTOS
    cout << "Edad de Ana: " << edades["Ana"] << endl;
    cout << "Edad de Pedro: " << edades.at("Pedro") << endl; // 'at()' lanza excepción si no existe la clave

    // 🔹 4. VERIFICAR SI EXISTE UNA CLAVE
    if (edades.count("Lucia") > 0)
        cout << "Lucia esta en el mapa.\n";
    else
        cout << "Lucia no está en el mapa.\n";

    // 🔹 5. MODIFICAR UN VALOR
    edades["Ana"] = 20; // sobreescribe el valor anterior
    cout << "Ana ahora tiene " << edades["Ana"] << " anos.\n\n";

    // 🔹 6. ELIMINAR ELEMENTOS
    edades.erase("Pedro"); // elimina por clave
    mostrarMapa(edades);

    // Eliminar usando un iterador
    auto it = edades.find("Carlos");
    if (it != edades.end()) {
        edades.erase(it);
        cout << "Carlos eliminado del mapa.\n";
    }

    mostrarMapa(edades);

    // 🔹 7. RECORRER ORDENADO POR CLAVE
    cout << "Recorriendo claves ordenadas:\n";
    for (const auto& [nombre, edad] : edades)
        cout << nombre << " -> " << edad << endl;
    cout << endl;

    // 🔹 8. BUSCAR UN ELEMENTO
    string buscado = "Juan";
    auto encontrado = edades.find(buscado);
    if (encontrado != edades.end())
        cout << "Encontrado: " << encontrado->first << " tiene " << encontrado->second << " anos.\n";
    else
        cout << buscado << " no se encuentra en el mapa.\n";

    // 🔹 9. LIMPIAR TODO
    edades.clear();
    cout << "\nDespues de clear(), tamano: " << edades.size() << endl;

    return 0;
}

/*
| Método          | Función                                | Complejidad | Nota                                                 |
| --------------- | -------------------------------------- | ----------- | ---------------------------------------------------- |
| `m[key]`        | Inserta o actualiza un valor por clave | O(log n)    | Si la clave no existe, la crea con valor por defecto |
| `m.at(key)`     | Accede al valor sin crear clave nueva  | O(log n)    | Lanza `out_of_range` si no existe                    |
| `insert({k,v})` | Inserta un par clave–valor             | O(log n)    | No reemplaza si ya existe                            |
| `erase(key)`    | Elimina por clave                      | O(log n)    | Devuelve 1 si se eliminó algo                        |
| `erase(it)`     | Elimina usando un iterador             | O(1)        | Útil tras un `find()`                                |
| `count(key)`    | Devuelve 1 si existe, 0 si no          | O(log n)    | Ideal para verificar existencia                      |
| `find(key)`     | Devuelve iterador a la clave o `end()` | O(log n)    | Rápido y seguro                                      |
| `clear()`       | Borra todos los elementos              | O(n)        | —                                                    |
| `size()`        | Devuelve cantidad de elementos         | Constante   | —                                                    |

*/