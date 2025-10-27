#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

struct struct_archivo {
    int cod;
    char nombre[50];
    char marca[20];
    char tipo;
    double precio;
};

class Electro {
protected:
    int cod;
    string nombre;
    string marca;
    char tipo;
    double precio;

public:
    // Constructor
    Electro(int cod, string nombre, string marca, char tipo, double precio);
    virtual void actualizar_precios(int mes_actual, double suba_dolar) = 0;
    // ---- Getters (Métodos de acceso) ----
    // Los necesitarás para los incisos b, c y d
    int getCod() const;
    string getNombre() const;
    string getMarca() const;
    char getTipo() const;
    double getPrecio() const;
};

Electro::Electro(int cod, string nombre, string marca, char tipo, double precio) {
    this->cod = cod;
    this->nombre = nombre;
    this->marca = marca;
    this->tipo = tipo;
    this->precio = precio;
    
}

// Getters
int Electro::getCod() const { return this->cod; }
string Electro::getNombre() const { return this->nombre; }
string Electro::getMarca() const { return this->marca; }
char Electro::getTipo() const { return this->tipo; }
double Electro::getPrecio() const { return this->precio; }


class Nacional : public Electro {
public:
    // Constructor (llama al constructor de la clase base)
    Nacional(int cod, string nombre, string marca, char tipo, double precio);
    void actualizar_precios(int mes_actual, double suba_dolar);
};

Nacional::Nacional(int cod, string nombre, string marca, char tipo, double precio)
    : Electro(cod, nombre, marca, tipo, precio) {
    // El cuerpo está vacío porque solo necesitamos llamar al constructor base
}

void Nacional::actualizar_precios(int mes_actual, double suba_dolar) {
    this->precio *= 1.02; // (precio = precio + precio * 0.02)
}

class Importado : public Electro {
    public:
        Importado (int cod, string nombre, string marca, char tipo, double precio);
        void actualizar_precios(int mes_actual, double suba_dolar);
};

Importado::Importado(int cod, string nombre, string marca, char tipo, double precio)
    : Electro(cod, nombre, marca, tipo, precio) {
}

void Importado::actualizar_precios(int mes_actual, double suba_dolar) {
    this->precio += (this->precio * suba_dolar);
}

class Jardin : public Electro {
    public:
        Jardin (int cod, string nombre, string marca, char tipo, double precio);
        void actualizar_precios (int mes_actual, double suba_dolar);
};

Jardin::Jardin(int cod, string nombre, string marca, char tipo, double precio)
    : Electro(cod, nombre, marca, tipo, precio) {
}

void Jardin::actualizar_precios(int mes_actual, double suba_dolar) {
    if (mes_actual == 12) {
        this->precio *= 1.10; // (precio = precio + precio * 0.10)
    }
}


//CLASE GESTORA

class Empresa {
    private:
        vector<Electro*> vecElectro;
    public:
        void leer();
        void precios_actualizados(int mes_actual, double suba_dolar);
        void generarListadoOrdenado ();
        void productos_por_marca ();
        void producto_mas_caro ();
        void producto_menos_caro ();
        void mostrarMasBarato ();
        void mostrarMasCaro ();
};

//b.Lea el archivo binario, actualice todos los precios y genere otro archivo con los precios actualizados.

void Empresa::leer() {
    ifstream archivo("productos.dat", std::ios::binary);
    if (archivo.fail())
    {
        cout<<" ERROR\n";
    }else
    {
        struct_archivo struProd;
        while(archivo.read((char*)&struProd,sizeof(struProd))){
            switch (struProd.tipo)
            {
            case 'N':
                this->vecElectro.push_back(new Nacional(struProd.cod, struProd.nombre, struProd.marca, struProd.tipo, struProd.precio));
                break;
            case 'I':
                this->vecElectro.push_back(new Importado(struProd.cod, struProd.nombre, struProd.marca, struProd.tipo, struProd.precio));
                break;
            case 'J':
                this->vecElectro.push_back(new Jardin(struProd.cod, struProd.nombre, struProd.marca, struProd.tipo, struProd.precio));
                break;
            default:
                break;
            }
        }
    }
    archivo.close();
}

