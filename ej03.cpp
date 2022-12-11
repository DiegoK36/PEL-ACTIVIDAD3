#include <iostream>
#include <string> //manejo de strings
#include <cctype>
#include <algorithm> //manejo de espacios

using namespace std;

int exit_=0;
class entrada {
    public:
    string fecha;
    string cliente;
    string tipo;
    entrada(){
        fecha="";
        tipo="";
        cliente="";
    }entrada(string x,string y, string z){
        fecha=x;
        tipo=y;
        cliente=z;
     }

};

template<typename T> class VectorNormal{  //plantilla de vectro creado en clase
private:
    T * v_, * space_, * last_;

public:
    VectorNormal() : v_{new T [0]}, space_{v_}, last_{v_} {}
    VectorNormal(VectorNormal<T> const& v) : v_{new T[v.capacity()]}, space_{v_ + v.size()}, last_{v_ + v.capacity()} {
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

    ~VectorNormal() {delete[] v_;}

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
    }};
template<typename T> class VectorVIP{  //plantilla de vectro creado en clase
private:
    T * v_1, * space_, * last_;

public:
    VectorVIP() : v_1{new T [0]}, space_{v_1}, last_{v_1} {}
    VectorVIP(VectorVIP<T> const& v1) : v_1{new T[v1.capacity()]}, space_{v_1 + v1.size()}, last_{v_1 + v1.capacity()} {
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

    ~VectorVIP() {delete[] v_1;}

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

    
   
    };


                    



int main() {

    VectorNormal<entrada>* v = new VectorNormal<entrada>; //free store
    VectorVIP<entrada>* v1 = new VectorVIP<entrada>; //free store
    string tip, nomb;
    entrada a, b, c, d, e;
    a.fecha="11/12 a las 21:00";
    cout<<"******** Bienvenido al concierto de Dani Martin, el "<<a.fecha<< " ********"<<endl;
    cout<<"         Dime tu nombre:";
    cin>>nomb;
    cout<<"         ¿Que tipo de entrada quieres, [VIP] o [Normal]?";
    cin>>tip;
    a.cliente=nomb;
    a.tipo=tip;
    if(tip=="VIP"){
    v1->push_back(a);
    }else if(tip=="Normal"){
     v->push_back(a);
    }
   
     //mandamos al vector los 5 objetos creados
}