#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;  // 表示声明一个名为 cache 的指针，它指向 size_t 类型的数据表示声明一个名为 cache 的指针，它指向 size_t 类型的数据
    int cached;

public:
    // TODO: 实现“动态”设置容量的构造器
    // new size_t[capacity] 动态创建一个长度为 capacity 的数组。new 返回数组首元素的地址。把这个地址保存到指针 cache 中。
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(2) {             // capacity 是构造时传入的缓存容量。例如：DynFibonacci fib(12);这里的 capacity 就是 12。
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
