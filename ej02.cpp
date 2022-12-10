#include <iostream>


#include <string> //manejo de strings
#include <cctype>
#include <algorithm> //manejo de espacios

using namespace std;

int exit_ =0, found, found2; //variable modificable para salida o continuacion del codigo, y de marcadores de encontrado

class videoclub { //creacion de clase
public:
    string titulo;
    int precio;
    string tipo;
    int alquilado;

    videoclub(){ //constructor inicializado a "0"
        titulo = "";
        precio = 0;
        tipo = "";
        alquilado = 0;
    };
    videoclub(string x, int y, string z, int p){ //asignacion de variables
        titulo=x;
        precio=y;
        tipo=z;
        alquilado=p;
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

    auto begin(int n) const -> T* {return n + v_;} //funcion que espera un parametro y devuele un puntero a dicha posicion en el vector
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

    void dato(int posicion, string dato, int tam, int accion) { //funcion que muestra la busqueda, donde se espera; Posicion en el vector, el dato introducido por el usuario, el tamaño del vector y la accion a realizar.

        string opcion;

        videoclub aux; //creamos una variable auxiliar de tipo videoclub

        aux = *begin(posicion); //le asignamos a la variable el puntero que apunta a begin pasandole la posicion que queremos ver

        switch (accion) {
            case 1: //alquilar
                if (aux.titulo==dato){ //busqueda medinate titulo
                    if(aux.alquilado==0){ //si no esta disponible se notifica
                        cout << aux.titulo << " ya esta alquilado\n";
                        found=1; //se iguala a 1 la variable de busqueda al haberse realizado esta
                    }
                    else{ //en caso de estar disponible...
                        cout << "Titulo: " << aux.titulo << " | Precio: " << aux.precio << " euros | Tipo: " << aux.tipo << " | Disponible: SI" << endl; //se muestra su informacion
                        cout << "Desea alquilarlo?\n [1] SI\n [0] NO\n"; //se pregunta si desea ser alquilado
                        cin >> opcion;

                        if ((opcion=="1")||(opcion=="SI")){ //en caso de que se desee alquilar...
                            aux.titulo, aux.precio, aux.tipo, aux.alquilado=0; //se cambia los datos de este
                            v_[posicion] = aux; //se reescribre en el vector
                            cout << aux.titulo << " ha sido alquilada por usted\n"; //se notifica de que ha sido alquilado
                        }
                        found=1; //se iguala a 1 la variable de busqueda al haberse realizado esta
                    }
                }
                else if ((posicion==(tam-1))&&(found==0)){ //en caso de estar en la ultima iteracion del bucle de la funcion, mas no haberse encontrado...

                    cout << "No hay ningun disco con dicho titulo\n"; //se notifica de que no existe
                }
                break;
            case 2: //devolver
                if (aux.titulo==dato){ //busqueda medinate titulo
                    aux.titulo, aux.precio, aux.tipo, aux.alquilado=1; //se cambia los datos de este
                    v_[posicion] = aux; //se reescribre en el vector
                    cout << aux.titulo << " acaba de ser devuleta\n"; //se notifica de que ha sido devuelto
                    found2=1; //se iguala a 1 la variable de busqueda al haberse realizado esta
                }
                else if ((posicion==(tam-1))&&(found2==0)){ //en caso de estar en la ultima iteracion del bucle de la funcion, mas no haberse encontrado...

                    cout << "No hay ningun disco con dicho titulo\n"; //se notifica de que no existe
                }
                break;
        }
    }
};

VectorPEL<videoclub>* v = new VectorPEL<videoclub>; //free store

void alquilar(){ //funcion donde se alquilan los discos
    string discoA;
    int accion=1;

    cin.ignore(); //Ya que utilizaremos getline para conseguir el dato entero por parte del usuario necesitaremos esta linea para asi cuando se ejecute por segunda vez el bucle podamos seguir introduciendo datos
    cout << "¿Que disco desea buscar?:" << endl;
    getline(cin, discoA); //Recogida del string con espacios

    discoA.erase(std::remove_if(discoA.begin(), discoA.end(), ::isspace), discoA.end()); //QUita los espacios del string

    for (int i = 0; i < discoA.length(); ++i) { //Convierte a mayusculas la frase
        if (discoA[i]>='a' && discoA[i]<='z'){
            discoA[i]=discoA[i]-32;
        }
    }

    found=0;
    exit_ = 1;

    int tam = v->size(); //guardamos el tamaño del vector

    for(int i=0; i<v->size(); i++){ //Realizamos un bucle tantas veces como objetos haya en el vector

        v->dato(i, discoA, tam, accion); //lamada a la funcion pasandole los parametros de posicion en el vector, el dato introducido por el usuario, el tamaño del vector y la accion a realizar
    }
}

void devolver(){ //funcion donde se devuelven los discos
    string discoD;
    int accion=2;

    cin.ignore(); //Ya que utilizaremos getline para conseguir el dato entero por parte del usuario necesitaremos esta linea para asi cuando se ejecute por segunda vez el bucle podamos seguir introduciendo datos
    cout << "¿Que disco desea devolver?:" << endl;
    getline(cin, discoD); //Recogida del string con espacios

    discoD.erase(std::remove_if(discoD.begin(), discoD.end(), ::isspace), discoD.end()); //QUita los espacios del string

    for (int i = 0; i < discoD.length(); ++i) { //Convierte a mayusculas la frase
        if (discoD[i]>='a' && discoD[i]<='z'){
            discoD[i]=discoD[i]-32;
        }
    }

    found2=0;

    int tam = v->size(); //guardamos el tamaño del vector

    for(int i=0; i<v->size(); i++){ //Realizamos un bucle tantas veces como objetos haya en el vector

        v->dato(i, discoD, tam, accion); //lamada a la funcion pasandole los parametros de posicion en el vector, el dato introducido por el usuario, el tamaño del vector y la accion a realizar
    }
}

int main() {

    int elec;

    videoclub a, b, c, d, e;

    a.titulo="HALLOWEEN", a.precio=3, a.tipo="DVD", a.alquilado=0; //declaramos los atributos con sus datos para crear el objeto
    b.titulo="AVATAR", b.precio=9, b.tipo="BLUE RAY", b.alquilado=1; //declaramos los atributos con sus datos para crear el objeto
    c.titulo="MATRIX", c.precio=11, c.tipo="DVD", c.alquilado=1; //declaramos los atributos con sus datos para crear el objeto
    d.titulo="NOP", d.precio=5, d.tipo="DVD", d.alquilado=0; //declaramos los atributos con sus datos para crear el objeto
    e.titulo="PUF2", e.precio=7, e.tipo="BLUE RAY", e.alquilado=1; //declaramos los atributos con sus datos para crear el objeto

    v->push_back(a), v->push_back(b), v->push_back(c), v->push_back(d), v->push_back(e); //mandamos al vector los 5 objetos creados

    while (elec!=3) {
        cout << "\n";
        cout << "[1] Alquilar un disco\n";
        cout << "[2] Devolver un disco\n";
        cout << "[3] Salir\n";
        cout << "¿Que accion desea realizar?\n";
        cout << "\n";

        cin >> elec;

        while (cin.fail()) //Bucle para manejo de errores en input
        {
            cin.clear();
            cin.ignore();
            cout << "Error, introduzca dato de tipo entero: ";
            cin >> elec;
        }

        switch (elec) {
            case 1:
                alquilar();
                break;
            case 2:
                devolver();
                break;
            case 3:
                cout << "Gracias por visitar nuestro videoclub.\n";
                break;
            default:
                cout << "\n";
                cout << "Opcion inexistente.\n";
                break;
        }
    }
}