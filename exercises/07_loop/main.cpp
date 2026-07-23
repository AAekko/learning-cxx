#include "../exercise.h"

// TODO: 改正函数实现，实现正确的缓存优化斐波那契计算
// THINk: 这个函数是一个纯函数（pure function）吗？ 纯函数通常满足两个条件：1.相同的输入永远得到相同的输出。 2.不产生副作用，也就是不会修改函数外部或可长期保存的状态。
// READ: 纯函数 <https://zh.wikipedia.org/wiki/%E7%BA%AF%E5%87%BD%E6%95%B0>
static unsigned long long fibonacci(int i) {
    // TODO: 为缓存设置正确的初始值
    static unsigned long long cache[96]{0, 1};//使用 static 声明的（局部变量）只初始化一次，并且会一直存在到程序结束。普通局部变量则会在每次调用函数时重新创建。
    static int cached = 2;//因为循环中使用了 cached，所以要先声明。cached 用来记录“已经计算到哪里”，而 static 让这个进度在多次函数调用之间保留下来。  缓存cached也是有意义的，可以减少不必要的循环，因为前面的cache已经算过了。
    //第一次调用 fibonacci()，初始化 cache 和 cached，函数结束后，变量仍然存在；第二次调用 fibonacci()，不再初始化，继续使用上次留下的值；第三次调用 fibonacci()，仍然使用之前留下的值，程序结束，cache 和 cached 的生命周期结束。
    // TODO: 设置正确的循环条件
    //for循环：for (初始化; 继续循环的条件; 每轮“结束后”的操作)。下面那句；前面是空的表示没有初始化。
    for (; cached <= i; ++cached) {
        cache[cached] = cache[cached - 1] + cache[cached - 2];
    }
    return cache[i];
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT(fibonacci(0) == 0, "fibonacci(0) should be 0");
    ASSERT(fibonacci(1) == 1, "fibonacci(1) should be 1");
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(3) == 2, "fibonacci(3) should be 2");
    ASSERT(fibonacci(10) == 55, "fibonacci(10) should be 55");

    auto fib90 = fibonacci(90);
    std::cout << "fibonacci(90) = " << fib90 << std::endl;
    ASSERT(fib90 == 2880067194370816120, "fibonacci(90) should be 2880067194370816120");
    return 0;
}
