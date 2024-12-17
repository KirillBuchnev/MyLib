#include <iostream>
#include "..\MyStaticLib\vector.h" 

int main() {
    setlocale(LC_ALL, "RUS");
    try {
        Vector v1({ 3.0, 4.0 });
        Vector v2({ 1.0, 0.0 }); 

        cout << "Длина вектора v1: " << v1.length() << endl;

        v1.normalize();
        cout << "Нормализованный вектор v1: ";
        for (const auto& value : v1.getData()) {
            cout << value << " ";
        }
        cout << endl;

        double dot_product = v1.dotProduct(v2);
        cout << "Скалярное произведение v1 и v2: " << dot_product << endl;

        cout << "Данные вектора v2: ";
        for (const auto& value : v2.getData()) {
            cout << value << " ";
        }
        cout << endl;

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}