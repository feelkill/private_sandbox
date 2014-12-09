/* http://www.cnblogs.com/hazir/p/4138692.html */

#include <iostream>
#include <string.h>

struct Foo 
{
    void bar() const { }
};

struct A 
{
    void foo() const 
    {
        std::cout << "A's this: " << this << std::endl;
    }

    char pad0[32];
};

struct B 
{
    void bar() const 
    {
        std::cout << "B's this: " << this << std::endl;
    }

    char pad2[64];
};

struct C : A, B
{ 
};

void call_by_ptr(const C &obj, void (C::*mem_func)() const)
{
    void *data[2];
    memcpy(data, &mem_func, sizeof(mem_func));
    std::cout << "------------------------------\n"
        "Object ptr:\t" << &obj <<
        "\nFunction ptr:\t" << data[0] <<
        "\nPointer adj:\t" << data[1] << std::endl;
    (obj.*mem_func)();
}

int main() 
{
    std::cout <<
        "sizeof(int*)      == " << sizeof(int*) << "\n"
        "sizeof(double*)   == " << sizeof(double*) << "\n"
        "sizeof(void(*)()) == " << sizeof(void(*)()) << std::endl;

    // test the size of member method pointer
    //
    std::cout << "sizeof(Foo::bar()) == " << sizeof(&Foo::bar) << std::endl;

    // test this pointer
    //
    C obj;
    obj.foo();
    obj.bar();

    C obj2;
    call_by_ptr(obj2, &C::foo);
    call_by_ptr(obj2, &C::bar);
}
