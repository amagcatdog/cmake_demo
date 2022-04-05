#include <iostream>
#include <string>
#include "config.h"
#ifdef USE_MY_MATHLIB
#include "mathlib/mathlib.h"
#else
#include <math.h>
#endif

using std::string;
using std::cout;
using std::endl;

typedef int (*add_func)(int, int);
#ifdef USE_MY_MATHLIB
add_func add = MathLib::add;
#else
add_func add = [](int x, int y) -> int { return x+y; };
#endif

auto power = [](double base, int exp) -> double {
// 这里可以用配置的 USE_MY_MATHLIB 选项
// 也可以用CMAKE环境检查结果 HAVE_POW
#ifdef USE_MY_MATHLIB
return MathLib::pow(base, exp);
#else
return std::pow(base, exp);
#endif
};

void help() {
    cout << EXECUTABLE_NAME << " v" 
        << CMAKE_DEMO_VERSION_MAJOR << "."
        << CMAKE_DEMO_VERSION_MINOR << endl;

    cout << "Usage:\n" 
        << "  " << EXECUTABLE_NAME << " x add y\n"
        << "  " << EXECUTABLE_NAME << " x pow y"
        << endl;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        help();
    }
    if (string(argv[2]) == string("add")) {
        int res = add(std::stoi(argv[1]), std::stoi(argv[3]));
        cout << argv[1] << " " << argv[2] << " " << argv[3]
            << " is " << res << endl;
    } else if (string(argv[2]) == string("pow")) {
        double res = power(std::stod(argv[1]), std::stoi(argv[3]));
        cout << argv[1] << " " << argv[2] << " " << argv[3]
            << " is " << res << endl;
    } else {
        cout << argv[1] << " " << argv[2] << " " << argv[3]
            << " not supported" << endl;
    }
    return 0;
}