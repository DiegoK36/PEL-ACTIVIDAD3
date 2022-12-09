#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <vector>

using namespace std;

#include <iostream>
using namespace std;

//Plantilla de Función para el VectorPEL
template <typename T> class VectorPel{

private:
T* v_, *space_, *last_;

public:
//Constructor del Vector
VectorPel()  : v_{new T[0]}, space_{v_}, last_{v_} {}

//Constructor copia del Vector
* VectorPel (VectorPel <T> const& v): v_{new T[v.capacity()]}, space_{v_ +v.size()}, last_{v_ + v.capacity()} {
try {
    for (auto i = size_t{0}; i<v.size();++i){
    v_[i]= v[i];
        }
    }
    catch(...) {
        delete[] v_;
        throw;
    }
}

//Destructor del Vector
~ VectorPel() {delete[]v_; cout<<"El Vector se ha eliminado de manera satisfactoria\n";};

//Funciones de nuestro VectorPEL
auto capacity() const -> size_t {return last_ - v_;}
auto size()     const -> size_t {return space_ - v_;}
auto empty()    const -> size_t{return v_== last_;} 

auto begin() -> T*{return v_;}
auto begin() const-> T const* {return v_;}
auto end() -> T* {return space_;}
auto end() const-> T const* {return space_;}

void push_back(T const &val);
};

template<typename T>
   void VectorPel<T>::push_back(T const& val)
   {
      if (space_ == last_) { // capacidad agotada o primera vez que invocamos push_back
         std::size_t cp = capacity(),              // capacidad actual del vector
                     new_cp = (cp == 0)? 2 : 2*cp; // nueva capacidad
         T* new_block = new T[new_cp]; // nuevo bloque de memoria
         try {
            for (auto i = std::size_t{}; i < cp; ++i)
               new_block[i] = v_[i];
            new_block[cp] = val;
         }
         catch (...) { // de lanzarse una excepción...
            delete[] new_block; //... destruimos el nuevo array...
            throw;              // ...y relanzamos la excepción
         }
         // destruimos el array original y reasignamos los punteros:
         delete[] v_;
         v_ = new_block;
         space_ = new_block + cp + 1;
         last_ = new_block + new_cp;
      }
      else {
         *space_ = val;
         ++space_;
      }
   }

class Disco {
    
    private:
    string titulo, tipo;
    float precio;
    bool alquilado;

    public:
    Disco (string titulo, string tipo, float precio, bool alquilado) {
        this->titulo = titulo;
        this->tipo = tipo;
        this->precio = precio;
        this->alquilado = alquilado;
    }
    ~Disco() {}
};

//Funciones Prototipo
void menu();

//Variables Globales
string titulo, tipo;
float precio;
bool alquilado;

int main(){

    int opcion;
    auto Discos = VectorPel<Disco>{}; // Creamos un vector vacío para los discos
    menu();
    cin>>opcion;
    do {

    switch (opcion) {
    case 1: //Caso para cargar un Disco nuevo
        cout<<"*****Cargar un Disco en el Sistema*****\n"<<endl;
        cout<<"Introduce el Titulo del Disco"<<endl;
        cin>>titulo;
        cout<<"Introduce el Tipo del Disco"<<endl;
        cin>>tipo;
        cout<<"Introduce el Precio del Disco"<<endl;
        cin>>precio;
        Discos.push_back(Disco{titulo,tipo,precio,false});
        cout<<"\nDisco creado CORRECTAMENTE!"<<endl;
        break;

    case 2: //Caso para buscar un Disco por Titulo
        cout<<"*****Buscar un Disco en el Sistema*****\n"<<endl;
        break;

    case 3: //Caso para alquilar un Disco
        cout<<"*****Alquilar un Disco en el Sistema*****\n"<<endl;
        break;

    case 4: //Caso para devolver un Disco
        cout<<"*****Devolver un Disco en el Sistema*****\n"<<endl;
        break;

    case 6: //Opcion para regresar al Menu
        system("cls");
        menu();
        cin>>opcion;
        break;

    case 0: //Opcion para salir del menu
        break;
    
    default: //En caso de no escoger las opciones indicadas
        cout<<"\nElige una opcion valida: | SALIR -> 0 | VOLVER -> 6 |\n";
        cin>>opcion;
        break;
    }

    } while (opcion!=0);
    
    getch();
    return 0;
}

//Funciones
void menu() {
    cout<<"*****SISTEMA DE ALQUILER*****\n"<<endl;
    cout<<"1 - Cargar un Disco nuevo en el sistema\n";
    cout<<"2 - Buscar un Disco mediante el titulo en el sistema\n";
    cout<<"3 - Alquilar un Disco\n";
    cout<<"4 - Devolver un Disco\n";
    cout<<"0 - Salir\n";
    cout<<"\nEscoja la opcion deseada [0-4]: ";
}