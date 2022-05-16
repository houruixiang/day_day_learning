#ifndef NO_TEMPLATE_DELEGATE_H
#define NO_TEMPLATE_DELEGATE_H

#include <map>
#include <string>
#include <tuple>
#include <functional>
#include <type_traits>

struct NoTemplateDelegate {
public:
  typedef void* InstancePtr;
  typedef void (*InternalFunction)(InstancePtr, int);
  typedef std::pair<InstancePtr, InternalFunction> Stub;
 
  // turns a free function into our internal function stub
  template <void (*Functor)(int)>
  static inline void FunctorStub(InstancePtr, int arg0)
  {
    // we don't need the instance pointer because we're dealing with free functions
    return (Functor)(arg0);
  }
 
  // turns a member function into our internal function stub
  template <class C, void (C::*Functor)(int)>
  static inline void ClassMethodStub(InstancePtr instance, int arg0)
  {
    // cast the instance pointer back into the original class instance
    return (static_cast<C*>(instance)->*Functor)(arg0);
  }
 
public:
  NoTemplateDelegate() : m_stub(nullptr, nullptr) {}

  /// Binds a free function
  template <void (*Functor)(int)>
  void Bind(void)
  {
    m_stub.first = nullptr;
    m_stub.second = &FunctorStub<Functor>;
  }
 
  /// Binds a class method
  template <class C, void (C::*Functor)(int)>
  void Bind(C* instance)
  {
    m_stub.first = instance;
    m_stub.second = &ClassMethodStub<C, Functor>;
  }
 
  /// Invokes the delegate
  void Invoke(int arg0) const
  {
    // static_assert(m_stub.second != nullptr, "Cannot invoke unbound delegate. Call Bind() first.");
    return m_stub.second(m_stub.first, arg0);
  }
 
private:
  Stub m_stub;
};


//------------------------------------------------------------------------------------------------
void FreeFunction(int)
{
    // do something
    std::cout << "FreeFunction" << std::endl;
}
 
struct TClass {
public:
    void MemberFunction(int)
    {
        // do something
        std::cout << "TClass::MemberFunction" << std::endl;
    }
};


struct DClass {
public:
    void MemberFunction(int)
    {
        // do something
        std::cout << "DClass::MemberFunction" << std::endl;
    }
};

void Test_NoTemplateDelegate()
{
    std::cout << std::endl << "---Test NoTemplateDelegate---" << std::endl;

    std::map<std::tuple<std::string, int>, NoTemplateDelegate> dict;
    {
        NoTemplateDelegate delegate;
        delegate.Bind<&FreeFunction>();  // free function
        std::string name = "FreeFunction";
        std::tuple<std::string, int> key {name, 0};
        dict[key] = delegate;
    }
    {
        TClass c;
        NoTemplateDelegate delegate;
        delegate.Bind<TClass, &TClass::MemberFunction>(&c);
        std::string name = "TClass::MemberFunction";
        std::tuple<std::string, int> key {name, 1};
        dict[key] = delegate;
    }
    {
        DClass c;
        NoTemplateDelegate delegate;
        delegate.Bind<DClass, &DClass::MemberFunction>(&c);
        std::string name = "DClass::MemberFunction";
        std::tuple<std::string, int> key {name, 2};
        dict[key] = delegate;
    }

    {
        std::tuple<std::string, int> key {"FreeFunction", 0};
        dict[key].Invoke(10);             // calls the bound function
    }
    {
        std::tuple<std::string, int> key {"TClass::MemberFunction", 1};
        dict[key].Invoke(100);             // calls the bound function
    }
    {
        std::tuple<std::string, int> key {"DClass::MemberFunction", 2};
        dict[key].Invoke(1000);             // calls the bound function
    }
}

#endif