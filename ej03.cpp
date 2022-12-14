/* Una universidad del estado nos ha pedido realizar un software, tanto para colgar las notas de los estudiantes como poder verlas
    por parte de estos, hemos decidido hacer estas funcionalidades utilizando dos vectores, ya que uno de los requisitos de este software
    era que las notas se almacenasen por diferentes grupos, por lo que cada vector ha sido un contendor de un solo grupo.
    Otro de los requisitos ha sido que unicamente los profesores pudiesen colgar las notas, por lo que esta funcion queda restringida bajo una contraseña (admin)
    que los profesores tendran, por parte de los alumnos podran acceder al tablon y filtrando por grupo veran todas la notas que han sido corregidas hasta el momento.
 */

#include <iostream>

using namespace std;

class entrada {
    public:
    string nombre;
    string expediente;
    string tipo;
    string calificacion;

    entrada(){
        nombre="";
        expediente="";
        tipo="";
        calificacion="";
    }
    entrada(string a,string b,string c, string d){
        nombre=a;
        expediente=b;
        tipo=c;
        calificacion=d;
    }
};

template<typename T> class VectorM11{  //plantilla de vectro creado en clase
private:
    T * v_, * space_, * last_;

public:
    VectorM11() : v_{new T [0]}, space_{v_}, last_{v_} {}
    VectorM11(VectorM11<T> const& v) : v_{new T[v.capacity()]}, space_{v_ + v.size()}, last_{v_ + v.capacity()} {
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

    ~VectorM11() {delete[] v_;}

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

    void datos(){ //funcion que imprime los datos del vector

        entrada aux; //creamos una variable auxiliar de tipo videoclub

        for(int i=0; i<size(); i++){ //bucle que se repite tantas veces como objetos haya en el vector

            aux = *begin(i); //le asignamos a la variable el puntero que apunta a begin pasandole la posicion que queremos ver
            cout << "Nombre: " << aux.nombre << " | N. expediente: " << aux.expediente << " | Grupo: " << aux.tipo << " | Calificacion: " << aux.calificacion << endl; //se muestra por pantalla la informacion
        }

    }
};


template<typename T> class VectorM12{  //plantilla de vectro creado en clase
private:
    T * v_1, * space_, * last_;

public:
    VectorM12() : v_1{new T [0]}, space_{v_1}, last_{v_1} {}
    VectorM12(VectorM12<T> const& v1) : v_1{new T[v1.capacity()]}, space_{v_1 + v1.size()}, last_{v_1 + v1.capacity()} {
        try{
            for(auto i = size_t{0}; i< v1.size(); i++){
                v_1[i] = v1[i];
            }
        }
        catch (...){
            delete[] v_1;
            throw;
        }
    }

    ~VectorM12() {delete[] v_1;}

    auto capacity() const -> size_t { return last_ - v_1; }
    auto size() const -> size_t { return space_ - v_1; }
    auto empty() const -> bool { return v_1 == last_; }

    T mostrar_dato(int n) {return v_1[n];}

    auto begin(int n) const -> T* {return n + v_1;} //funcion que espera un parametro y devuelve un puntero a dicha posicion en el vector
    auto end() const -> T* {return space_;}

    auto push_back(T const& valor) {
        if (space_ == last_) {
            size_t cp = capacity(), new_cp = (cp == 0)? 2:2*cp;
            T* new_block = new T[new_cp];
            try{
                for(auto i = size_t{0}; i < cp; i++) {
                    new_block[i] = v_1[i];
                }
                new_block[cp] = valor;
            }
            catch (...) {
                delete[] new_block;
                throw;
            }
            delete[] v_1;
            v_1 = new_block;
            space_ = new_block + cp + 1;
            last_ = new_block + new_cp;
        }
        else{
            *space_ = valor;
            ++space_;

        }
    }

    void datos(){ //funcion que imprime los datos del vector

        entrada aux; //creamos una variable auxiliar de tipo videoclub

        for(int i=0; i<size(); i++){ //bucle que se repite tantas veces como objetos haya en el vector

            aux = *begin(i); //le asignamos a la variable el puntero que apunta a begin pasandole la posicion que queremos ver
            cout << "Nombre: " << aux.nombre << " | N. expediente: " << aux.expediente << " | Grupo: " << aux.tipo << " | Calificacion: " << aux.calificacion << endl; //se muestra por pantalla la informacion
        }
    }
};

VectorM11<entrada>* v_m11 = new VectorM11<entrada>; //free store grupo M11
VectorM12<entrada>* v_m12 = new VectorM12<entrada>; //free store grupo M12

void grabar_notas(){

    string nombre, expediente, tipo, calificacion;
    int exit=0;

    entrada a;

    cout << "Introuzca su nombre del estudiante\n"; //se piden los datos del estudiante...
    cin >> nombre;
    cout << "Introuzca su numero de expediente\n";
    cin >> expediente;
    cout << "Introuzca su calificacion\n";
    cin >> calificacion;

    while (exit==0){ //bucle que se repetira hasta que se introduzca bien un grupo

        cout << "Introuzca su grupo: [M11] o [M12]\n";
        cin >> tipo;

        if((tipo=="M11")||(tipo=="m11")){

            a.nombre=nombre, a.expediente=expediente, a.tipo=tipo, a.calificacion=calificacion; //declaramos los atributos con sus datos para crear el objeto
            v_m11->push_back(a);  //mandamos al vector los objetos creados

            cout << "Ha quedado grabada la nota de: " << nombre << endl; //confirmacion de realizacion

            exit=1; //salimos del bucle
        }
        else if((tipo=="M12")||(tipo=="m12")){
            a.nombre=nombre, a.expediente=expediente, a.tipo=tipo, a.calificacion=calificacion; //declaramos los atributos con sus datos para crear el objeto
            v_m12->push_back(a); //mandamos al vector los objetos creados

            cout << "Ha quedado grabada la nota de: " << nombre << endl; //confirmacion de realizacion

            exit=1; //salimos del bucle
        }
        else{
            cout << "Introduzca bien el grupo\n";
        }
    }
}

void ver_notas_grabadas(){

    string tipo;
    int exit=0;

    while (exit==0){ //bucle que se repetira hasta que se introduzca bien un grupo

        cout << "Introuzca su grupo: [M11] o [M12]\n";
        cin >> tipo;

        if((tipo=="M11")||(tipo=="m11")){
            v_m11->datos();
            exit=1;
        }
        else if((tipo=="M12")||(tipo=="m12")){
            v_m12->datos();
            exit=1;
        }
        else{
            cout << "Introduzca bien el grupo\n";
        }
    }
}

int main() {

    int elec=0;
    string contra;

    while (elec!=3) {
        cout << "\n";
        cout << "Bienvenido al sistema de notas\n";
        cout << "[1] Grabar una nota en el tablon (PROFESOR)\n";
        cout << "[2] Ver notas en el tablon (ALUMNO)\n";
        cout << "[3] Salir\n";
        cout << "Que accion desea realizar?\n";
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
                cout << "Introduzca la contrasena\n";
                cin >> contra;
                if (contra=="admin"){
                    grabar_notas();
                }
                else{
                    cout << "Contraseña incorrecta";
                }
                break;
            case 2:
                ver_notas_grabadas();
                break;
            case 3:
                cout << "Gracias por visitar nuestro sistema.\n";
                break;
            default:
                cout << "\n";
                cout << "Opcion inexistente.\n";
                break;
        }
    }
}