#include "pch.h"
#include "vector.h"

// Пространство имен для математических операций с векторами
namespace VectorMath {

    // Конструктор класса Vector
    // Создает вектор из переданного списка значений
    // @param values - список вещественных чисел для инициализации вектора
    // @throws invalid_argument если переданный список пуст
    Vector::Vector(const vector<double>& values) : data(values) {
        if (data.empty()) {
            throw invalid_argument("Вектор не может быть пустым");
        }
    }

    // Вычисление длины (модуля) вектора
    // Использует евклидову норму: sqrt(x1^2 + x2^2 + ... + xn^2)
    // @return длина вектора как вещественное число
    double Vector::length() const {
        double sum = 0.0;
        for (const double& value : data) {
            sum += value * value;
        }
        return sqrt(sum);
    }

    // Нормализация вектора (приведение к единичной длине)
    // Делит каждый компонент вектора на его длину
    // @throws runtime_error если вектор имеет нулевую длину
    void Vector::normalize() {
        double len = length();
        if (len == 0) {
            throw runtime_error("Нельзя нормализовать пустой вектор");
        }
        for (double& value : data) {
            value /= len;
        }
    }

    // Вычисление скалярного произведения двух векторов
    // @param other - второй вектор для вычисления скалярного произведения
    // @return скалярное произведение как вещественное число
    // @throws invalid_argument если векторы имеют разную размерность
    double Vector::dotProduct(const Vector& other) const {
        if (data.size() != other.data.size()) {
            throw invalid_argument("Вектора должны иметь одинаковый размер");
        }

        double result = 0.0;
        for (size_t i = 0; i < data.size(); ++i) {
            result += data[i] * other.data[i];
        }
        return result;
    }

    // Получение внутренних данных вектора
    // @return константная ссылка на внутренний вектор значений
    const vector<double>& Vector::getData() const {
        return data;
    }

} // namespace VectorMath