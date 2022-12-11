#include <iostream>

#include <string> //manejo de strings
#include <cctype> //
#include <algorithm> //manejo de espacios
#include <functional>

using namespace std;

int exit_ =0; //variable modificable para salida o continuacion del codigo

class album //creacion de clase
{
public:
    string titulo;
    string grupo;
    string genero;

    album(){ //constructor inicializado a "0"
        titulo = "";
        grupo = "";
        genero = "";
    };
    album(string x, string y, string z){ //asignacion de variables
        titulo=x;
        grupo=y;
        genero=z;
    }

};

template<typename T> class VectorPEL { //plantilla de vectro creado en clase
private:
    T * v_, * space_, * last_;

public:
    VectorPEL() : v_{new T [0]}, space_{v_}, last_{v_} {}
    VectorPEL(VectorPEL<T> const& v) : v_{new T[v.capacity()]}, space_{v_ + v.size()}, last_{v_ + v.capacity()} {
        try{
            for(auto i = size_t{0}; i< v.size(); i++){
                v_[i] = v[i];
            }
        }
        catch (...){
            delete[] v_;
            throw;
        }
    }

    ~VectorPEL() {delete[] v_;}

    auto capacity() const -> size_t { return last_ - v_; }
    auto size() const -> size_t { return space_ - v_; }
    auto empty() const -> bool { return v_ == last_; }

    T mostrar_dato(int n) {return v_[n];}

    auto begin(int n) const -> T* {return n + v_;} //funcion que espera un parametro y devuelve un puntero a dicha posicion en el vector
    auto end() const -> T* {return space_;}

    auto push_back(T const& valor) {
        if (space_ == last_) {
            size_t cp = capacity(), new_cp = (cp == 0)? 2:2*cp;
            T* new_block = new T[new_cp];
            try{
                for(auto i = size_t{0}; i < cp; i++) {
                    new_block[i] = v_[i];
                }
                new_block[cp] = valor;
            }
            catch (...) {
                delete[] new_block;
                throw;
            }
            delete[] v_;
            v_ = new_block;
            space_ = new_block + cp + 1;
            last_ = new_block + new_cp;
        }
        else{
            *space_ = valor;
            ++space_;
        }
    }

    int dato(int posicion, string dato, int tam) { //funcion que muestra la busqueda donde se espera; Posicion en el vector, el dato introducido por el usuario, y el tamaño del vector

        int found;
        string alb[3]; //cramos un array para almacenar el objeto desmenuzado en sus atributos

        album aux; //creamos una variable auxiliar de tipo albunm
        aux = *begin(posicion); //le asignamos a la variable el puntero que apunta a begin pasandole la posicion que queremos ver

        alb[0] = aux.titulo; //rellenamos el array con los atributos
        alb[1] = aux.genero; //rellenamos el array con los atributos
        alb[2] = aux.grupo; //rellenamos el array con los atributos

        for(int i=0; i<3; i++){ //bucle oomo busqueda del dato del usuario y los datos almacenados
            if (dato==alb[i]) { //Si hay coincidencia se imprime toda la informacion acerca del album
                cout << alb[0] << endl;
                cout << alb[1] << endl;
                cout << alb[2] << endl;
                i = 3; //al tener toda la informacion se finaliza el bucle de manrea inmediata
                found = 2; //se "activa" el localizador
            }
            else if (((i+1)==3)&&(posicion==(tam-1))){ //en caso de estar en la ultima iteracion del bucle de la funcion mas el bucle de donde se llama a la funcion...
                    if (found != 2) { //en caso de no haber un localizador significara que el dato introducido por el usuario es eroneo y se le notifica
                        cout << "No hay nada relacionado con dicha palabra\nQuiere introducir otra?\n [1] SI\n [0] NO\n"; //se le pregunta si desea realizar otra busqueda
                        cin >> exit_;
                        while (cin.fail()) //Bucle para manejo de errores en input
                        {
                            cin.clear();
                            cin.ignore();
                            cout << "Error, introduzca dato de tipo entero: ";
                            cin >> exit_;
                        }

                    }
            }
        }
        return exit_; //se devuelve la decision del usuario
    };
};

int main() {

    VectorPEL<album>* v = new VectorPEL<album>; //free store

    string dato;
    int onetime=0;

    album a, b, c, d, e;

    a.titulo="HOTSPACE", a.genero="ROCK", a.grupo="QUEEN"; //declaramos los atributos con sus datos para crear el objeto
    b.titulo="STARSHOPPING", b.genero="ALTERNATIVE", b.grupo="LILPEEP"; //declaramos los atributos con sus datos para crear el objeto
    c.titulo="SUNFLOWER", c.genero="HIPHOP", c.grupo="POSTMALONE"; //declaramos los atributos con sus datos para crear el objeto
    d.titulo="VICEVERSA", d.genero="REGGAETON", d.grupo="RAUWALEJANDRO"; //declaramos los atributos con sus datos para crear el objeto
    e.titulo="ONSTAGE", e.genero="ROCK", e.grupo="ELVIS"; //declaramos los atributos con sus datos para crear el objeto

    v->push_back(a), v->push_back(b), v->push_back(c), v->push_back(d), v->push_back(e); //mandamos al vector los 5 objetos creados

    do {

        if (onetime!=0){ //Condicional que restringe la entrada en la primera iteracion del codigo
            cin.ignore(); //Ya que utilizaremos getline para conseguir el dato entero por parte del usuario necesitaremos esta linea, para asi cuando se ejecute por segunda vez el bucle podamos seguir introduciendo datos
        }
        onetime=1;

        cout << "¿Que palabra desea buscar?:" << endl;
        getline(cin, dato); //Recogida del string con espacios

        dato.erase(std::remove_if(dato.begin(), dato.end(), ::isspace), dato.end()); //QUita los espacios del string

        for (int i = 0; i < dato.length(); ++i) { //Convierte a mayusculas la frase
            if (dato[i]>='a' && dato[i]<='z'){
                dato[i]=dato[i]-32;
            }
        }

        exit_ = 0;

        int tam = v->size(); //miramos el tamaño del vector

        for(int i=0; i<v->size(); i++){ //Realizamos un bucle tantas veces como objetos haya en el vector

            v->dato(i, dato, tam); //lamada a la funcion pasandole los parametros de posicion en el vector, el dato introducido por el usuario, y el tamaño del vector
        }
    }
    while (exit_==1); //mientras siga a 1 la variable exit no termina de preguntar al usuario.
}