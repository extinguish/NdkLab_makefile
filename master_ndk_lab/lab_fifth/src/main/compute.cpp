#include <iostream>

int add(int a, int b);
int mul(int a, int b);
int divide(int a, int b);

int main()
{
    int a = 3;
    int b = 2;
    std::cout << "a + b = " << add(a, b) << std::endl;
    std::cout << "a x b = " << mul(a, b) << std::endl;
    std::cout << "a / b = " << divide(a, b) << std::endl;

    return 0;
}
