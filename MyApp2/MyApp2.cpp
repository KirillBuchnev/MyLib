#include <iostream>
#include <windows.h>
#include <vector>

typedef void* (*CreateDynamicVectorFunc)(const double*, int);
typedef void (*PrintDynamicVectorFunc)(void*);
typedef void* (*AddDynamicVectorsFunc)(void*, void*);
typedef double* (*GetVectorDataFunc)(void*, int*);
typedef void (*DeleteDynamicVectorFunc)(void*);

int main() {
    setlocale(LC_ALL, "RUS");
    
    HMODULE hDll = LoadLibrary(L"..\\MyDLLlib\\x64\\Release\\MyDLLlib.dll");
    if (!hDll) {
        std::cout << "Не удалось загрузить библиотеку" << std::endl;
        return 1;
    }

    CreateDynamicVectorFunc createVector = nullptr;
    PrintDynamicVectorFunc printVector = nullptr;
    AddDynamicVectorsFunc addVectors = nullptr;
    GetVectorDataFunc getVectorData = nullptr;
    DeleteDynamicVectorFunc deleteVector = nullptr;

    const char* functionNames[] = {
        "CreateDynamicVector",
        "PrintDynamicVector",
        "AddDynamicVectors",
        "GetVectorData",
        "DeleteDynamicVector"
    };

    void* functionPointers[] = {
        (void**)&createVector,
        (void**)&printVector,
        (void**)&addVectors,
        (void**)&getVectorData,
        (void**)&deleteVector
    };

    try {
        double values1[] = { 1.0, 2.0, 3.0 };
        double values2[] = { 4.0, 5.0, 6.0 };

        void* vec1 = createVector(values1, 3);
        void* vec2 = createVector(values2, 3);

        if (!vec1 || !vec2) {
            throw std::runtime_error("Не удалось создать векторы");
        }

        std::cout << "Вектор 1: ";
        printVector(vec1);

        std::cout << "Вектор 2: ";
        printVector(vec2);

        void* sumVector = addVectors(vec1, vec2);
        if (!sumVector) {
            throw std::runtime_error("Не удалось сложить векторы");
        }

        std::cout << "Сумма векторов: ";
        printVector(sumVector);

        deleteVector(vec1);
        deleteVector(vec2);
        deleteVector(sumVector);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    FreeLibrary(hDll);
    return 0;
}