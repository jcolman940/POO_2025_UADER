#include <iostream>
#include <cstring>

using namespace std;

template <class T>
class Vector {
    private:
        T* data;
        size_t size;
        size_t capacity;
        void resize(size_t newcapacity);
    public:
        Vector ();
        ~Vector();
        void add (T datos);
        void remove (size_t pos);
        void removeOcurrencia (T datos);
        T& operator[](size_t pos) const;
        T get_in_pos (size_t pos){ return this->data[pos];};
        size_t getsize() const { return this->size; }
};

template <class T>
Vector<T> :: Vector(){
    this->size = 0;
    this->capacity = 2;
    this->data = new T[this->capacity];
}

template <class T>
Vector<T>::~Vector() {
    delete[] this->data;
}

template <class T>
void Vector<T>::resize(size_t newcapacity) {
    T* temp = new T[newcapacity];
    for (size_t i = 0; i < this->size; i++) {
        temp[i] = this->data[i];
    }
    delete[] this->data;
    this->data = temp;
    this->capacity = newcapacity;
}

template <class T>
void Vector<T>::add(T datos){
    if (this->size == this->capacity){
        this->resize(this->capacity*2);
        
    }
    this->data[this->size++]=datos;
}


template <class T>
void Vector<T>::remove(size_t pos) {
    if (pos >= this->size) return; // Validación básica
    for (size_t i = pos; i < this->size - 1; i++) // Corrección en el límite: size - 1
        this->data[i] = this->data[i+1];
    this->size--;
}

template <class T>
void Vector<T>::removeOcurrencia(T datos) {
    for (size_t i = 0; i < this->size; /* no incrementa aqui */) {
        if (this->data[i] == datos) {
            remove(i); // remove(i) ya decrementa size y mueve elementos a la izquierda
        } else {
            i++; // Solo avanza si no se eliminó
        }
    }
}

template <class T>
T& Vector<T>::operator[](size_t pos) const {
    if (pos >= this->size) {
        throw std::out_of_range("Indice fuera de rango");
    }
    return this->data[pos];
}

// ========================================
// Clase base abstracta Producto
// ========================================

char* copystr(const char* str) {
    if (!str) str = "";
    char* newstr = new char[strlen(str) + 1];
    strcpy(newstr, str);
    return newstr;
}

class Producto {
protected:
    int numero;
    char* descripcion;
    double precio;

public:
    Producto() { // ✅ constructor por defecto, para compilar ejemplo
        numero = 0;
        descripcion = copystr("");
        precio = 0.0;
    }
    Producto(int numero, const char* descripcion, double precio);
    int getnumero() const { return this->numero; }
    const char* getdescripcion() const { return this->descripcion; }
    virtual double getprecio() const = 0;
};

Producto::Producto(int numero, const char* descripcion, double precio) {
    this->numero = numero;
    this->descripcion = copystr(descripcion);
    this->precio = precio;
}

// ========================================
// Clase Parte (concreta)
// ========================================
class Parte : public Producto {
public:
    Parte() : Producto() {} // ✅ constructor vacío
    Parte(int numero, const char* descripcion, double precio)
    : Producto(numero, descripcion, precio) {}

    double getprecio() const override {return this->precio;}
};

// ========================================
// Clase BicicletaArmada (compuesta por partes)
// ========================================
class BicicletaArmada : public Producto {
private:
    Vector<Parte> partes;

public:
    BicicletaArmada(int numero, const char* descripcion)
    : Producto(numero, descripcion, 0.0) {}

    void add_parte(const Parte& p) {partes.add(p);}
    double getprecio() const override;
};

double BicicletaArmada::getprecio() const {
    double total = 0;
    for (size_t i = 0; i < partes.getsize(); i++)
        total += partes[i].getprecio();
    return total;
}

// ========================================
// Clase Oferta (usa composición, NO herencia)
// ========================================
class Oferta {
private:
    int numero;
    char* descripcion;
    Vector<Producto*> productos_v;

public:
    Oferta(int numero, const char* descripcion) {
        this->numero = numero;
        this->descripcion = copystr(descripcion);
    }

    void add_producto(Producto* p) {productos_v.add(p);}
    double getprecio() const;
    friend ostream& operator<<(ostream& os, const Oferta& o);
};

double Oferta::getprecio() const {
    double monto_total = 0;
    for (size_t i = 0; i < productos_v.getsize(); i++)
        monto_total += productos_v[i]->getprecio();
    return monto_total * 0.80; // Aplica 20% de descuento
}

ostream& operator<<(ostream& os, const Oferta& o) {
    os << "========================================" << endl;
    os << "Oferta N" << o.numero << " - " << o.descripcion << ":" << endl;
    for (size_t i = 0; i < o.productos_v.getsize(); i++) {
        os << "  - " << o.productos_v[i]->getdescripcion()
        << " ($" << o.productos_v[i]->getprecio() << ")" << endl;
    }
    os << "Precio total (con 20% desc): $" << o.getprecio() << endl;
    os << "========================================" << endl;
    return os;
}

// ========================================
// Clase Bicicleteria (administra productos y ofertas)
// ========================================
class Bicicleteria {
private:
    Vector<Producto*> inventario_productos;
    Vector<Oferta*> ofertas_v;

public:
    Bicicleteria() {}

    void add_producto(Producto* p);
    void add_oferta(Oferta* o) {ofertas_v.add(o);}
    void mostrar_inventario() const;
    void mostrar_ofertas() const;
};

void Bicicleteria::add_producto(Producto* p) {
    inventario_productos.add(p);
};

void Bicicleteria::mostrar_inventario() const {
    cout << "\n--- Inventario General de la Tienda ---" << endl;
    if (inventario_productos.getsize() == 0) {
        cout << "(Inventario vacío)" << endl;
        return;
    }
    for (size_t i = 0; i < inventario_productos.getsize(); i++) {
        cout << " - " << inventario_productos[i]->getdescripcion()
        << " ($" << inventario_productos[i]->getprecio() << ")" << endl;
    }
}

void Bicicleteria::mostrar_ofertas() const {
    cout << "\n--- Listado de Todas las Ofertas ---" << endl;
    if (ofertas_v.getsize() == 0) {
        cout << "(No hay ofertas para mostrar)" << endl;
        return;
    }
    for (size_t i = 0; i < ofertas_v.getsize(); i++)
        cout << *(ofertas_v[i]);
}



// ========================================
// Main de prueba (mínimo)
// ========================================
int main() {
    Bicicleteria tienda;

    // Crear partes
    auto* p1 = new Parte(1, "Rueda", 100);
    auto* p2 = new Parte(2, "Asiento", 50);
    auto* p3 = new Parte(3, "Manubrio", 75);

    tienda.add_producto(p1);
    tienda.add_producto(p2);
    tienda.add_producto(p3);

    // Crear bicicleta
    auto* bici = new BicicletaArmada(10, "Bici Montana");
    bici->add_parte(*p1);
    bici->add_parte(*p2);
    bici->add_parte(*p3);
    tienda.add_producto(bici);

    // Crear oferta
    auto* oferta = new Oferta(100, "Pack Aventura");
    oferta->add_producto(bici);
    oferta->add_producto(p1);
    tienda.add_oferta(oferta);

    tienda.mostrar_inventario();
    tienda.mostrar_ofertas();

    return 0;
}
