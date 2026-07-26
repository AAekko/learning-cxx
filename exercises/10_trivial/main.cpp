#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>
// 类型名FibonacciCache，说明这个结构体内部是什么样的；《变量名fib，代表实际创建出来的对象。》 ！定义类型名，就是为某一种成员结构取一个名字，方便后面创建多个采用相同结构的变量
struct FibonacciCache { // 这里定义了一种名为 FibonacciCache 的类型。它规定：每个 FibonacciCache 类型的对象都包含：一个名为 cache、长度为 16 的数组，一个名为 cached 的整数此时只是制定了结构，并没有创建实际对象。之后写：FibonacciCache fib;才创建了一个名为 fib 的对象
    unsigned long long cache[16];
    int cached;
};

// TODO: 实现正确的缓存优化斐波那契计算
// static 出现在不同位置时含义会有所区别
static unsigned long long fibonacci(FibonacciCache &cache, int i) {           // & 表示 cache 是传入对象的别名，而不是复制一份新对象。&cache就是形参，但是加了&又叫引用形参。
    for (; cache.cached <= i; ++cache.cached) {
        cache.cache[cached.cache] = cache.cache[cached.cache - 1] + cache[cached.cache - 2];
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    FibonacciCache fib{{0, 1}, 2};  // fib.cache[0] = 0;fib.cache[1] = 1;fib.cached = 2;
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
