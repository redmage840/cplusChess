#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

// try and pass python dict to function that takes map here

PYBIND11_MODULE(pytest, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");
}

int main(){
    std::cout<<"hello python import"<<std::endl;
    return 0;
    }