void Empresa::precios_actualizados(int mes_actual, double suba_dolar) {
    std::ofstream archivo("Productos_actualizados.dat", std::ios::binary);
    
    if(archivo.fail()) {
        std::cout << " ERROR\n";
        return;
    }

    struct_archivo struProd;
    for(Electro* prod : this->vecElectro) // Bucle for-each más limpio 
    {
        // ¡1. POLIMORFISMO!
        prod->actualizar_precios(mes_actual, suba_dolar);

        // 2. Preparar la estructura
        struProd.cod = prod->getCod();
        
        // (Usando la versión segura strncpy)
        strncpy(struProd.nombre, prod->getNombre().c_str(), 49);
        struProd.nombre[49] = '\0';
        strncpy(struProd.marca, prod->getMarca().c_str(), 19);
        struProd.marca[19] = '\0';
        
        struProd.tipo = prod->getTipo();
        struProd.precio = prod->getPrecio();

        // 3. Escribir
        archivo.write((char*)&struProd,sizeof(struProd));
    }
    archivo.close();
}

/*c.Lea el archivo binario y genere un listado de precios el cual debe estar ordenado por 
nombre del producto (utilice stl) y luego genere un archivo de texto a partir de este listado 
con el siguiente formato:  nombre, marca ............$ precio.*/

bool compararPorNombre(const Electro* a, const Electro* b) {
    return a->getNombre() < b->getNombre();
}

void Empresa::generarListadoOrdenado() {
    
    // 1. ORDENAR (¡Usando STL 'sort'!)
    //    Le pasamos el inicio del vector, el fin del vector, y nuestro
    //    criterio de ordenación.
    std::sort(this->vecElectro.begin(), this->vecElectro.end(), compararPorNombre);

    // 2. ABRIR ARCHIVO DE TEXTO (¡NO binario!)
    std::ofstream archivoTexto("listado_precios.txt");
    if (archivoTexto.fail()) {
        cout << "ERROR al crear el archivo de texto." << endl;
        return;
    }

    /*// 3. CONFIGURAR FORMATO DE PRECIO
    //    Esto es para que los precios se vean bien (ej: 15000.50)
    archivoTexto << std::fixed << std::setprecision(2);*/

    // 4. RECORRER EL VECTOR (que ya está ordenado) Y ESCRIBIR
    for (const Electro* prod : this->vecElectro) {
        archivoTexto << prod->getNombre() << ", " << prod->getMarca() << ".$ " << prod->getPrecio() << "\n";
    }

    archivoTexto.close();
}

/*d.Es necesario saber cuántos productos hay por marca y cual producto es el más caro y el 
más barato, utilice stl.*/

void Empresa::productos_por_marca () {
    map <string , int> conteoMarcas;
    // 1. Recorremos el vector
for (Electro* prod : this->vecElectro) {
    // 2. Obtenemos la clave (la marca)
    string marca = prod->getMarca();
    //    Usamos la marca como índice y le sumamos 1
    conteoMarcas[marca]++;
}
for (auto &it : conteoMarcas)
for (auto it = conteoMarcas.begin(); it != conteoMarcas.end(); ++it) {
        cout << " Marca: " << it->first << " Cantidad: " << it->second;
        cout << endl;
    }
}

bool compararPorPrecio(const Electro* a, const Electro* b) { 
    return a->getPrecio() < b->getPrecio(); 
}

void Empresa::mostrarMasBarato() {
    
    // 1. Siempre verificar que el vector no esté vacío
    if (this->vecElectro.empty()) {
        cout << "No hay productos en la lista." << endl;
        return;
    }
    //min y max devuelve un iterador de punteros
    // 2. Usar min_element con nuestro comparador
    //    'it_barato' es un iterador a la posición del producto más barato
    auto it_barato = std::min_element(this->vecElectro.begin(), this->vecElectro.end(), compararPorPrecio);

    // 3. Obtener el puntero Electro* desde el iterador
    Electro* prodBarato = *it_barato; 

    // 4. Imprimir
    cout<<"El producto mas barato es: "<<prodBarato->getNombre();
}

void Empresa::mostrarMasCaro() {
    
    // 1. Siempre verificar que el vector no esté vacío
    if (this->vecElectro.empty()) {
        cout << "No hay productos en la lista." << endl;
        return;
    }
    //min y max devuelve un iterador de punteros
    // 2. Usar min_element con nuestro comparador
    //    'it_barato' es un iterador a la posición del producto más barato
    auto it_caro = std::max_element(this->vecElectro.begin(), this->vecElectro.end(), compararPorPrecio);

    // 3. Obtener el puntero Electro* desde el iterador
    Electro* prodCaro = *it_caro; 

    // 4. Imprimir
    cout<<"El producto mas barato es: "<<prodCaro->getNombre();
}