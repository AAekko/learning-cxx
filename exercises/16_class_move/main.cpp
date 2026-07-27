#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(1) {
        cache[0] = 0;
        cache[1] = 1;
        ASSERT(capacity >= 2, "capacity should be at least 2")
    }

    // TODO: 实现移动构造器.接管 other 的缓存
    //DynFibonacci &&表示右值引用。other 就是即将被移动的原对象，这里对应 fib
    DynFibonacci(DynFibonacci &&other) noexcept
        : cache(other.cache), cached(other.cached) {  // 让新对象也获得这个数组的地址。但是现在两个对象指向同一个数组，这是危险的。
        other.cache = nullptr;  // 所以马上执行other.cache = nullptr;最终，新对象 fib_ 接管了数组，原对象 fib 不再拥有数组。这就是资源所有权的转移。
        other.cached = 0;
    }


    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    // noexcept 表示这个函数承诺不会抛出异常。移动操作只是复制指针、修改指针和整数，正常情况下不会抛出异常。给移动构造和移动赋值加上 noexcept 也能让标准库更放心地使用移动操作。
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
    // 防止 fib0 = std::move(fib0)
    // &other是取得 other 的地址
    if (this != &other) {
        // 先释放自己原来的缓存
        delete[] cache;

        // 接管 other 的缓存
        cache = other.cache;
        cached = other.cached;

        // other 不再拥有缓存
        other.cache = nullptr;
        other.cached = 0;
    }

        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        for (; cached < i; ++cached) {
            cache[cached + 1] = cache[cached] + cache[cached - 1];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");  // 因此这个版本不能继续计算，只能读取已经缓存的结果，所以它先检查是否有缓存。
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;  //cache 是一个指针。指针用作布尔值时：cache != nullptr  → true；cache == nullptr  → false
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);  // 这里的 fib_ 是 const 对象。编译器会认为它不允许被修改，所以只能调用末尾带 const 的成员函数
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);  //自己移动到自己会导致数据丢失
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
