#pragma once
#include <vector>
#include "vector.h"

namespace VectorMath {

    // Класс для работы с динамическими векторами
    class DynamicVector {
    private:
        Vector* vector; // Указатель на внутренний вектор

    public:
        // Конструктор из списка значений
        explicit DynamicVector(const std::vector<double>& values);

        // Деструктор
        ~DynamicVector();

        // Вывод вектора
        void printVector() const;

        // Сложение с другим вектором
        DynamicVector* add(const DynamicVector* other) const;

        // Получение данных
        std::vector<double> getData() const;
    };

} // namespace VectorMath