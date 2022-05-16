#ifndef PLAYGROUND_UTCALLBACK_H
#define PLAYGROUND_UTCALLBACK_H

#include <iostream>
#include <map>
#include <tuple>
#include <variant>
#include <type_traits>
#include <functional>

using FuncA = std::function<int(char)>;
using FuncB = std::function<int(int)>;
using FuncC = std::function<int(float)>;
using FuncD = std::function<int(double)>;
using FuncType = std::variant<std::nullptr_t, FuncA, FuncB, FuncC, FuncD>;
using FuncTuple = std::tuple<std::nullptr_t, FuncA, FuncB, FuncC, FuncD>;

int CallA(char) {
    std::cout << "FuncA char" << std::endl;
    return 0;
}
int CallB(int) {
    std::cout << "FuncB int" << std::endl;
    return 0;
}
int CallC(float) {
    std::cout << "FuncC float" << std::endl;
    return 0;
}

int CallD(double) {
    std::cout << "FuncD double" << std::endl;
    return 0;
}
struct CallBacks {
public:
    void RegisterCb(int idx, FuncType cb)
    {
        m_funcDict[idx] = cb;
    }

    template<typename... Args>
    int Call(int idx, Args&&... args) 
    {
        auto it = m_funcDict.find(idx);
        if (it != m_funcDict.end()) {
            if (std::holds_alternative<FuncA>(it->second)) {
                auto func = std::get<FuncA>(it->second);
                return std::invoke(func, std::forward<Args...>(args)...);
            }
            if (std::holds_alternative<FuncB>(it->second)) {
                auto func = std::get<FuncB>(it->second);
                return std::invoke(func, std::forward<Args...>(args)...);
            }
            if (std::holds_alternative<FuncC>(it->second)) {
                auto func = std::get<FuncC>(it->second);
                return std::invoke(func, std::forward<Args...>(args)...);
            }
            if (std::holds_alternative<FuncD>(it->second)) {
                auto func = std::get<FuncD>(it->second);
                return std::invoke(func, std::forward<Args...>(args)...);
            }
        }


        // auto it = m_funcDict.find(idx);
        // if (it != m_funcDict.end()) {
        //     auto func = nullptr;
        //     if (std::holds_alternative<FuncA>(it->second)) {
        //         func = std::get<FuncA>(it->second);
        //     }
        //     else if (std::holds_alternative<FuncB>(it->second)) {
        //         func = std::get<FuncB>(it->second);
        //     }
        //     else if (std::holds_alternative<FuncC>(it->second)) {
        //         func = std::get<FuncC>(it->second);
        //     }
        //     else if (std::holds_alternative<FuncD>(it->second)) {
        //         func = std::get<FuncD>(it->second);
        //     } else {
        //         return 0;
        //     }
        //     return std::invoke(func, std::forward<Args...>(args)...);
        // }

        return 0;
    }

private:
    std::map<int, FuncType> m_funcDict;

};

void Test_CallBacks()
{
    std::cout << std::endl << "---Test CallBacks---" << std::endl;

    CallBacks callback;
    callback.RegisterCb(0, FuncType {(FuncA)CallA});
    callback.RegisterCb(1, FuncType {(FuncB)CallB});
    callback.RegisterCb(2, FuncType {(FuncC)CallC});
    callback.RegisterCb(3, FuncType {(FuncD)CallD});

    int res = callback.Call(0, (char)(0));
    callback.Call(1, (int)(0));
    callback.Call(2, (float)(0));
    callback.Call(3, (double)(0));
}

#endif
