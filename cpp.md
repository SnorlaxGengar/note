##### Class Member function

Class member function is different from common function.
Can't assign `Derived::foo` to a FuncPtr variable.
May the compiler implement it like: `void foo(Derived* ptr)`.
Ref to [this](https://godbolt.org/z/PErE1c3f6).

```C++
#include <iostream>
#include <functional>
#include <typeinfo>

class Base {
    public:
        virtual void foo() { std::cout << __LINE__ << std::endl; }
};

class Derived : public Base {
    public:
        virtual void foo() { std::cout << __LINE__ << std::endl; }
};

using FuncPtr = void ();

int main() {
    Derived d;
    auto fp = std::bind(&Derived::foo, &d);
    std::cout << typeid(fp).name() << std::endl;
    fp();

    // FuncPtr fp_normal = reinterpret_cast<void ()>(&Derived:
    // fp_normal();

    return 0;
}
```

According c++filt to decode type name below:

```bash
$ c++filt -t St5_BindIFM7DerivedFvvEPS0_EE
std::_Bind<void (Derived::*(Derived*))()>
```
