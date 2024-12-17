#include <iostream>
#include <windows.h>
#include <vector>
#include <stdexcept>

// Пространство имен для математических операций с векторами
namespace VectorMath {
    // Типы функций для работы с динамическими векторами
    // Определение указателей на функции библиотеки DLL

    // Функция создания динамического вектора
    // @param values - массив значений
    // @param size - размер массива
    // @return указатель на созданный вектор
    typedef void* (*CreateDynamicVectorFunc)(const double*, int);

    // Функция вывода динамического вектора
    // @param vec - указатель на вектор
    typedef void (*PrintDynamicVectorFunc)(void*);

    // Функция сложения двух динамических векторов
    // @param vec1 - первый вектор
    // @param vec2 - второй вектор
    // @return указатель на результирующий вектор
    typedef void* (*AddDynamicVectorsFunc)(void*, void*);

    // Функция получения данных вектора
    // @param vec - указатель на вектор
    // @param size - указатель для возврата размера
    // @return массив значений вектора
    typedef double* (*GetVectorDataFunc)(void*, int*);

    // Функция удаления динамического вектора
    // @param vec - указатель на вектор
    typedef void (*DeleteDynamicVectorFunc)(void*);

    // Класс для работы с динамической библиотекой векторов
    class DynamicVectorLibrary {
    private:
        // Дескриптор библиотеки
        HMODULE hDll;

        // Указатели на функции библиотеки
        CreateDynamicVectorFunc createVector;
        PrintDynamicVectorFunc printVector;
        AddDynamicVectorsFunc addVectors;
        GetVectorDataFunc getVectorData;
        DeleteDynamicVectorFunc deleteVector;

    public:
        // Конструктор класса
        // Загружает библиотеку и получает указатели на функции
        // @param libraryPath - путь к библиотеке DLL
        DynamicVectorLibrary(const wchar_t* libraryPath) {
            // Загрузка библиотеки
            hDll = LoadLibrary(libraryPath);
            if (!hDll) {
                throw std::runtime_error("Не удалось загрузить библиотеку");
            }

            // Получение указателей на функции
            const char* functionNames[] = {
                "CreateDynamicVector",
                "PrintDynamicVector",
                "AddDynamicVectors",
                "GetVectorData",
                "DeleteDynamicVector"
            };

            void** functionPointers[] = {
                (void**)&createVector,
                (void**)&printVector,
                (void**)&addVectors,
                (void**)&getVectorData,
                (void**)&deleteVector
            };

            // Загрузка указателей на функции
            for (size_t i = 0; i < sizeof(functionNames) / sizeof(functionNames[0]); ++i) {
                functionPointers[i][0] = GetProcAddress(hDll, functionNames[i]);
                if (!functionPointers[i][0]) {
                    FreeLibrary(hDll);
                    throw std::runtime_error("Не удалось получить указатель на функцию");
                }
            }
        }

        // Деструктор класса
        // Освобождает библиотеку
        ~DynamicVectorLibrary() {
            if (hDll) {
                FreeLibrary(hDll);
            }
        }

        // Создание вектора
        // @param values - массив значений
        // @param size - размер массива
        // @return указатель на созданный вектор
        void* CreateVector(const double* values, int size) {
            return createVector(values, size);
        }

        // Вывод вектора
        // @param vec - указатель на вектор
        void PrintVector(void* vec) {
            printVector(vec);
        }

        // Сложение векторов
        // @param vec1 - первый вектор
        // @param vec2 - второй вектор
        // @return указатель на результирующий вектор
        void* AddVectors(void* vec1, void* vec2) {
            return addVectors(vec1, vec2);
        }

        // Удаление вектора
        // @param vec - указатель на вектор
        void DeleteVector(void* vec) {
            deleteVector(vec);
        }
    };
}

int main() {
    setlocale(LC_ALL, "RUS");

    try {
        // Создание экземпляра библиотеки
        VectorMath::DynamicVectorLibrary vectorLib(L"..\\MyDLLlib\\x64\\Release\\MyDLLlib.dll");

        // Создание тестовых массивов
        double values1[] = { 1.0, 2.0, 3.0 };
        double values2[] = { 4.0, 5.0, 6.0 };

        // Создание векторов
        void* vec1 = vectorLib.CreateVector(values1, 3);
        void* vec2 = vectorLib.CreateVector(values2, 3);

        if (!vec1 || !vec2) {
            throw std::runtime_error("Не удалось создать векторы");
        }

        // Вывод векторов
        std::cout << "Вектор 1: ";
        vectorLib.PrintVector(vec1);

        std::cout << "Вектор 2: ";
        vectorLib.PrintVector(vec2);

        // Сложение векторов
        void* sumVector = vectorLib.AddVectors(vec1, vec2);
        if (!sumVector) {
            throw std::runtime_error("Не удалось сложить векторы");
        }

        // Вывод суммы векторов
        std::cout << "Сумма векторов: ";
        vectorLib.PrintVector(sumVector);

        // Освобождение памяти
        vectorLib.DeleteVector(vec1);
        vectorLib.DeleteVector(vec2);
        vectorLib.DeleteVector(sumVector);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}