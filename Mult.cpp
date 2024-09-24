#include <iostream>
#include <bitset>
using namespace std;

bitset<32> floatToBinary(float);

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
    return bitset<32>(bits); // Facil manipulacion
}


