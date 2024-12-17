#include "pch.h"
#include "header.h"
#include <iostream>

namespace VectorMath {

    // Конструктор класса DynamicVector
    // Создает динамический вектор из переданного списка значений
    // @param values - список вещественных чисел для инициализации вектора
    DynamicVector::DynamicVector(const std::vector<double>& values) {
        vector = new Vector(values);
    }

    // Деструктор класса DynamicVector
    // Освобождает динамически выделенную память для вектора
    DynamicVector::~DynamicVector() {
        delete vector;
    }

    // Вывод значений вектора в консоль
    // Печатает все элементы вектора, разделяя их пробелом
    void DynamicVector::printVector() const {
        for (double val : vector->getData()) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    // Сложение двух динамических векторов
    // @param other - указатель на второй вектор для сложения
    // @return новый динамический вектор, являющийся суммой исходных
    // @throws runtime_error если векторы имеют разную длину
    DynamicVector* DynamicVector::add(const DynamicVector* other) const {
        std::vector<double> result;
        auto& data1 = vector->getData();
        auto& data2 = other->vector->getData();

        if (data1.size() != data2.size()) {
            throw std::runtime_error("Vectors must be of equal length");
        }

        for (size_t i = 0; i < data1.size(); ++i) {
            result.push_back(data1[i] + data2[i]);
        }

        return new DynamicVector(result);
    }

    // Получение данных вектора
    // @return вектор с элементами текущего вектора
    std::vector<double> DynamicVector::getData() const {
        return vector->getData();
    }

} // namespace VectorMath

// Extern C-функции для работы с библиотекой
extern "C" {
    // Создание нового динамического вектора
    // @param values - массив значений
    // @param size - размер массива
    // @return указатель на созданный вектор
    __declspec(dllexport) void* CreateDynamicVector(const double* values, int size) {
        std::vector<double> vec(values, values + size);
        return new VectorMath::DynamicVector(vec);
    }

    // Вывод динамического вектора
    // @param vec - указатель на вектор
    __declspec(dllexport) void PrintDynamicVector(void* vec) {
        if (vec) {
            static_cast<VectorMath::DynamicVector*>(vec)->printVector();
        }
    }

    // Сложение двух динамических векторов
    // @param vec1 - первый вектор
    // @param vec2 - второй вектор
    // @return указатель на результирующий вектор
    __declspec(dllexport) void* AddDynamicVectors(void* vec1, void* vec2) {
        return static_cast<VectorMath::DynamicVector*>(vec1)->add(static_cast<VectorMath::DynamicVector*>(vec2));
    }

    // Получение данных вектора
    // @param vec - указатель на вектор
    // @param size - указатель для возврата размера
    // @return массив значений вектора
    __declspec(dllexport) double* GetVectorData(void* vec, int* size) {
        auto data = static_cast<VectorMath::DynamicVector*>(vec)->getData();
        *size = data.size();
        double* result = new double[data.size()];
        std::copy(data.begin(), data.end(), result);
        return result;
    }

    // Удаление динамического вектора
    // @param vec - указатель на вектор
    __declspec(dllexport) void DeleteDynamicVector(void* vec) {
        delete static_cast<VectorMath::DynamicVector*>(vec);
    }
}