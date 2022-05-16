#include <iostream>
#include <map>
#include <tuple>
#include <variant>
#include <type_traits>
#include <functional>
#include "ConvertVariant.h"
#include "Callbacks.h"
#include "CallbackLists.h"
#include "SimpleCallbackList.h"
#include "Delegate.h"

int main(void)
{
    std::variant<long, int, double> var {0.9};
    std::cout << std::holds_alternative<double>(var) << std::endl;

    std::cout << "hello world!" << std::endl;

    Test_CallBacks();

    Test_CallbackList();

    Test_SimpleCallbackList();

    Test_Delegate();
    return 0;
}
