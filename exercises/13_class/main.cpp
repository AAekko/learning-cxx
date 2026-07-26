#include "../exercise.h"

// C++ 中，`class` 和 `struct` 之间的**唯一区别**是
// `class` 默认访问控制符是 `private`，
// `struct` 默认访问控制符是 `public`。
// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

// 这个 class 中的字段被 private 修饰，只能在 class 内部访问。
// 因此必须提供构造器来初始化字段。
// READ: 构造器 <https://zh.cppreference.com/w/cpp/language/constructor>
class Fibonacci {
    size_t cache[16];  // size_t 是 C++ 中专门表示“对象大小、数组长度和下标”的无符号整数类型
    int cached;

public:
    // TODO: 实现构造器
    // Fibonacci()
    Fibonacci() : cache{}, cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }  // 因为cache和cached这两个成员被 private 修饰了，外部根本碰不到，所以必须通过构造器来完成这个“出生设定”。
    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 现在类型拥有无参构造器，声明时会直接调用
    // 这个写法不再是未定义行为了
    Fibonacci fib;  // 不需要在这里初始化了，因为结构体里面有构造器。你也初始化不了，因为结构体是class类型，外面改不了内部。
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
