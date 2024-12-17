#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

namespace VectorMath {

    // Класс для работы с математическими векторами
    class Vector {
    private:
        vector<double> data; // Внутренние данные вектора

    public:
        bool isHappyVector() const;
        // Конструктор из списка значений
        explicit Vector(const vector<double>& values);

        // Вычисление длины вектора
        double length() const;

        // Нормализация вектора
        void normalize();

        // Скалярное произведение с другим вектором
        double dotProduct(const Vector& other) const;

        // Получение внутренних данных
        const vector<double>& getData() const;
    };

} // namespace VectorMath