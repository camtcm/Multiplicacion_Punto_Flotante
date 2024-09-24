#include <iostream>
#include <bitset>
#include <cmath>
#include <cstring>
using namespace std;

bitset<32> floatToBinary(float);
void componentes(float, int&, int&, int&);

int main() {
    float x, y;
    cout << "Ingrese un numero flotante: ";
    cin >> x;
    cout << "Ingrese otro numero flotante: ";
    cin >> y;

    cout << "x: " << floatToBinary(x) << endl;
    cout << "y: " << floatToBinary(y) << endl;
}

bitset<32> floatToBinary(float value) {
    int bits = *(int*)&value;    
    return bitset<32>(bits); // Manipulacion 
}


void componentes(float valor, int& sign, int& exponent, int& significand) {
    bitset<32> bits = floatToBinary(valor);
    
    sign = (bits[31]) ? 1 : 0; // primer bit

    exponent = 0;
    for (int i = 30; i >= 23; --i) {
        exponent = (exponent << 1) | bits[i]; // desplazar y agregar
    }
    
    significand = 0;
    for (int i = 22; i >= 0; --i) {
        significand = (significand << 1) | bits[i];
    }
}
