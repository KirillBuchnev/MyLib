#pragma once
#include "pch.h"
#include "..\MyStaticLib\vector.h"
#include <iostream>
#include <vector>

// ������������ ���� ��� �������������� �������� � ���������
namespace VectorMath {

    // ����� ��� ������ � ������������� ���������
    class DynamicVector {
    private:
        // ��������� �� ���������� ������
        Vector* vector;

    public:
        // ����������� ������ DynamicVector
        // ������� ������������ ������ �� ����������� ������ ��������
        // @param values - ������ ������������ ����� ��� ������������� �������
        explicit DynamicVector(const std::vector<double>& values);

        // ���������� ������ DynamicVector
        // ����������� ����������� ���������� ������ ��� �������
        ~DynamicVector();

        // ����� �������� ������� � �������
        // �������� ��� �������� �������, �������� �� ��������
        void printVector() const;

        // �������� ���� ������������ ��������
        // @param other - ��������� �� ������ ������ ��� ��������
        // @return ����� ������������ ������, ���������� ������ ��������
        // @throws runtime_error ���� ������� ����� ������ �����
        DynamicVector* add(const DynamicVector* other) const;

        // ��������� ������ �������
        // @return ������ � ���������� �������� �������
        std::vector<double> getData() const;
    };

} // namespace VectorMath

// Extern C-������� ��� ������ � �����������
extern "C" {
    // �������� ������ ������������� �������
    // @param values - ������ ��������
    // @param size - ������ �������
    // @return ��������� �� ��������� ������
    __declspec(dllexport) void* CreateDynamicVector(const double* values, int size);

    // ����� ������������� �������
    // @param vec - ��������� �� ������
    __declspec(dllexport) void PrintDynamicVector(void* vec);

    // �������� ���� ������������ ��������
    // @param vec1 - ������ ������
    // @param vec2 - ������ ������
    // @return ��������� �� �������������� ������
    __declspec(dllexport) void* AddDynamicVectors(void* vec1, void* vec2);

    // ��������� ������ �������
    // @param vec - ��������� �� ������
    // @param size - ��������� ��� �������� �������
    // @return ������ �������� �������
    __declspec(dllexport) double* GetVectorData(void* vec, int* size);

    // �������� ������������� �������
    // @param vec - ��������� �� ������
    __declspec(dllexport) void DeleteDynamicVector(void* vec);
}