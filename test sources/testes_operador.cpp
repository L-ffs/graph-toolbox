#include <iostream>
using namespace std;

class classe {

    public:
    int valor;
    bool value;
    operator int() const{
        return valor;
    }
};

int main () {
    
    int idade= 10;
    classe obj;
    obj.valor= 10;
    
    cout << idade + obj << endl;
    
    return 0;
}