#pragma once
#include "pch.h"
#include "..\MyStaticLib\vector.h"
#include <iostream>
#include <vector>

extern "C" {
    __declspec(dllexport) void* CreateDynamicVector(const double* values, int size);
    __declspec(dllexport) void PrintDynamicVector(void* vec);
    __declspec(dllexport) void* AddDynamicVectors(void* vec1, void* vec2);
    __declspec(dllexport) double* GetVectorData(void* vec, int* size);
    __declspec(dllexport) void DeleteDynamicVector(void* vec);
}

class DynamicVector {
private:
    Vector* vector;

public:
    DynamicVector(const std::vector<double>& values);
    ~DynamicVector();
    void printVector() const;
    DynamicVector* add(const DynamicVector* other) const;
    std::vector<double> getData() const;
};