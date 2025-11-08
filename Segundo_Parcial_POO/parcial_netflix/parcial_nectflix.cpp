#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

struct datos_catalogo {
    int nro;
    char nombre [200];
    char tipo; // serie o pelicula
};

struct datos_votaciones {
    int nro; // id de pelicula o serie
    int votacion;
};

class Catalogo {
    private:
        int nro;
        string nombre;
        char tipo; // s o p
        vector<int> valoracion;
    public:
        Catalogo (int nro, string nombre, char tipo);
        void agregarVoto (int voto) ;
        double getPromedioValoracion () const;
        int getCantidadVotos() const { return valoracion.size();};
        int getNro() const;
        string getNombre() const;
        char getTipo() const;

        // Setters
        void setNro(int n);
        void setNombre(string n);
        void setTipo(char t);
};

Catalogo :: Catalogo (int nro, string nombre, char tipo){
    this->nro = nro;
    this->nombre = nombre;
    this->tipo = tipo;
}

void Catalogo :: agregarVoto (int voto){
    valoracion.push_back (voto);
}

double Catalogo :: getPromedioValoracion () const{

    if (valoracion.empty()) {
        return 0.0;
    }
    // 2. Sumar todos los votos guardados en el vector
    int sumaTotal = 0;
    for (int voto : valoracion) {
        sumaTotal += voto;
    }
    // 3. Calcular el promedio
    //    (double)sumaTotal -> Convierte la suma a decimal
    //    valoracion.size() -> El número total de votos
    return (double)sumaTotal / valoracion.size();
}


int Catalogo :: getNro () const { return this->nro;}
string Catalogo :: getNombre () const { return this->nombre;}
char Catalogo :: getTipo () const { return this->tipo;}

//CLASE GESTORA

class Plataforma {
    private:
        vector<Catalogo> VecCatalogo;
    public: 
        Plataforma () {};
        void leerCatalogo ();
        void leerVotaciones ();
        void escribirCatalogo ();
        void topFive ();
        void mostrarMasVotadas ();
        void contarVotosPorTipo();
};

void Plataforma :: leerCatalogo (){
    ifstream archivoCatalogo("catalogo.dat", ios::binary);
    if (archivoCatalogo.fail()){
        cout<<"ERROR\n";
    }
    datos_catalogo datCat;

    while(archivoCatalogo.read((char*)&datCat, sizeof(datCat))){

        this->VecCatalogo.push_back(Catalogo(datCat.nro, datCat.nombre, datCat.tipo));

    }
    archivoCatalogo.close();
}

void Plataforma :: leerVotaciones (){
    ifstream archivoVotaciones("votaciones.dat", ios::binary);
    if (archivoVotaciones.fail()){
        cout<<"ERROR\n";
    }   
    datos_votaciones datVot;
    
    while (archivoVotaciones.read((char*) & datVot, sizeof(datVot))){
        for (Catalogo& c : VecCatalogo){
            if (datVot.nro == c.getNro()){
                c.agregarVoto (datVot.votacion);
            }
        }    
    }
    archivoVotaciones.close();
}

bool compararPorNombre(const Catalogo& a, const Catalogo& b) {
    return a.getNombre() < b.getNombre();
}

void Plataforma :: escribirCatalogo (){
    sort(this->VecCatalogo.begin(), this->VecCatalogo.end(), compararPorNombre);

    // 2. ABRIR ARCHIVO DE TEXTO 
    ofstream archivoTexto("listado_catalogo.txt");
    if (archivoTexto.fail()) {
        cout << "ERROR al crear el archivo de texto." << endl;
        return;
    }

    for (const Catalogo& c : VecCatalogo) {
        archivoTexto << c.getNombre() << ", Valoracion " << c.getPromedioValoracion() << "\n";
    }

    archivoTexto.close();
}

bool compararPorValoracion(const Catalogo& a, const Catalogo& b) {
    return a.getPromedioValoracion() > b.getPromedioValoracion();
}

void Plataforma :: topFive () {
    // 1. ORDENAR (¡Perfecto!)
    sort(this->VecCatalogo.begin(), this->VecCatalogo.end(), compararPorValoracion);

    cout << "--- Top 5 Peliculas/Series por Valoracion ---" << endl;

    // 2. MOSTRAR LOS PRIMEROS 5
    // Usamos un 'for' con un índice 'i'
    for (size_t i = 0; i < 5; i++) {
        
        // ¡Importante! Verificamos si 'i' se pasó del tamaño del vector
        if (i >= VecCatalogo.size()) {
            break; // Salimos del bucle si ya no hay más items
        }
        
        // Obtenemos el item en la posición 'i'
        const Catalogo& c = VecCatalogo[i];
        
        // Imprimimos sus datos
        cout << (i + 1) << ". " << c.getNombre() 
             << " (Promedio: " << c.getPromedioValoracion() << ")" << endl;
    }
}

bool compararPorCantidadVotos(const Catalogo& a, const Catalogo& b) {
    return a.getCantidadVotos() > b.getCantidadVotos();
}

void Plataforma::mostrarMasVotadas() {
    if (VecCatalogo.empty()) {
        cout << "No hay items en el catalogo." << endl;
        return;
    }

    // 1. Usamos max_element (STL) con nuestro nuevo comparador
    //    Esto nos da un iterador a UN item con la mayor cantidad de votos.
    auto it_max = std::max_element(VecCatalogo.begin(), VecCatalogo.end(), compararPorCantidadVotos);

    // 2. Obtenemos ese número máximo de votos
    int maxVotos = it_max->getCantidadVotos();

    cout << "--- Item(s) con mas cantidad de votos (" << maxVotos << " votos) ---" << endl;

    // 3. Recorremos el vector DE NUEVO e imprimimos TODOS los que
    //    coincidan con ese número máximo.
    //    Esto resuelve el "el o las".
    for (const Catalogo& c : VecCatalogo) {
        if (c.getCantidadVotos() == maxVotos) {
            cout << "- " << c.getNombre() << endl;
        }
    }
}

void Plataforma::contarVotosPorTipo()
{
    if(this->VecCatalogo.empty())
    {
        cout << "No hay películas o series en la plataforma." << endl;
        return;
    }
    
    // 1. Crea un mapa: la clave es el 'tipo' (char), el valor es el 'conteo' (size_t)
    map<char, size_t> votosPorTipo;

    // 2. Carga el mapa: recorre el vector y acumula los votos
    for(const Catalogo& c : this->VecCatalogo)
    {
        // Si la clave (ej. 's') no existe, la crea con valor 0.
        // Luego, le SUMA la cantidad de votos de 'c'.
        votosPorTipo[c.getTipo()] += c.getCantidadVotos();
    }

    cout << "--- Votos totales por Tipo ---" << endl;
    // 3. Imprime el mapa (usando el 'for' moderno para mapas)
    for (auto const& par : votosPorTipo) 
    {
        // par.first es la Clave ('s' o 'p')
        // par.second es el Valor (el total de votos acumulado)
        cout << "Tipo: " << par.first << " | Cantidad total de votos: " << par.second << endl;
    }
}