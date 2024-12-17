#ifndef VECTOR_H
#define VECTOR_H
#include "pch.h"
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

class Vector {

    vector<double> data; 

public:
    Vector(const vector<double>& values);

    double length() const;

    void normalize();

    double dotProduct(const Vector& other) const;

    const vector<double>& getData() const;
};

#endif 