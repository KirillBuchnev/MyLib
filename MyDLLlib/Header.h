#pragma once
#include "pch.h"
#include "..\MyStaticLib\vector.h"
#include <iostream>
#include <vector>

// ѕространство имен дл€ математических операций с векторами
namespace VectorMath {

    //  ласс дл€ работы с динамическими векторами
    class DynamicVector {
    private:
        // ”казатель на внутренний вектор
        Vector* vector;

    public:
        //  онструктор класса DynamicVector
        // —оздает динамический вектор из переданного списка значений
        // @param values - список вещественных чисел дл€ инициализации вектора
        explicit DynamicVector(const std::vector<double>& values);

        // ƒеструктор класса DynamicVector
        // ќсвобождает динамически выделенную пам€ть дл€ вектора
        ~DynamicVector();

        // ¬ывод значений вектора в консоль
        // ѕечатает все элементы вектора, раздел€€ их пробелом
        void printVector() const;

        // —ложение двух динамических векторов
        // @param other - указатель на второй вектор дл€ сложени€
        // @return новый динамический вектор, €вл€ющийс€ суммой исходных
        // @throws runtime_error если векторы имеют разную длину
        DynamicVector* add(const DynamicVector* other) const;

        // ѕолучение данных вектора
        // @return вектор с элементами текущего вектора
        std::vector<double> getData() const;
    };

} // namespace VectorMath

// Extern C-функции дл€ работы с библиотекой
extern "C" {
    // —оздание нового динамического вектора
    // @param values - массив значений
    // @param size - размер массива
    // @return указатель на созданный вектор
    __declspec(dllexport) void* CreateDynamicVector(const double* values, int size);

    // ¬ывод динамического вектора
    // @param vec - указатель на вектор
    __declspec(dllexport) void PrintDynamicVector(void* vec);

    // —ложение двух динамических векторов
    // @param vec1 - первый вектор
    // @param vec2 - второй вектор
    // @return указатель на результирующий вектор
    __declspec(dllexport) void* AddDynamicVectors(void* vec1, void* vec2);

    // ѕолучение данных вектора
    // @param vec - указатель на вектор
    // @param size - указатель дл€ возврата размера
    // @return массив значений вектора
    __declspec(dllexport) double* GetVectorData(void* vec, int* size);

    // ”даление динамического вектора
    // @param vec - указатель на вектор
    __declspec(dllexport) void DeleteDynamicVector(void* vec);
}