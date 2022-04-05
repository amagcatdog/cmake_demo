#include "mathlib.h"

MathLib::~MathLib() {

}

MathLib::MathLib() {

}

int MathLib::add(int x, int y) {
    return x+y;
}

double MathLib::pow(double base, int exp) {
    double res = 1;
    while (exp-- > 0) {
        res *= base;
    }
    return res;
}