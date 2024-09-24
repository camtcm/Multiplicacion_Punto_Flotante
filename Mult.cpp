#include <iostream>
#include <bitset>
#include <cmath>
#include <cstring>
using namespace std;

bitset<32> floatToBinary(float);
void componentes(float, int&, int&, int&);
float multiply(float,float);

int main() {
    float x, y;
    cout << "Ingrese un numero flotante: ";
    cin >> x;
    cout << "Ingrese otro numero flotante: ";
    cin >> y;

    // float resultado = multiply(x,y);
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

float multiply(float x, float y) {
    if (x == 0.0f || y == 0.0f) {
        return 0.0f;
    }

    int signR, exponentR, significandR; //resultado
    int signX, exponentX, significandX;
    int signY, exponentY, significandY;

    componentes(x, signX, exponentX, significandX);
    componentes(y, signY, exponentY, significandY);

    // SUMAR EXPONENTES
    exponentR = (exponentX + exponentY); 

    // RESTAR EL BIAS
    exponentR -= 127;
}