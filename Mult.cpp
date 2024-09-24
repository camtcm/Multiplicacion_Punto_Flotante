#include <iostream>
#include <bitset>
#include <cmath>
#include <iomanip>

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

    float resultado = multiply(x,y);
    // cout << fixed << setprecision(20);
    cout << "\nResultado (algoritmo implementado): " << resultado << endl;
    cout << "Resultado (operacion de C++): " << x * y << endl;

    cout << endl << "------------ setprecision(19) -------------" << endl;
    // std::cout << "Número: " << std::fixed << std::setprecision(19) << num << std::endl;
    cout << "Resultado (algoritmo implementado): " << fixed << setprecision(19) << resultado << endl;
    cout << "Resultado (operacion de C++): " << fixed << setprecision(19) << x*y << endl;
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

    int resultado;
    int signR, exponentR; //resultado
    int signX, exponentX, significandX;
    int signY, exponentY, significandY;

    componentes(x, signX, exponentX, significandX);
    componentes(y, signY, exponentY, significandY);

    // SUMAR EXPONENTES
    exponentR = (exponentX + exponentY); 

    // RESTAR EL BIAS
    exponentR -= 127;

    // REPORTAR OVERFLOW - UNDERFLOW
    if (exponentR >= 255) {
        cout << "Overflow exponente";
        return INFINITY;
    } else if (exponentR <= 0) {
        cout << "Underflow exponente";
        return 0.0f;
    }

    significandX = significandX | (1 << 23);
    significandY = significandY | (1 << 23);

    // MULTIPLICAR SIGNIFICANDS 
    long long significandR = (long long)significandX * (long long) significandY; // manejar desbordamiento


    // NORMALIZAR
    if (significandR & (1LL << 47)) {
        significandR = significandR >> 24; 
        exponentR += 1; // ajustar exponente 
    } else {
        significandR = significandR >> 23;
    }

    signR = signX ^ signY; // xor

    resultado = (signR << 31) | (exponentR << 23) | (significandR & 0X7FFFFF);
    float resultadoFloat;
    // float resultadoFloat = *((float*)&resultado);
    memcpy(&resultadoFloat, &resultado, sizeof(resultadoFloat));

    return resultadoFloat;

}