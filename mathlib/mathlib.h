#pragma once

class MathLib {
public:
    ~MathLib();

    static int add(int x, int y);
    static double pow(double base, int exp);
private:
    MathLib();
};