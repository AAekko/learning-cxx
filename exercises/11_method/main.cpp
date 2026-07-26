#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算.这里的 get() 叫作成员函数, 在成员函数内部，可以直接访问同一个对象的成员
    unsigned long long get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib{{0, 1}, 2};                                 //这是结构体的聚合初始化，按照成员定义的顺序赋值
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");  //C++ 中，struct 的成员默认是 public，所以外部可以直接调用：fib.get(10);Tip:聚合初始化只初始化结构体中的“数据成员”，不初始化成员函数。
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
