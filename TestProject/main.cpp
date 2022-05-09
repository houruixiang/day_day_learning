#include <iostream>
#include <map>
#include <tuple>
#include <variant>
#include <type_traits>
#include <functional>
#include "ConvertVariant.h"
#include "Callbacks.h"
#include "CallbackLists.h"


int main(void)
{
    std::variant<long, int, double> var {0.9};
    std::cout << std::holds_alternative<double>(var) << std::endl;

    std::cout << "hello world!" << std::endl;

    Test_CallBacks();

    Test_CallbackList();

    return 0;
}
