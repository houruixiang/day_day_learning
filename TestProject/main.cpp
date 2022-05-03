#include <iostream>
#include <variant>
#include "ConvertVariant.h"

int main(void)
{
    std::variant<long, int, double> var {0.9};
    std::cout << std::holds_alternative<double>(var) << std::endl;
    std::cout << "hello world!" << std::endl;
    return 0;
}
