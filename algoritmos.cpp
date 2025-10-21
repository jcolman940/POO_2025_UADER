#include <iostream>
#include <vector>
#include <list>
#include <algorithm>  // Algoritmos generales
#include <numeric>    // accumulate()
#include <iterator>   // ostream_iterator
#include <cmath>      // pow()
using namespace std;

// Función auxiliar para imprimir un contenedor
template <typename T>
void mostrar(const T& c, const string& nombre = "Contenedor") {
    cout << nombre << ": ";
    copy(c.begin(), c.end(), ostream_iterator<typename T::value_type>(cout, " "));
    cout << endl;
}

// Función usada con for_each
void mostrarCuadrado(int x) {
    cout << x * x << " ";
}

// Función usada con transform
int triple(int x) {
    return x * 3;
}

int main() {
    // ============================================================
    // 🔹 1. SORT, REVERSE, MIN/MAX
    // ============================================================
    vector<int> v = {5, 2, 9, 1, 7};
    cout << "=== Ordenamiento y reversa ===" << endl;
    mostrar(v, "Vector original");

    sort(v.begin(), v.end()); // orden ascendente
    mostrar(v, "Ordenado ascendente");

    reverse(v.begin(), v.end()); // invierte el orden
    mostrar(v, "Reverso");

    cout << "Minimo: " << *min_element(v.begin(), v.end()) << endl;
    cout << "Maximo: " << *max_element(v.begin(), v.end()) << "\n\n";


    // ============================================================
    // 🔹 2. FIND, COUNT, REMOVE
    // ============================================================
    cout << "=== Busqueda y eliminacion ===" << endl;
    vector<int> w = {1, 2, 3, 2, 4, 2, 5};
    mostrar(w, "Vector original");

    // Buscar elemento
    auto it = find(w.begin(), w.end(), 3);
    if (it != w.end())
        cout << "Encontrado el valor 3 en posicion " << (it - w.begin()) << endl;

    // Contar ocurrencias
    cout << "El valor 2 aparece " << count(w.begin(), w.end(), 2) << " veces." << endl;

    // Eliminar todas las ocurrencias de un valor (remove + erase idiom)
    w.erase(remove(w.begin(), w.end(), 2), w.end());
    mostrar(w, "Despues de eliminar los 2");

    cout << endl;


    // ============================================================
    // 🔹 3. ACCUMULATE y TRANSFORM
    // ============================================================
    cout << "=== Operaciones numericas ===" << endl;
    vector<int> nums = {1, 2, 3, 4, 5};
    mostrar(nums, "nums");

    int suma = accumulate(nums.begin(), nums.end(), 0);
    cout << "Suma total: " << suma << endl;

    // Media aritmética
    double promedio = static_cast<double>(suma) / nums.size();
    cout << "Promedio: " << promedio << endl;

    // Transform: aplicar función a cada elemento
    vector<int> triplicados;
    transform(nums.begin(), nums.end(), back_inserter(triplicados), triple);
    mostrar(triplicados, "Triplicados");

    cout << endl;


    // ============================================================
    // 🔹 4. for_each y lambdas
    // ============================================================
    cout << "=== for_each y lambdas ===" << endl;
    vector<int> valores = {1, 2, 3, 4, 5};

    cout << "Cuadrados con función externa: ";
    for_each(valores.begin(), valores.end(), mostrarCuadrado);
    cout << endl;

    cout << "Cubos con lambda: ";
    for_each(valores.begin(), valores.end(), [](int x) {
        cout << pow(x, 3) << " ";
    });
    cout << "\n\n";


    // ============================================================
    // 🔹 5. COPY, MERGE, UNIQUE
    // ============================================================
    cout << "=== Copia, combinacion y eliminacion de duplicados ===" << endl;
    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b = {3, 4, 5, 6, 7};
    vector<int> combinados;

    // Combinar (ambos deben estar ordenados)
    merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(combinados));
    mostrar(combinados, "Combinados");

    // Eliminar duplicados consecutivos
    auto nuevoFinal = unique(combinados.begin(), combinados.end());
    combinados.erase(nuevoFinal, combinados.end());
    mostrar(combinados, "Sin duplicados");

    cout << "\n=== Fin del ejemplo general ===\n";
    return 0;
}
