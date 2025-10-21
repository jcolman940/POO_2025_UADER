#include <iostream>

using namespace std;

template<class T>
class vector {
    private:
        T* data;
        size_t size; //cantidad de elementos
        size_t capacity; //maximo de espacios vector
        void resize(size_t newcapacity);
        
    public:
        vector();
        T get_in_pos(size_t pos){return this->data[pos];};
        void add(T datos);// agregar elemento;
        void remove(size_t pos);// remover un dato pasando la pos
        size_t getsize(){return this->size;}// retorna la cantidad de elementos
};

template<class T>
vector<T>::vector(){
    this->size = 0;//cantidad de elementos del vector
    this->capacity = 2; // capacidad maxima(temporalmente) del vector
    this->data = new T[2];// vector dinamico
}

template<class T>
void vector<T>::add(T datos) {
    if (this->size == this->capacity) {
        this->resize(this->capacity*2);
    }
    this->data[this->size++] = datos;// se incrementa post asignacion
}    

class Alumno {
    private:
        int dni;
        char* nya;
        vector<double> parcial;
        vector<double> recup;

    public:
        Alumno () : dni (0), nya ("") {}
        void agregarParcial (double parcial);
        void agregarRecuperatorio (double recup);
        friend ostream& operator << (ostream& os, Alumno& p);
    
};
