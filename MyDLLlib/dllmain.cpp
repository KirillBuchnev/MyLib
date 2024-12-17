#include "pch.h"
#include "header.h"
#include <iostream>

DynamicVector::DynamicVector(const std::vector<double>& values) {
    vector = new Vector(values);
}

DynamicVector::~DynamicVector() {
    delete vector;
}

void DynamicVector::printVector() const {
    for (double val : vector->getData()) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

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

std::vector<double> DynamicVector::getData() const {
    return vector->getData();
}

extern "C" {
    __declspec(dllexport) void* CreateDynamicVector(const double* values, int size) {
        std::vector<double> vec(values, values + size);
        return new DynamicVector(vec);
    }

    __declspec(dllexport) void PrintDynamicVector(void* vec) {
        if (vec) {
            static_cast<DynamicVector*>(vec)->printVector();
        }
    }

    __declspec(dllexport) void* AddDynamicVectors(void* vec1, void* vec2) {
        return static_cast<DynamicVector*>(vec1)->add(static_cast<DynamicVector*>(vec2));
    }

    __declspec(dllexport) double* GetVectorData(void* vec, int* size) {
        auto data = static_cast<DynamicVector*>(vec)->getData();
        *size = data.size();
        double* result = new double[data.size()];
        std::copy(data.begin(), data.end(), result);
        return result;
    }

    __declspec(dllexport) void DeleteDynamicVector(void* vec) {
        delete static_cast<DynamicVector*>(vec);
    }
}