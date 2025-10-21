#include <iostream>
#include <deque>     // Para std::deque, (doble cola)
#include <queue>     // Para std::queue, (cola FIFO)
#include <stack>     // Para std::stack, (pila, LIFO)
#include <algorithm> // Para reverse(), sort(), etc.
using namespace std;

// Función auxiliar para mostrar un deque
void mostrarDeque(const deque<int>& d) {
    cout << "Deque: ";
    for (auto it = d.begin(); it != d.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

// Función para mostrar una queue (usando copia)
template <typename T>
void mostrarQueue(queue<T> q) {
    cout << "Queue (front -> back): ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

// Función para mostrar una stack (usando copia)
template <typename T>
void mostrarStack(stack<T> s) {
    cout << "Stack (top -> bottom): ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

int main() {
    cout << "=============================\n";
    cout << "       DEQUE<T> ejemplos\n";
    cout << "=============================\n";
    // 🔹 1. DEQUE (cola doble)
    deque<int> d;

    // Agregar elementos al frente y atrás
    d.push_back(10);   // [10]
    d.push_front(5);   // [5,10]
    d.push_back(20);   // [5,10,20]
    d.push_front(1);   // [1,5,10,20]
    mostrarDeque(d);

    // Acceso a extremos
    cout << "Front: " << d.front() << " | Back: " << d.back() << endl;

    // Eliminar elementos de ambos lados
    d.pop_front(); // elimina 1
    d.pop_back();  // elimina 20
    cout << "DespuEs de pop_front() y pop_back(): ";
    mostrarDeque(d);

    // Insertar y borrar en el medio
    auto it = d.begin();
    advance(it, 1);
    d.insert(it, 99); // [5,99,10]
    mostrarDeque(d);

    it = d.begin();
    advance(it, 1);
    d.erase(it); // elimina 99
    mostrarDeque(d);

    cout << "TamaNo final del deque: " << d.size() << endl;


    cout << "\n=============================\n";
    cout << "        QUEUE<T> ejemplos\n";
    cout << "=============================\n";
    // 🔹 2. QUEUE (FIFO)
    queue<int> q;

    // Agregar (push) al final y quitar (pop) del frente
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);

    cout << "Front: " << q.front() << " | Back: " << q.back() << endl;
    mostrarQueue(q);

    // Quitar elementos (pop) y mostrar paso a paso
    q.pop(); // elimina 10
    cout << "Despues de pop(), nuevo front: " << q.front() << endl;

    // Agregar más
    q.push(50);
    q.push(60);
    mostrarQueue(q);

    cout << "Tamano final del queue: " << q.size() << endl;


    cout << "\n=============================\n";
    cout << "        STACK<T> ejemplos\n";
    cout << "=============================\n";
    // 🔹 3. STACK (LIFO)
    stack<int> s;

    // Apilar (push) y desapilar (pop)
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    cout << "Top actual: " << s.top() << endl;
    mostrarStack(s);

    // Pop elimina el último insertado
    s.pop(); // elimina 4
    cout << "Despues de pop(), top: " << s.top() << endl;

    // Agregar más
    s.push(10);
    s.push(20);
    mostrarStack(s);

    cout << "Tamaño final del stack: " << s.size() << endl;

    cout << "\n=== Fin del ejemplo general ===\n";
    return 0;
}

/*
| Contenedor | Tipo                               | Acceso permitido | Inserciones rápidas | Acceso aleatorio | Métodos clave                                              |
| ---------- | ---------------------------------- | ---------------- | ------------------- | ---------------- | ---------------------------------------------------------- |
| `deque<T>` | Cola doble                         | Ambos extremos   | ✅ (frente y final)  | ✅                | `push_front()`, `push_back()`, `pop_front()`, `pop_back()` |
| `queue<T>` | FIFO (primero entra, primero sale) | Solo extremos    | ✅                   | ❌                | `push()`, `pop()`, `front()`, `back()`                     |
| `stack<T>` | LIFO (último entra, primero sale)  | Solo un extremo  | ✅                   | ❌                | `push()`, `pop()`, `top()`                                 |

-Usa "deque" si necesitás agregar o quitar tanto al inicio como al final.

-Usa "queue" para procesar tareas en orden de llegada.

-Usa "stack" para problemas tipo deshacer/rehacer, evaluación de expresiones, etc.
*/